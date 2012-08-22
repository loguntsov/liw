//---------------------------------------------------------------------------

#include <vcl.h>
#include <Math.hpp>
#include <Math.h>
#pragma hdrstop

#include "Unit1.h"
#include "Truby.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
    for(int i=0;SortamentName[i]!=NULL;i++)
    {
        SortamentComboBox->Items->Add(SortamentName[i]->Name);
    }
    StringGrid1->Cells[0][0]="Диаметр";
    StringGrid1->Cells[1][0]="Расход";
    StringGrid1->Cells[2][0]="Уклон";
    StringGrid1->Cells[3][0]="Наполнение";
    StringGrid1->Cells[4][0]="Скорость";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SortamentComboBoxClick(TObject *Sender)
{
    int n=SortamentComboBox->ItemIndex;
    CSortament **Sort=SortamentName[n]->Sortament;
    CSortament *Diam;
    int i=0;
    for(i=0;Sort[i]!=NULL;i++)
    {
        Diam=Sort[i];
        StringGrid1->Cells[0][i+1]=Diam->Diametr.UslDiametr;
        StringGrid1->Cells[1][i+1]=Diam->GetQmin();
        StringGrid1->Cells[2][i+1]=Diam->Geti1000min();
        StringGrid1->Cells[3][i+1]=Diam->Diametr.GetMaxNapoln();
        StringGrid1->Cells[4][i+1]=Diam->GetVmin();
    }
    StringGrid1->RowCount=i+1;
}
//---------------------------------------------------------------------------
