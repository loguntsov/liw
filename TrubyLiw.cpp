//---------------------------------------------------------------------------

#include <vcl.h>
#include <Math.hpp>
#include <Math.h>
#include <Sysutils.hpp>
#include "MathMethod.h"
#include <algorithm.h>

#pragma hdrstop

#include "TrubyLiw.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

double const PI=M_PI;
double const MaxHPerepad=6;
double Hmin=2; // Минимальное заглубление
double Hmax=8; // Максимальное заглубление
double H0max=8.5; // Максимальное заглубление для насосной станции
double hPer=5; // Максимальная глубина перепадного колодца
double Md=99; // Максимальное суточное количество осадков по СНиП 2.01.01-82
double MinDim=0;
double Tk=3; // Время поверхностной концентрации
double Tl=1; // Время пробега по лотку
double N=0.65; // Климатич коэф.

double step(double x,double y);

//
//  CMaterial
//
CMaterial::CMaterial(
        char *NamE, // наименование материала
        char *Gost, // гост на материал
        double N, // коэффициент шероховатости
        double VMAX // Максимальная скорость для данного материала
)
{
    Name=NamE;GOST=Gost;n=N;
    Vmax=VMAX;
}

// Возможные материалы труб.

CMaterial MAsbest1("асбестоцементные безнапорные","ГОСТ 1839",0.012,7);
CMaterial MAsbest2("асбестоцементные напорные","ГОСТ 539",0.012,7);
CMaterial MKeramika("керамические","ГОСТ 286",0.014,7);
CMaterial MBeton("железобетонные безнапорные","ГОСТ 6482",0.014,7);
CMaterial MStal("стальные электросварные","ГОСТ 8696",0.012,10);
CMaterial MChug("чугунные","ГОСТ 9583",0.012,10);

//
// CDiametr
//


CDiametr::CDiametr(int Usl,double Fakt)
{
    UslDiametr=Usl;
    FaktDiametr=Fakt;
}
CDiametr::CDiametr()
{
   UslDiametr=FaktDiametr=0;
}
double CDiametr::GetMaxNapoln(void) // Возвращает максимальное наполнение для данного диаметра
{
    return MaxNapoln(UslDiametr);
}
double CDiametr::GetVtoNap100(double Q) // Возвращает скорость идеальной жидкости при 100% наполнении, Q - л/c
{
    return 4.0e3*Q/PI/(FaktDiametr*FaktDiametr);
}

//
//  CTruba
//
CTruba::CTruba(TrubaInform Information)
{
    Info=Information;
    //HLBegMin=Info.HLBeg ;
    Rash=true;
    DH=0;
    //PerepadWells=
    GS=false;
}
CTruba::~CTruba()
{
    
}
CSortament * CTruba::GetSortament(void)
{
    
    try
    {
    if (NSortament<0)
    {
        return NULL;
    }
    return Info.SortamentItem->Sortament[NSortament];
    } catch (...)
    {
        return NULL;
    }
}
void CTruba::ToMaxSortament(void)
{
    if (!FindDiametrAndi1000(Hmin,Hmax,true))
    {
        //if (Q<Info.SortamentItem->Sortament[0]->GetQmin())
        {
            // Не расчетные участки
            Rash=false;
            NSortament=0;
            IsDiametrGood();
            Time=Info.Time;
            i1000=Geti1000ToHmin();
        }
    }
            /*
            if (HEnd>2*Hmax-Hmin) SetNapWodowod(); else
                if (HEnd>H0max) SetPumpStation(Hmin+GetDiametr());
        } else
        if (FindDiametrAndi1000(Hmax,Hmax+(Hmax-Hmin),true))
        {
            if (HEnd>H0max) SetPumpStation(Hmin+GetDiametr());
        } else
        if (FindDiametrAndi1000(ZEnd-ZBeg,Hmin,true))
        {
            SetWells(Hmin+GetDiametr());
        } else
        {
            SetNapWodowod(); // Напорные водоводы
        }
    }*/
}

void CTruba::ToGetSortament(void)
{
    ToMaxSortament();
    //ToNapolnenie();
}

double CTruba::func(double x)
{
    double d=Sortament->Diametr.FaktDiametr/1000;
    //double a0=Sortament->Material->a0;
    //double b0=Sortament->Material->b0;
    double a=2*ArcCos(2*x-1);
    double n=Sortament->Material->n;
    double A0=2*PI-a;
    double B0=sin(a);
    double R=(d/4)*(A0+B0)/A0;
    double w=(d*d/8)*(A0+B0);
    double y=2.5*sqrt(n)-0.13-0.75*sqrt(R)*(sqrt(n)-0.1);
    return w*pow(R,y)/n*sqrt(R*i1000/1000)-Q/1000;
}
void CTruba::ToNapolnenie(void)
{
    //if (NapWodowod!=NULL) { hd=1;return;}
    const double b=0.001;
    const double h=-0.1;
    double x1=1,x2=1+h,y1=func(x1),y2;
    const double e=0.000001;
    while (x2>b)
    {
        y2=func(x2);
        if (y1*y2<=0)
        {
            double xx1=x1,xx2=x2;
            while (!(fabs(xx1-xx2)<e || fabs(func(xx1)-func(xx2))<=e))
            {
                double c=(xx1+xx2)/2;
                if(func(xx1)*func(c)<0) xx2=c; else xx1=c;
            }
            hd=(xx1+xx2)/2;return;
        }
        x1=x2;x2=x1+h;y1=y2;
    }
    hd=1;
}
double CTruba::GetLen(void)
{
    return Info.Len;
}
double CTruba::GetHEnd(void)
{
    return (double(int((ZEnd-ZBeg+HBeg+i1000/1000*Len)*100+0.5)))/100;
}
double CTruba::GetHHEnd(void)
{
    return HEnd-GetDiametr();
}
void CTruba::SetHEnd(double HEND)
{
    i1000=(ZBeg-ZEnd-(HBeg-HEND))/Len*1000;
}
double CTruba::GetW(double hd)
{
    double a=2*ArcCos(2*hd-1);
    double d=GetDiametr();
    return (d*d/8)*(2*PI-a+sin(a));
}
double CTruba::GetW(void)
{
    return GetW(1);
}
double CTruba::GetV(void)
{
    //if (NapWodowod==NULL)
    return (Q/1000)/GetW();
    //return NapWodowod->GetV();
}
double CTruba::GetZLBeg(void)
{
    return ZBeg-HBeg;
}
double CTruba::GetZLEnd(void)
{
    return ZEnd-HEnd;
}
double CTruba::GetZHBeg(void)
{
    return ZLBeg+GetDiametr();
}
double CTruba::GetZHEnd(void)
{
    return ZLEnd+GetDiametr();
}
double CTruba::GetDiametr(void)
{
    
    try
    {
        return Sortament->Diametr.FaktDiametr/1000;
    }
    catch (...)
    {
        throw "GetDiametr";
        return 0;
    }
}
double CTruba::Geti1000mest(void)
{
    return ((ZBeg-ZEnd)/Len)*1000;
}
double CTruba::Geti1000ToHminimum(void)
{
    double x=(ZBeg-ZEnd-(HBeg-(Hmin+GetDiametr()-MaxHPerepad)))/Len*1000;
    if (x<1/Sortament->Diametr.FaktDiametr*1000) x=1/Sortament->Diametr.FaktDiametr*1000;
    return x;
}
double CTruba::Geti1000ToHmin(void)
{
    double x=(ZBeg-ZEnd-(HBeg-(Hmin+GetDiametr())))/Len*1000;
    if (x<1/Sortament->Diametr.FaktDiametr*1000) x=1/Sortament->Diametr.FaktDiametr*1000;
    return x;
}

double CTruba::Geti1000ToHmax(void)
{
    return (ZBeg-ZEnd-(HBeg-Hmax))/Len*1000;
}
double CTruba::Geti1000(void)
{
    return fi1000;
}
double CTruba::GetZBeg(void)
{
    return Info.ZBeg;
}
double CTruba::GetZEnd(void)
{
    return Info.ZEnd;
}
double CTruba::GetHBeg(void)
{
    return fHBeg+DH;
}
void CTruba::SetHBeg(double X)
{
    fHBeg=X;
    DH=0;
}
double CTruba::GetQmax()
{
    return Sortament->GetQmin()*sqrt(i1000/Sortament->Geti1000min());
}
double CTruba::GetBeta(void) // Возвращает коэффициент бета для рачета расхода
{
    double x[]={0.4,0.5,0.6,0.7};
    double y[]={0.8,0.75,0.7,0.65};
    LinIntr a(x,y,4);
    double beta;
    if (N<=0.4) return 0.8; else
    if (N>=0.7) return 0.65; else beta=a.GetY(N);
    double imest=Geti1000mest();
    if (imest>=10 && imest<=30) return beta*1.15;
    if (imest>30) return 1;
    return beta;
}

void CTruba::Seti1000(double i)
{
    //i=int(double(i/0.5)+0.999999)*0.5;
    if (i<1/Sortament->Diametr.FaktDiametr*1000) i=1/Sortament->Diametr.FaktDiametr*1000;
    /*if (Sortament->Diametr.UslDiametr==150)
    {
        if (i<8)
        {
            fi1000=8;return;
        }
        fi1000=i;return;
    }
    if (Sortament->Diametr.UslDiametr==200)
    {
        if (i<5)
        {
            fi1000=5;return;
        }
        fi1000=i;return;
    }*/
    fi1000=i;
}
double CTruba::GetVmin(void)
{
    return Sortament->GetVmin();//,Vvh);
}
void CTruba::CreateReport(TStrings *Str)
{
    Str->Add("Сведения о трубопроводе: ");
    Str->Add("      Расход: Q="+AnsiString(Q));
    Str->Add("      Диаметр: d="+AnsiString(Sortament->Diametr.UslDiametr)+" мм. ~"+FloatToStr(GetDiametr())+" м.");
    Str->Add("      Материал труб: Трубы "+Sortament->Material->Name+" "+Sortament->Material->GOST);
    Str->Add("      Уклон: i="+AnsiString(i1000));
    Str->Add("       DH="+FloatToStr(DH));
    //if (GS) Str->Add("На участке применяется гаситель скорости");
    if (!Rash)
    {
        Str->Add("Участок не расчетный. Расход слишком маленький и не обепечивается наполнение 100% или требуется установка доп. сооружения (перепадные колодцы, нас. станция) ");
    } else
    {
        Str->Add("      Скорость: V="+AnsiString(V));
        Str->Add("      Время: T="+AnsiString(Time));
        //Str->Add("      Наполнение при пропуске ливневого расхода: h/d="+AnsiString(GetNapolnenieToQPlusQliv()));
    }
    /*if (PumpStation!=NULL)
    {
        Str->Add("На участке присутствует насосная станция");
        double l=PumpStation->GetL();
        Str->Add("  на расстоянии: "+AnsiString(l)+" метров от начала участка");
        Str->Add("  c перепадом уровней: "+AnsiString(DH)+" м.");
    } else
    if (PerepadWells!=NULL)
    {
        Str->Add("На участке присутсвуют перепадные колодцы.");
        PerepadWells->CreateReport(Str);
    } else
    if (NapWodowod!=NULL)
    {
        Str->Add("На участке присутсвуют напорные водоводы.");
        NapWodowod->CreateReport(Str);
    }*/
    Str->Add("Длина участка: "+FloatToStr(Info.Len));
    Str->Add("Отметки :");
    Str->Add("В начале трубопровода: ");
    Str->Add("      Земли: ZBeg="+FloatToStr(ZBeg));
    Str->Add("      Заглубление: h="+AnsiString(HBeg));
    Str->Add("      Лотка: Zл="+AnsiString(ZLBeg));
    Str->Add("      Шелыги: Zш="+AnsiString(ZHBeg));
    Str->Add("В конце трубопровода: ");
    Str->Add("      Земли: ZEnd="+FloatToStr(ZEnd));    
    Str->Add("      Заглубление: h="+AnsiString(HEnd));
    Str->Add("      Лотка: Zл="+AnsiString(ZLEnd));
    Str->Add("      Шелыги: Zш="+AnsiString(ZHEnd)+" "+FloatToStr(HHEnd));
}
void CTruba::SetPumpStation(double H)
{
    DH=0;
    //PumpStation=new CPumpStation(this,Hmax-H);
}
int CTruba::GetNumSortamentFrom(double Diam)
{
    int N=NSortament-Info.SortamentItem->GetNumSortament(Diam);
    return N;
}
bool CTruba::IsDiametrGood(void) // Проверяет подходит ли диаметр, и инициализирует класс под него.
{
    try
    {
    HBeg=Info.HLBeg +GetDiametr();
    bool f0=true;
    if (Sortament->Diametr.UslDiametr < MinDim) return false;
    if (Info.TROFHIL!=NULL)
    {
        f0=false;
        if (Info.TROFHIL->Sortament->Diametr.FaktDiametr<=Sortament->Diametr.FaktDiametr)
        {
            f0=true;
            double x=Info.TROFHIL->HHEnd+GetDiametr();
            HBeg=max(x,Info.HLBeg );
        } else
        if (Info.TROFLOT->Sortament->Diametr.FaktDiametr>Sortament->Diametr.FaktDiametr)
        if (Info.TROFLOT->GetNumSortamentFrom(Sortament->Diametr.FaktDiametr)<2)
        {
            f0=true;
            double x=Info.TROFLOT->HEnd;
            HBeg=max(x,Info.HLBeg);
        }
    }
    return f0;
    } catch (...)
    {
        throw("Ошибка в IsDiametrGood");
        return false;
    }
}

bool CTruba::FindDiametrAndi1000( // ищет подходящий уклон для текущего диаметра трубы, результаты записывает в NSortament и i1000
        double H1min, // Минимальное заглубление
        double H1max, // Максимальное заглубление
        bool f // если true - то ищем по минимальному заглублению, иначе по максимальному);
        )// возвращает true если все хорошо
{
    int Diam=-1;double uk=0;double strap=100000000;double q1=0;double v;
    DH=0;
    for(int i=0;Info.SortamentItem->Sortament[i]!=NULL;i++)
    {
        NSortament=i;double di=GetDiametr();
        if (!IsDiametrGood()) continue;
        //for(double uk1000=Geti1000ToHmin();uk1000<Geti1000ToHmax();uk1000=uk1000+0.5)
        //{
        double n0=Sortament->Material->n;
        //for(double k=Geti1000ToHmin();k<Geti1000ToHmax();k=k+0.003)
        //{
        //i1000=Geti1000ToHmin();//uk1000;
        v=8;//sqrt(i1000/1000)*pow(di/4,2.0/3-n0*sqrt(di/4))/n0;
        //if (v>Sortament->Material->Vmax) continue;
        //if (v<GetVmin()) v=GetVmin();
        double q0=0;Q=-10000000;double Tv;
        int j=0;
        double q5;
        do
        {
            j++;q0=Q;
            Tv=0.017*Len/v;//Sortament->GetW()*v;
            Q=pow((Tk+Tl)/(Tk+Tl+Info.Time+Tv),1.2*N-0.1)*Info.Q*GetBeta()+Info.Qdop;
            if (Q<Info.Qmax) Q=Info.Qmax;
            v=4.0*(Q/1000)/PI/sqr(di);
            //if (v<GetVmin()) v=GetVmin();
            //if (v>Sortament->Material->Vmax) v=Sortament->Material->Vmax;
            i1000=sqr(n0*v/powl(di/4,2.0/3-n0*sqrt(di/4)))*1000;
            //v=GetV();
            //q0=GetQmax();
            q5=GetQmax();
            //if (q0>Q) v=v+0.01; else
        } while (!((fabs((q0-Q)/(Q))<0.00005 && q5>Q ) || (j==100)));
        //v=GetV();
        if (di==0.6)
        {
            double h=Geti1000ToHmax();
            di=0.6;

        }
        i1000=sqr(n0*v/powl(di/4,2.0/3-n0*sqrt(di/4)))*1000;
        double Hm=Geti1000ToHmin();
        //if (j==100) break;
        if (i1000>=Geti1000ToHminimum() && i1000<=Geti1000ToHmax())
        {
            if (HEnd<Hmin+GetDiametr())
            {
                DH=double(int((Hmin+GetDiametr()-HEnd)*1000))/1000;
            } else DH=0;
            if (HBeg>Hmax) continue;
            double s=(HBeg+HEnd)*Len/2;
            if (s<strap)
            if (v>=GetVmin() && v<=Sortament->Material->Vmax)
            {
                Diam=i;
                strap=s;
                uk=i1000;
                q1=Q;
            }
        }
    }
    if (Diam>-1)
    {
        NSortament=Diam;
        i1000=uk;
        Q=q1;
        hd=1;
        Time=Info.Time+0.017*Len/GetV();
        IsDiametrGood();DH=0;
        if (HEnd<Hmin+GetDiametr())
        {
            DH=double(int((Hmin+GetDiametr()-HEnd)*1000))/1000;
        } else DH=0;
        return true;
    } else
    {
        NSortament=-1;
        Q=Info.Q;
        return false;
    }
}

void CTruba::SetWells(double H) // Установка перепадных колодцев с падением заглубления по лотку до H м
{
    DH=0;
    //DH=HEnd-H;
    //PerepadWells=new CPerepadWells(this);
}
void CTruba::SetNapWodowod(void) // Установка напорных водоводов.
{
    DH=0;
    //NapWodowod=new CNapWodowod(this);
}
double CTruba::GetQfromHD(double hd)
{
    double a=2.0*ArcCos(2.0*MaxNapoln(Sortament->Diametr.UslDiametr)-1);
    double w=GetW(hd);
    double r=(Sortament->Diametr.FaktDiametr/1000)/4*((PI*2-a+sin(a))/(PI*2-a));
    double n=Sortament->Material->n;
    double y=2.5*sqrt(n)-0.13-0.75*sqrt(r)*(sqrt(n)-0.1);
    double v=pow(r,y)/n*sqrt(r*i1000/1000);
    return 1000.0*w*v;
}
double CTruba::GetZmest(double Len) // Возвращает отметку земли на расстоянии Len от начала участка
{
    return ZBeg-Geti1000mest()/1000*Len;
}
double CTruba::GetNapolnenieToQPlusQliv(void)
{
    double Q0=Q,HD=hd;
    Q=Q+Qliv;
    ToNapolnenie();
    double ret=hd;
    hd=HD;Q=Q0;
    return ret;
}
AnsiString CTruba::CreateLineTable(void) // Создание отчеста в виде строки таблицы
{
    AnsiString answ="";
    answ=Format("%7.1f|",ARRAYOFCONST((Len)))+
           Format("%7.1f|",ARRAYOFCONST((Q)))+
           Format("%6.0f |",ARRAYOFCONST(((double)Sortament->Diametr.UslDiametr)))+
           Format("%6.1f|",ARRAYOFCONST((i1000)));
           if (Rash) answ=answ+Format("%8.2f|",ARRAYOFCONST((V))); else answ=answ+"   -    |";
           if (Rash) answ=answ+Format("  %5.2f|",ARRAYOFCONST((hd))); else answ=answ+"   -   |";
           answ=answ+Format("%6.2f|",ARRAYOFCONST((ZBeg)))+
           Format("%6.2f|",ARRAYOFCONST((ZHBeg)))+
           Format("%6.2f|",ARRAYOFCONST((ZLBeg)))+
           Format("%6.2f||",ARRAYOFCONST((HBeg)))+
           Format("%6.2f|",ARRAYOFCONST((ZEnd)))+
           Format("%6.2f|",ARRAYOFCONST((ZHEnd)))+
           Format("%6.2f|",ARRAYOFCONST((ZLEnd)))+
           Format("%6.2f|",ARRAYOFCONST((HEnd)));

    return answ;

}
void CTruba::CreateSpecialReport(TStrings *Str) // Создание отчета об инженерных конструкциях на трубе
{
    if (GS)  Str->Add("       |На участке применяется гаситель скорости       |      |      |      |      ||      |      |      |      |");
    //if (PumpStation!=NULL) PumpStation->CreateSpecialReport(Str);
    //else
    //if (PerepadWells!=NULL) PerepadWells->CreateSpecialReport(Str);
    //else
    //if (NapWodowod!=NULL) NapWodowod->CreateSpecialReport(Str);
}
AnsiString CTruba::CreateLineTableSmall(void) // Создание отчета об параметрах трубопровода без отметок
{
    AnsiString answ="";
    /*
    answ=Format("%7.1f|",ARRAYOFCONST((Len)))+
            Format("%7.2f|",ARRAYOFCONST((Q)))+
            Format("%6.0f |",ARRAYOFCONST(((double)Sortament->Diametr.UslDiametr)));
            if (NapWodowod==NULL) answ=answ+Format("%6.1f|",ARRAYOFCONST((i1000))); else answ=answ+"   -  |";
            if (Rash) answ=answ+Format("%8.2f|",ARRAYOFCONST((V))); else answ=answ+"   -    |";
            if (Rash) answ=answ+Format("  %5.2f|",ARRAYOFCONST((hd))); else answ=answ+"   -   |";
            answ=answ+Format("%6.2f|",ARRAYOFCONST((Qliv)));
            if (Rash && (NapWodowod==NULL)) answ=answ+Format("%8.2f|",ARRAYOFCONST((GetQfromHD(0.95)))); else answ=answ+"    -   |";
            if (GS) answ=answ+"ГС "; else answ=answ+"   ";
            if (PumpStation!=NULL) answ=answ+PumpStation->CreateLineTableSmall();
            else
            if (PerepadWells!=NULL) answ=answ+PerepadWells->CreateLineTableSmall();
            else
            if (NapWodowod!=NULL) answ=answ+NapWodowod->CreateLineTableSmall();
            else answ=answ+"           |";
    */
    return answ;
}
AnsiString CTruba::CreateOtm(void) // Создание строки таблицы отметок
{
 AnsiString a;
 if (i1000<0) a="   -  |"; else a=Format("%5.2f |",ARRAYOFCONST((i1000/1000*Len)));
 return
      a+
      Format("%6.2f|",ARRAYOFCONST((ZBeg)))+
      Format("%6.2f|",ARRAYOFCONST((ZEnd)))+
      Format("%6.2f|",ARRAYOFCONST((ZLBeg)))+
      Format("%6.2f|",ARRAYOFCONST((ZLEnd)))+
      Format("%6.2f|",ARRAYOFCONST((ZHBeg)))+
      Format("%6.2f|",ARRAYOFCONST((ZHEnd)))+
      Format("%5.2f|",ARRAYOFCONST((HBeg)))+
      Format("%5.2f|",ARRAYOFCONST((HEnd)))+
      Format(" %-9s  |",ARRAYOFCONST((Sortament->Material->GOST))
      );
}
void CTruba::CreateOtmSoor(TStrings *Str) //Создание отметок земли технических сооружений
{

}
//---------------------------------------------------------------------------
//
// CSortament
//
CSortament::CSortament(CDiametr Diam,CMaterial *Mat)
{
    Diametr=Diam;
    Material=Mat;
}
double CSortament::GetVmin(void) // Возвращает минимальную скорость для данного сортамента
{
    try {
    double R=GetR();
    return 1.7*Power(R,1/(3.5+0.5*R));
    } catch (...)
    {
        return 0;
    }
}
double CSortament::GetQmin(void) // Возвращает минимальный расход
{
    return 1000*GetW()*GetVmin();
}
double CSortament::Geti1000min(void) // Возвращает минимальный уклон
{
    double R=GetR();
    double n=Material->n;
    double y=2.5*sqrt(n)-0.13-0.75*sqrt(R)*(sqrt(n)-0.1);
    double n0=3.5+0.5*R;
    return 2465*sqr(n)*pow(R,(2/n0)-2*y-1);
}
double CSortament::Geti1000(double Q) // Возвращает уклон трубы для данного диаметра при расходе Q и максимальном наполнении
{
    return sqr(Q/GetQmin())*Geti1000min();
}
double CSortament::GetW(void) // Возвращает площадь живого сечения трубы
{
    double arad=GetAlfa();
    double adeg=arad*180/M_PI;
    double d=Diametr.FaktDiametr/1000;
    return sqr(d)/4*(M_PI*(1-adeg/360)+sin(arad)/2);
}
double CSortament::GetAlfa(void) // Возвращает угол
{
    return 2*ArcCos(2*MaxNapoln(Diametr.FaktDiametr)-1);
}
double CSortament::GetR(void) // Возвращает гидравлический радиус
{
    double arad=GetAlfa();
    double adeg=arad*180/M_PI;
    double d=Diametr.FaktDiametr/1000;
    return d/4*(1+sin(arad)/(2*M_PI*(1-adeg/360)));
}
//
// CSortamentItem
//
CSortamentItem::CSortamentItem(AnsiString Nam,CSortament **Sort)
{
    Name=Nam;Sortament=Sort;
}
int CSortamentItem::GetNumSortament(double Diam) // Возвращает номер наиболее близкого сортамента к диаметру Diam
{
    for(int i=0;Sortament[i]!=NULL;i++)
    {
        if (Diam<Sortament[i]->Diametr.FaktDiametr) return i;
    }
    return -1;
}


extern double MaxNapoln(
    double Diam // Условный диаметр трубы,мм
) // Возвращает наполнение для конкретного диаметра трубы.
{
    return 1;
    /*if (Diam>=1000) return 1;
    if (Diam>=450) return 1;
    if (Diam>=300) return 1;
    return 0.6;*/
}

double sqr(double X) // Возвращает x^2
{
    return X*X;
}

double step(double x,double y)
{
    return exp(log(x)*y);
}

//
// Сортаменты
//
CSortamentItem *SortamentName[]={
    new CSortamentItem("Асбестоцементные трубы ГОСТ 1839 и ГОСТ 539",SAsbest),
    new CSortamentItem("Керамические трубы ГОСТ 286",SKeramika),
    new CSortamentItem("Железобетонные безнапорные трубы ГОСТ 6482",SBeton),
    new CSortamentItem("Керамические + Железобетонные + Чугун",SKeramikaBeton),
    new CSortamentItem("Стальные электросварные",SStal),
  
NULL
};

CSortament *SAsbest[]={
    new CSortament(CDiametr(100,100),&MAsbest1),
    new CSortament(CDiametr(150,141),&MAsbest1),
    new CSortament(CDiametr(200,189),&MAsbest1),
    new CSortament(CDiametr(250,244),&MAsbest2),
    new CSortament(CDiametr(300,279),&MAsbest1),
    new CSortament(CDiametr(350,334),&MAsbest2),
    new CSortament(CDiametr(400,368),&MAsbest1),
    new CSortament(CDiametr(500,473),&MAsbest2),
NULL
}; // Асбестоцементные трубы
CSortament *SKeramika[]={
    new CSortament(CDiametr(150,150),&MKeramika),
    new CSortament(CDiametr(200,200),&MKeramika),
    new CSortament(CDiametr(250,250),&MKeramika),
    new CSortament(CDiametr(300,300),&MKeramika),
    new CSortament(CDiametr(350,350),&MKeramika),
    new CSortament(CDiametr(400,400),&MKeramika),
    new CSortament(CDiametr(450,450),&MKeramika),
    new CSortament(CDiametr(500,500),&MKeramika),
    new CSortament(CDiametr(550,550),&MKeramika),
    new CSortament(CDiametr(600,600),&MKeramika),
NULL
}; // Керамические трубы
CSortament *SBeton[]={
    new CSortament(CDiametr(400,400),&MBeton),
    new CSortament(CDiametr(500,500),&MBeton),
    new CSortament(CDiametr(600,600),&MBeton),
    new CSortament(CDiametr(800,800),&MBeton),
    new CSortament(CDiametr(1000,1000),&MBeton),
    new CSortament(CDiametr(1200,1200),&MBeton),
    new CSortament(CDiametr(1400,1400),&MBeton),
    new CSortament(CDiametr(1600,1600),&MBeton),
    new CSortament(CDiametr(2000,2000),&MBeton),
    new CSortament(CDiametr(2400,2400),&MBeton),
NULL
}; // Железобетонные трубы
CSortament *SKeramikaBeton[]={
    new CSortament(CDiametr(150,150),&MKeramika),
    new CSortament(CDiametr(200,200),&MKeramika),
    new CSortament(CDiametr(250,250),&MKeramika),
    new CSortament(CDiametr(300,300),&MKeramika),
    new CSortament(CDiametr(350,350),&MKeramika),
    new CSortament(CDiametr(400,400),&MKeramika),
    new CSortament(CDiametr(500,500),&MBeton),
    new CSortament(CDiametr(600,600),&MBeton),
    new CSortament(CDiametr(700,703),&MChug),
    new CSortament(CDiametr(800,800),&MBeton),
    new CSortament(CDiametr(900,903.4),&MChug),
    new CSortament(CDiametr(1000,1000),&MBeton),
    new CSortament(CDiametr(1200,1200),&MBeton),
    new CSortament(CDiametr(1400,1400),&MBeton),
    new CSortament(CDiametr(1600,1600),&MBeton),
    new CSortament(CDiametr(2000,2000),&MBeton),
    new CSortament(CDiametr(2400,2400),&MBeton),
NULL
}; // Керамика + Бетон + Чугун
CSortament *SStal[]={
    new CSortament(CDiametr(65,67.6),&MStal),
    new CSortament(CDiametr(80,83.6),&MStal),
    new CSortament(CDiametr(100,103),&MStal),
    new CSortament(CDiametr(125,128.2),&MStal),
    new CSortament(CDiametr(150,153.4),&MStal),
    new CSortament(CDiametr(200,203.6),&MStal),
    new CSortament(CDiametr(250,254),&MStal),
    new CSortament(CDiametr(300,304.4),&MStal),
    new CSortament(CDiametr(350,354.6),&MStal),
    new CSortament(CDiametr(400,404),&MStal),
    new CSortament(CDiametr(500,503.6),&MStal),
    new CSortament(CDiametr(600,603.4),&MStal),
    new CSortament(CDiametr(700,703),&MStal),
    new CSortament(CDiametr(800,803.6),&MStal),
    new CSortament(CDiametr(900,903.4),&MStal),
    new CSortament(CDiametr(1000,1003),&MStal),
NULL
}; // Стальные электросварные


// Данные о максимальном количестве осадков
AnsiString NameMest[]={"Хабаровск",""};
double MD[]={99,0};

