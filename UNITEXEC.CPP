//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitExec.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormExec *FormExec;
//---------------------------------------------------------------------------
__fastcall TFormExec::TFormExec(TComponent* Owner)
    : TForm(Owner)
{
}
void TFormExec::Next(void)
{
    ProgressBar1->Position=ProgressBar1->Position+1;
}
//---------------------------------------------------------------------------
