//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ChildWin.h"
#include "Liw.h"
#include "Main.h"
#include "DiskSystem.h"
#include "UnitExec.h"
#include "Math.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
const int SaveVer=0;
//---------------------------------------------------------------------


__fastcall TMDIChild::TMDIChild(TComponent *Owner)
	: TForm(Owner)
{
    x=1;y=1;f=true;
    IsChange=false;
}
//---------------------------------------------------------------------
void __fastcall TMDIChild::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree;
    if (Report!=NULL) Report->ChildWin=NULL;
}
//---------------------------------------------------------------------
void __fastcall TMDIChild::FormCreate(TObject *Sender)
{
    for(int i=0;SortamentName[i]!=NULL;i++)
    {
        SortamentBox->Items->Add(SortamentName[i]->Name);
        SegmentSortamentBox->Items->Add(SortamentName[i]->Name);
    }
    SegmentSortamentBox->ItemIndex=0;
    GeodezicCells->Cells[0][0]="№";
    GeodezicCells->Cells[1][0]="Отметка земли";
    GeodezicCells->Cells[2][0]="Сосредоточенный расход";
    GeodezicCells->Cells[0][1]="1";
    GeodezicCells->Cells[0][2]="2";
    SegmentCells->Cells[0][0]="№ уч-ка";
    SegmentCells->Cells[0][1]="1";
    SegmentCells->Cells[1][0]="Начальная точка,м";
    SegmentCells->Cells[2][0]="Конечная точка,м";
    SegmentCells->Cells[3][0]="Длина,м";
    SegmentCells->Cells[4][0]="Заглубление,м";
    SegmentCells->Cells[5][0]="Кол-во дождеприемников";
    SegmentCells->Cells[6][0]="Сортамент";
    #ifdef IsDemo
        UpDown->Max = 15;
    #endif
    MDIReport=NULL;
    for(int i=0;NameMest[i]!="";i++)
    {
        MdComboBox->Items->Add(NameMest[i]);
    }
    ComboType->ItemIndex=0;
    Report=NULL;
}
//---------------------------------------------------------------------------


void __fastcall TMDIChild::Calculate(void)
{
    MinDim=0;
    //if (ComboType->ItemIndex>0) MinDim=200; else MinDim=0;
    int nSegment=NumberSegment->Text.ToInt();
    #ifdef IsDemo
    if (nSegment>15)
    {
        MessageBox(Handle, "Данная программа является демо версией.Расчет больше чем 15 участков ограничен.Для снятия этого ограничения обратитесь к автору программы.","", MB_OK | MB_ICONWARNING);
        Abort();
    }
    #endif
    TFormExec *ExecForm=new TFormExec(this);
    ExecForm->ProgressBar1->Max=nSegment*3-1;
    ExecForm->Show();
    Hmin=HminEdit->Text.ToDouble();
    Hmax=HmaxEdit->Text.ToDouble();
    // Исходные данные о местности
    double q20,p,f0,gamma,zs,tk,tl,m,fe;
    q20=q20Edit->Text.ToDouble();
    p=pEdit->Text.ToDouble();
    f0=F0Edit->Text.ToDouble();N=f0;
    gamma=GammaEdit->Text.ToDouble();
    m=MEdit->Text.ToDouble();
    zs=ZSEdit->Text.ToDouble();
    tk=TkEdit->Text.ToDouble();Tk=tk;
    tl=TlEdit->Text.ToDouble();Tl=tl;
    fe=FEEdit->Text.ToDouble();
    double A=pow(20,f0)*q20*pow(1+log10(p)/log10(m),gamma);
    double qsr=(pow(A,1.2)*zs*fe)/((1.0+0.001*pow(fe,2.0/3.0))*pow(tk,1.2*f0-0.1));
    Label20->Caption="Qsr="+FloatToStr(qsr);
    H0max=Hmax*(1.00+dHmaxEdit->Text.ToDouble()/100);
    CSortamentItem * DefaultSortamentItem=SortamentName[SortamentBox->ItemIndex];
    CGeoPoint **GeoPoints=new CGeoPoint * [nSegment+1];
    CGeoSegment **GeoSegments=new CGeoSegment * [nSegment];
    for(int i=0;i<nSegment+1;i++)
    {
        double Z=GeodezicCells->Cells[1][i+1].ToDouble();
        double q0=0;
        if (GeodezicCells->Cells[2][i+1]!="")
            q0=GeodezicCells->Cells[2][i+1].ToDouble();
        GeoPoints[i]=new CGeoPoint(Z,q0);
        ExecForm->Next();
    }
    CSortamentItem *SortamentItem=NULL;
    bool *IsBeginGeoPoint=new bool [nSegment+1];
    for(int i=0;i<nSegment+1;i++) IsBeginGeoPoint[i]=false;
    int SumDogd=0;
    int NDogd=0;
    for(int i=0;i<nSegment;i++)
    {
        if (SegmentCells->Cells[5][i+1]!="") NDogd=SegmentCells->Cells[5][i+1].ToDouble(); else NDogd=0;
        SumDogd+=NDogd;
    }
    qsr=qsr/SumDogd;
    Label20->Caption="Qsr="+FloatToStr(qsr);
    for(int i=0;i<nSegment;i++)
    {
        int BegGeoPoint=SegmentCells->Cells[1][i+1].ToInt()-1;
        IsBeginGeoPoint[BegGeoPoint]=true;
        int EndGeoPoint=SegmentCells->Cells[2][i+1].ToInt()-1;
        double Len=SegmentCells->Cells[3][i+1].ToDouble();
        double HBeg=0;
        if (SegmentCells->Cells[4][i+1]!="") HBeg=SegmentCells->Cells[4][i+1].ToDouble();
        for(int j=0;SortamentName[j]!=NULL;j++)
        {
            if (SegmentCells->Cells[6][i]==SortamentName[j]->Name)
            {
                SortamentItem=SortamentName[j];break;
            } else SortamentItem=DefaultSortamentItem;
        }
        GeoSegmentInform a;
        a.SortamentItem = SortamentItem;
        a.PBeg = GeoPoints[BegGeoPoint];
        a.PEnd = GeoPoints[EndGeoPoint];
        a.Len = Len;
        a.HBeg = HBeg;
        a.NSegment = i;
        if (SegmentCells->Cells[5][i+1]!="") NDogd=SegmentCells->Cells[5][i+1].ToDouble(); else NDogd=0;
        a.Q = NDogd*qsr;
        a.Name = AnsiString(BegGeoPoint+1)+" x "+AnsiString(EndGeoPoint+1);
        GeoSegments[i]=new CGeoSegment(a);
    }
    int n=0,NumSeg=0;
    for(int i=0;i<nSegment+1;i++)
    {
        ExecForm->Next();
        if (!IsBeginGeoPoint[i])
        {
            n++;NumSeg=i;
        }
    }
    if (n==1)
    {
        GeoPoints[NumSeg]->Calculation();
        Report=new TMDIReport(Application);
        TStrings *Str=Report->RichBox->Lines;
        TRichEdit *Rich=Report->RichBox;
        Rich->Paragraph->LeftIndent = 30;
        //Rich->Paragraph->RightIndent = 30;
        Rich->Paragraph->FirstIndent = 30;
        switch(3)
        {
            case 3 :
                for(int i=0;i<nSegment;i++)
                {
                    GeoSegments[i]->CreateReport(Str);                    
                }
            break;
            case 0 :
            Str->Add("------------------------------------------------------------------------------------------------------------------");
            Str->Add("Наиме- | Длина | Расход|Диаметр|Уклон |Скорость|  h/d  |                        Отметки земли                   |");
            Str->Add("нование|   м   |  л/с  |  мм   |x1000 |  м/с   |   %   |       в начале            ||    в конце                |");
            Str->Add("участка|       |       |       |      |        |       |земля |лоток |шелыга|  H,м ||земля |лоток |шелыга| H,м  |");
            Str->Add("------------------------------------------------------------------------------------------------------------------");
            for(int i=0;i<nSegment;i++)
            {
                Str->Add(GeoSegments[i]->CreateLineTable());
                GeoSegments[i]->CreateSpecialReport(Str);
                ExecForm->Next();
            }
            break;
            case 1 :
            Rich->Paragraph->Alignment=taCenter;
            Rich->SelAttributes->Height=12;
            Rich->Lines->Add("Гидравлический расчет канализационной сети");
            Rich->Paragraph->Alignment=taLeftJustify;
            Str->Add("----------------------------------------------------------------------------------------");
            Str->Add("| Номер | Длина | Расход|Диаметр|Уклон |Скорость|  h/d  |Расход| Расход |  Примечание  |");
            Str->Add("|участка|   м   |  л/с  |  мм   |x1000 |  м/с   |       |инфил.|  при   |              |");
            Str->Add("|       |       |       |       |      |        |       |  л/с |h/d=0.95|              |");
            Str->Add("|-------|-------|-------|-------|------|--------|-------|------|--------|--------------|");
            for(int i=0;i<nSegment;i++)
            {
                Str->Add(GeoSegments[i]->CreateLineTableSmall());
                ExecForm->Next();
            }
            Str->Add("----------------------------------------------------------------------------------------");
            Str->Add("Примечание:");
            Str->Add("ГС - гаситель скорости");
            Str->Add("ПК ## - перепадные колодцы в количестве ## штук");
            Str->Add("НСП ## - насосная станция подкачки, установленная на расстоянии ## от начала уч-ка");
            Str->Add("НВ ## - напорные водоводы, в количестве ## штук + НСП устанавливаемая в начале участка");
            Str->Add("");
            Rich->SelAttributes->Height=12;
            Rich->Paragraph->Alignment=taCenter;
            Str->Add("Отметки по участкам");
            //Rich->Paragraph->Alignment=taLeftJustify;
            Str->Add("-----------------------------------------------------------------------------------");
            Str->Add("| Номер |      |                      Отметки                        |  Материал  |");
            Str->Add("|участка| h=i*l|    земля         лоток         шелыга    заглубление| Примечание |");
            Str->Add("|       |      | нач  |  кон | нач  | кон  | нач  | кон  | нач | кон |            |");
            Str->Add("|-------|------|------|------|------|------|------|------|-----|-----|------------|");
            for(int i=0;i<nSegment;i++)
            {
                GeoSegments[i]->CreateReportOtm(Str);
                ExecForm->Next();
            }
            Str->Add("-----------------------------------------------------------------------------------");
            //Rich->Paragraph->Alignment=taRightJustify;
            //Report->Visible=false;
            break;
        }
        Report->Visible=true;
        Report->ChildWin = this;
        this->Report=Report;
    }
    else
    {
       // Ошибка
        ShowMessage("Ошибка в топологии сети!!!.Или где-то еще :)");
    }
    for(int i=0;i<nSegment;i++) delete GeoSegments[i];
    for(int i=0;i<nSegment-1;i++) delete GeoPoints[i];
    delete GeoSegments;
    delete GeoPoints;
    delete ExecForm;
}
void TMDIChild::LoadSegmentData(int ACol,int ARow)
{
    x=ACol;y=ARow;
    f=false;
    BegGeoPointBox->Text=SegmentCells->Cells[1][ARow];
    EndGeoPointBox->Text=SegmentCells->Cells[2][ARow];
    SegmentLen->Text=SegmentCells->Cells[3][ARow];
    SegmentHBeg->Text=SegmentCells->Cells[4][ARow];
    NDogdEdit->Text=SegmentCells->Cells[5][ARow];
    for(int i=0;i<SegmentSortamentBox->Items->Count;i++)
    {
        if (SegmentSortamentBox->Items->Strings[i]==SegmentCells->Cells[6][ARow])
        {
            SegmentSortamentBox->ItemIndex=i;break;
        } else SegmentSortamentBox->ItemIndex=0;
    }
    f=true;
}
void TMDIChild::DownloadSegmentData(void)
{
    f=false;
    SegmentCells->Cells[1][y]=BegGeoPointBox->Text;
    SegmentCells->Cells[2][y]=EndGeoPointBox->Text;
    SegmentCells->Cells[3][y]=SegmentLen->Text;
    SegmentCells->Cells[4][y]=SegmentHBeg->Text;
    SegmentCells->Cells[5][y]=NDogdEdit->Text;
    SegmentCells->Cells[6][y]=SegmentSortamentBox->Text;
    f=true;
}
//---------------------------------------------------------------------------


void __fastcall TMDIChild::SegmentCellsSelectCell(TObject *Sender,
      int ACol, int ARow, bool &CanSelect)
{
    LoadSegmentData(ACol,ARow);
    //DownloadSegmentData();
}
//---------------------------------------------------------------------------



void __fastcall TMDIChild::SegmentCellsSetEditText(TObject *Sender,
      int ACol, int ARow, const AnsiString Value)
{
    LoadSegmentData(ACol,ARow);
}
//---------------------------------------------------------------------------

void __fastcall TMDIChild::BegGeoPointBoxChange(TObject *Sender)
{
    if (f) DownloadSegmentData();
}
//---------------------------------------------------------------------------

void __fastcall TMDIChild::SpeedButton1Click(TObject *Sender)
{
    PageControl1->ActivePage=TabSheet2;        
}
//---------------------------------------------------------------------------

void __fastcall TMDIChild::UpDownChanging(TObject *Sender,
      bool &AllowChange)
{
    GeodezicCells->RowCount=UpDown->Position+2;

    for(int i=0;i<UpDown->Position+1;i++)
    {
        GeodezicCells->Cells[0][i+1]=i+1;
    }
    SegmentCells->RowCount=UpDown->Position+1;
    for(int i=1;i<SegmentCells->RowCount;i++)
    {
        SegmentCells->Cells[0][i]=i;
    }
    BegGeoPointBox->Items->Clear();
    EndGeoPointBox->Items->Clear();
    for(int i=1;i<UpDown->Position+2;i++)
    {
        BegGeoPointBox->Items->Add(i);
        EndGeoPointBox->Items->Add(i);
    }

}
//---------------------------------------------------------------------------


void __fastcall TMDIChild::NumberSegmentChange(TObject *Sender)
{
    bool f=true;
    UpDownChanging(Sender,f);
}
//---------------------------------------------------------------------------
void TMDIChild::FileSave(void) // Запись исходных данных
{
    if (FileName=="") FileSaveAs();
    else
    {
        Caption=FileName;
        // Дальше идет код сохранения данных формы
        TFileStream *a=new TFileStream(FileName,fmCreate|fmOpenWrite);
        DiskStream *S=new DiskStream(a);
        S->Write("LIW");
        S->Write(SaveVer); // Номер версии сохранения, должен увеличиваться с добавлением новых данных
        int nSegment=UpDown->Position; // Количество участков
        S->Write(nSegment);
        S->Write(SortamentBox->ItemIndex);
        S->Write(HminEdit->Text.ToDouble());
        S->Write(HmaxEdit->Text.ToDouble());
        S->Write(dHmaxEdit->Text.ToDouble());
        // Данные о местности
        S->Write(q20Edit->Text.ToDouble());
        S->Write(pEdit->Text.ToDouble());
        S->Write(F0Edit->Text.ToDouble());
        S->Write(GammaEdit->Text.ToDouble());
        S->Write(MEdit->Text.ToDouble());
        S->Write(ZSEdit->Text.ToDouble());
        S->Write(TkEdit->Text.ToDouble());
        S->Write(TlEdit->Text.ToDouble());
        S->Write(FEEdit->Text.ToDouble());

        for(int i=0;i<nSegment+1;i++)
        {
            S->Write(GeodezicCells->Cells[1][i+1]);
            S->Write(GeodezicCells->Cells[2][i+1]);
        }
        for(int i=0;i<nSegment;i++)
        {
            S->Write(SegmentCells->Cells[1][i+1]);
            S->Write(SegmentCells->Cells[2][i+1]);
            S->Write(SegmentCells->Cells[3][i+1]);
            S->Write(SegmentCells->Cells[4][i+1]);
            S->Write(SegmentCells->Cells[5][i+1]);
            S->Write(SegmentCells->Cells[6][i+1]);
        }
        S->Write(ComboType->ItemIndex);
        delete S;
        delete a;
    }
}
void TMDIChild::FileSaveAs(void) // Запись исходных данных как ...
{
    if (SaveDialog->Execute())
    {
        FileName=SaveDialog->FileName;
        FileSave();
    }
}
void TMDIChild::FileLoad(AnsiString File) // Открытие исходных данных
{
    FileName=File;
    Caption=FileName;
    // Здесь идет код загрузки данных из файла
    TFileStream *a=new TFileStream(FileName,fmOpenRead);
    DiskStream *S=new DiskStream(a);
    AnsiString Format=S->ReadAnsiString();
    if (Format!="LIW")
    {
        ShowMessage("Файл не является файлом данных ливнеыфх сетей");
        Abort();
    }
    int LoadVer=S->ReadInt(); // Номер версии сохранения, должен увеличиваться с добавлением новых данных
    int nSegment=S->ReadInt();
    NumberSegmentChange(NULL);    
    //UpDown->Position=nSegment;
    NumberSegment->Text=nSegment;
    UpDown->Position = nSegment;
    SortamentBox->ItemIndex=S->ReadInt();
    HminEdit->Text=S->ReadDouble();
    HmaxEdit->Text=S->ReadDouble();
    dHmaxEdit->Text=S->ReadDouble();
    // Данные о местности
    q20Edit->Text=S->ReadDouble();
    pEdit->Text=S->ReadDouble();
    F0Edit->Text=S->ReadDouble();
    GammaEdit->Text=S->ReadDouble();
    MEdit->Text=S->ReadDouble();
    ZSEdit->Text=S->ReadDouble();
    TkEdit->Text=S->ReadDouble();
    TlEdit->Text=S->ReadDouble();
    FEEdit->Text=S->ReadDouble();
    for(int i=0;i<nSegment+1;i++)
    {
        GeodezicCells->Cells[1][i+1]=S->ReadAnsiString();
        GeodezicCells->Cells[2][i+1]=S->ReadAnsiString();
    }
    f=false;
    for(int i=0;i<nSegment;i++)
    {
        SegmentCells->Cells[1][i+1]=S->ReadAnsiString();
        SegmentCells->Cells[2][i+1]=S->ReadAnsiString();
        SegmentCells->Cells[3][i+1]=S->ReadAnsiString();
        SegmentCells->Cells[4][i+1]=S->ReadAnsiString();
        SegmentCells->Cells[5][i+1]=S->ReadAnsiString();
        SegmentCells->Cells[6][i+1]=S->ReadAnsiString();
    }
    ComboType->ItemIndex=S->ReadInt();
    //f=true;
    delete S;
    delete a;
    NumberSegment->Text=nSegment;    
}
bool TMDIChild::Clear(void)
{
    if (IsChange)
    {
        switch(MessageBox(Handle, "Файл не сохранен. Сохранить ?","",MB_YESNOCANCEL | MB_ICONQUESTION))
        {
            case IDYES : FileSave();break;
            case IDCANCEL : Abort();break;
        }
    }
    // Дальше должен идти код очистки формы, если нужен ? Пока нет.
    return true;
}

void __fastcall TMDIChild::MdComboBoxChange(TObject *Sender)
{
    int x=0;
    for(int i=0;NameMest[i]!="";i++)
    {
        if (MdComboBox->Text==NameMest[i]) { x=i;break;}
    }
    MdEdit->Text=MD[x];
}
//---------------------------------------------------------------------------
void TMDIChild::CreateReport(TMDIReport *Report,int NumReport)
{
}

void __fastcall TMDIChild::SpeedButton2Click(TObject *Sender)
{
    Calculate();    
}
//---------------------------------------------------------------------------



void __fastcall TMDIChild::SegmentCellsKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if (Key==13)
    {
        Key=8;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMDIChild::SegmentCellsKeyPress(TObject *Sender, char &Key)
{
    if (Key==13 && SegmentCells->Col<SegmentCells->ColCount-1)
    {

        SegmentCells->Col=SegmentCells->Col+1;
    }
}
//---------------------------------------------------------------------------

