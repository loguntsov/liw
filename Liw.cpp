//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Liw.h"
#include "MathMethod.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//
// CGeoSegment
//

CGeoSegment::CGeoSegment(GeoSegmentInform Information)
{
    Truba=NULL;
    Info=Information;
    PEnd->AddBefore(this);
}
CGeoSegment::~CGeoSegment()
{
    PEnd->DeleteBefore(this);
    delete Truba;
}
bool CGeoSegment::IsCalculated(void)
{
    return Truba!=NULL;
}
void CGeoSegment::Calculation(void)
{
    if (IsCalculated()) return;
    PBeg->Calculation();
    TrubaInform a;
    a.SortamentItem = Info.SortamentItem;
    a.Len = Info.Len;
    a.ZBeg = PBeg->z;
    a.ZEnd = PEnd->z;
    a.HLBeg = Info.HBeg;
    a.Qdop = PBeg->q0;
    a.Q = PBeg->q+Info.Q;
    a.VVH = PBeg->v;
    a.Qmax=PBeg->qmax;
    a.Time = PBeg->Time;
    a.TROFHIL = PBeg->GetTrubaOfMinHil();
    a.TROFLOT = PBeg->GetTrubaOfMinLot();
    a.NSegment = Info.NSegment;
    Truba=new CTruba(a);//SortamentItem,Len,PBeg->z,PEnd->z,HBeg,,PBeg->v,PBeg->qliv,PBeg->GetTrubaOfMinHil(),PBeg->GetTrubaOfMinLot());
    Truba->ToGetSortament();
    if (Truba->HEnd>H0max) Truba->SetPumpStation(Hmin+Truba->GetDiametr());
    if (Truba->HEnd>Hmax && PBeg->h>Hmax)
    {
        delete Truba;
        for(int i=0;i<PBeg->CountBefore();i++)
        {
            if (PBeg->Items(i)->Truba->HEnd>Hmax)
                PBeg->Items(i)->Truba->SetPumpStation(Hmin+PBeg->Items(i)->Truba->GetDiametr());
        }
        PBeg->Calculation();
        TrubaInform b;
        b.SortamentItem = Info.SortamentItem;
        b.Qmax=PBeg->qmax;
        b.Len = Info.Len;
        b.ZBeg = PBeg->z;
        b.ZEnd = PEnd->z;
        b.HLBeg = Info.HBeg;
        b.Qdop = Info.Q+PBeg->q0;
        b.VVH = PBeg->v;
        b.Time = PBeg->Time;
        b.TROFHIL = PBeg->GetTrubaOfMinHil();
        b.TROFLOT = PBeg->GetTrubaOfMinLot();
        b.Q = PBeg->q+Info.Q;
        b.NSegment = Info.NSegment;
        Truba=new CTruba(b);
        Truba->ToGetSortament();
    }
}
void CGeoSegment::CreateReport(TStrings *Str)
{
    if (IsCalculated())
    {
        Str->Add("Участок №"+IntToStr(Info.NSegment)+" : "+Info.Name);
        Truba->CreateReport(Str);
        Str->Add("--------------------------------------------------");
    }
}
AnsiString CGeoSegment::CreateLineTable(void)
{
    if (IsCalculated()) return Format("%7s|",ARRAYOFCONST((Info.Name.c_str())))+Truba->CreateLineTable();
    return "";
}
void CGeoSegment::CreateSpecialReport(TStrings *Str) // Создание отчета об инженерных конструкциях на участке
{
    if (IsCalculated())
    {
        Truba->CreateSpecialReport(Str);
        Str->Add("-----------------------------------------------------------------------------------------------------------------");
    }
}

AnsiString CGeoSegment::CreateLineTableSmall(void)
{
    if (IsCalculated()) return Format("|%7s|",ARRAYOFCONST((Info.Name.c_str())))+Truba->CreateLineTableSmall();
    return "";
}
void CGeoSegment::CreateReportOtm(TStrings *Str) // Создание отчета отметок об участке
{
    if (IsCalculated())
    {
           Str->Add(Format("|%7s|",ARRAYOFCONST((Info.Name.c_str())))+Truba->CreateOtm());
           Truba->CreateOtmSoor(Str);
    }
}
CGeoPoint * CGeoSegment::GetPBeg(void)
{
    return Info.PBeg;
}
CGeoPoint * CGeoSegment::GetPEnd(void)
{
    return Info.PEnd;
}

//
// CGeoPoint
//
CGeoPoint::CGeoPoint(
        double Z, // Геометричекая высота точки
        double Q0 // Сосредоточенный расход м3/ч
        )
{
    z=Z;
    q0=Q0/3.6;
    SegmentBefore=new TList();
    TheEndPoint=false;
    v=0;q=0;
}
CGeoPoint::~CGeoPoint()
{
    for(int i=0;i<SegmentBefore->Count;i++)
        delete Items(i);
    delete SegmentBefore;
}
CGeoSegment * CGeoPoint::Items(int i)
{
    return (CGeoSegment *) SegmentBefore->Items[i];
}
void CGeoPoint::AddBefore(CGeoSegment *Seg)
{
    SegmentBefore->Add(Seg);
}
void CGeoPoint::DeleteBefore(CGeoSegment *Seg)
{
    for(int i=0;i<SegmentBefore->Count;i++)
        if(Items(i)==Seg)
        {
            SegmentBefore->Delete(i);
            break;
        }
}
void CGeoPoint::Calculation(void)
{
    q=0;v=0;h=0;Time=0;
    qmax=0;int item=-1;
    for(int i=0;i<SegmentBefore->Count;i++)
    {
        if (!Items(i)->IsCalculated())
        {
            Items(i)->Calculation();
            if (TheEndPoint)
                if (Items(i)->Truba->HEnd>Hmax)
                    Items(i)->Truba->SetPumpStation(Hmin+Items(i)->Truba->GetDiametr());
        }
        q=q+Items(i)->Truba->Info.Q;
        if (Items(i)->Truba->Q>qmax)
        {
            qmax=Items(i)->Truba->Q;item=i;
        }
        if (Items(i)->Truba->Time>Time) Time=Items(i)->Truba->Time;
        double vtr=Items(i)->Truba->V;
        double htr=Items(i)->Truba->HEnd;
        //if (v<vtr) v=vtr;
        if (h<htr) h=htr;
    }
    if (item>-1) v=Items(item)->Truba->V; else v=100000000;
    // Установка гасителей скорости
    for(int i=0;i<SegmentBefore->Count;i++)
    {
        if (int(Items(i)->Truba->V*1000)>int(v*1000)) Items(i)->Truba->GS=true;
    }
    //q=qmax;
}
int CGeoPoint::CountBefore(void)
{
    return SegmentBefore->Count;
}
CTruba * CGeoPoint::GetTrubaOfMinHil(void)
{
    if (SegmentBefore->Count==0) return NULL;
    double x=100000000;CTruba *Tr=NULL;
    for(int i=0;i<SegmentBefore->Count;i++)
    {
        if (Items(i)->Truba->ZHEnd<x)
        {
            x=Items(i)->Truba->ZHEnd;Tr=Items(i)->Truba;
        }
    }
    return Tr;
}
CTruba * CGeoPoint::GetTrubaOfMinLot(void)
{
    if (SegmentBefore->Count==0) return NULL;
    double x=100000000;CTruba *Tr=NULL;
    for(int i=0;i<SegmentBefore->Count;i++)
    {
        if (Items(i)->Truba->ZLEnd<x)
        {
            x=Items(i)->Truba->ZLEnd;Tr=Items(i)->Truba;
        }
    }
    return Tr;

}

//
//
//

double GetKnerawn(double q) // Возвращает общий коэффициент неравномерности для данного расхода
{
    double x[]={5.0,10.0,20.0,50.0,100.0,300.0,500.0,1000.0,5000.0,100000000.0};
    double y[]={2.5,2.1,1.9,1.7,1.6,1.55,1.5,1.47,1.44,1.44};
    if (q<=5) return 2.5;
    if (q>=5000) return 1.44;
    LinIntr a(x,y,10);
    return a.GetY(q);
}

