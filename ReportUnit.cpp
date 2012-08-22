//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ReportUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMDIReport *MDIReport;
//---------------------------------------------------------------------------
__fastcall TMDIReport::TMDIReport(TComponent* Owner)
    : TForm(Owner)
{
    FileName="";
}
//---------------------------------------------------------------------------
void __fastcall TMDIReport::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    Clear();Action = caFree;
    if (ChildWin!=NULL) ChildWin->Report=NULL;
}
//---------------------------------------------------------------------------

void TMDIReport::FileSave(void) // Запись отчета
{
    if (FileName=="") FileSaveAs();
    else
    {
        RichBox->Lines->SaveToFile(FileName);
        RichBox->Modified=false;
        Caption=FileName;
    }
}
void TMDIReport::FileSaveAs(void)
{
    if (SaveDialog->Execute())
    {
        FileName=SaveDialog->FileName;
        FileSave();
    }
}
void TMDIReport::FileLoad(AnsiString File)
{
    Clear();
    FileName=File;
    RichBox->Lines->LoadFromFile(File);
    RichBox->Modified=false;
    Caption=File;

}
bool TMDIReport::Clear(void)
{
    if (RichBox->Modified)
    {
        switch(MessageBox(Handle, "Файл не сохранен. Сохранить ?","",MB_YESNOCANCEL | MB_ICONQUESTION))
        {
            case IDYES : FileSave();break;
            case IDCANCEL : Abort();break;
        }
    }
    RichBox->Clear();
    return True;
}
void TMDIReport::Print(void)
{
    RichBox->Print("");
}
void __fastcall TMDIReport::FormCreate(TObject *Sender)
{
    ChildWin=NULL;    
}
//---------------------------------------------------------------------------

