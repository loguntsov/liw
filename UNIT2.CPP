//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#include "Truby.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormCreate(TObject *Sender)
{
    for(int i=0;SortamentName[i]!=NULL;i++)
    {
        ComboBox1->Items->Add(SortamentName[i]->Name);
    }

}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button1Click(TObject *Sender)
{
    Label17->Caption="";
    double ZBeg=Edit1->Text.ToDouble();
    double ZEnd=Edit2->Text.ToDouble();
    double HBeg=Edit3->Text.ToDouble();
    double Q=Edit4->Text.ToDouble();
    double Len=Edit5->Text.ToDouble();
    double Vvh=Edit6->Text.ToDouble();
    CTruba *a=new CTruba(SortamentName[ComboBox1->ItemIndex],Len,ZBeg,ZEnd,HBeg,Q,Vvh);
    a->ToMaxSortament();
    a->ToNapolnenie();
    if (a->Rash)
    {
        Label11->Caption=a->hd;
        Label15->Caption=a->V;
    } else
    {
        Label17->Caption="Участок не расчетный";
    }
    Label7->Caption=a->Sortament->Diametr.UslDiametr;
    Label9->Caption=a->i1000;
    Label13->Caption=a->HEnd;
}
//---------------------------------------------------------------------------
