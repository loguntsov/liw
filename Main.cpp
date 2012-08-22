//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "About.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------

__fastcall TMainForm::TMainForm(TComponent *Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CreateMDIChild(String Name)
{
	TMDIChild *Child;

	//--- create a new MDI child window ----
	Child = new TMDIChild(Application);
	Child->Caption = Name;
	/*if (FileExists (Name))
		Child->Memo1->Lines->LoadFromFile(Name);*/
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FileNew1Execute(TObject *Sender)
{
	CreateMDIChild("NONAME" + IntToStr(MDIChildCount + 1));
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FileOpen1Execute(TObject *Sender)
{
	if (OpenDialog->Execute())
    {
        AnsiString x=OpenDialog->FileName.SubString(OpenDialog->FileName.Length()-3,4).LowerCase();
        if (x!=".liw")
        {
            (new TMDIReport(this))->FileLoad(OpenDialog->FileName);
        } else
        {
            (new TMDIChild(this))->FileLoad(OpenDialog->FileName);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::HelpAbout1Execute(TObject *Sender)
{
    TAboutBox *Help=new TAboutBox(this);
	Help->ShowModal();
    delete Help;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FileExit1Execute(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::FileSave1Execute(TObject *Sender)
{
    switch(ActiveMDIChild->Tag)
    {
        case 1: ((TMDIChild *) ActiveMDIChild)->FileSave();break;
        case 2: ((TMDIReport *) ActiveMDIChild)->FileSave();break;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FileSave1Update(TObject *Sender)
{
    if (ActiveMDIChild!=NULL)
    {
        switch(ActiveMDIChild->Tag)
        {
            case 2 : FileSave1->Enabled=true;break;
            case 1 : FileSave1->Enabled=true;break;
            
            default: FileSave1->Enabled=false;
        }
    } else FileSave1->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CalculateCalculationExecute(TObject *Sender)
{
    switch(ActiveMDIChild->Tag)
    {
        case 1: ((TMDIChild *) ActiveMDIChild)->Calculate();break;
        default:
        ;
    }
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::CalculateCalculationUpdate(TObject *Sender)
{
    if (ActiveMDIChild!=NULL)
    {
        switch(ActiveMDIChild->Tag)
        {
            case 1 : CalculateCalculation->Enabled=true;break;
            default: CalculateCalculation->Enabled=false;
        }
    } else CalculateCalculation->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PrevPageUpdate(TObject *Sender)
{
    if (ActiveMDIChild!=NULL)
    {
        switch(ActiveMDIChild->Tag)
        {
            case 1 :
               if  (((TMDIChild *) ActiveMDIChild)->PageControl1->ActivePageIndex==0) PrevPage->Enabled=false; else PrevPage->Enabled=true;
               break;
            default:
                PrevPage->Enabled=false;
        }
    } else PrevPage->Enabled=false;

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::NextPageUpdate(TObject *Sender)
{
    if (ActiveMDIChild!=NULL)
    {
        switch(ActiveMDIChild->Tag)
        {
            case 1 :
               if  (((TMDIChild *) ActiveMDIChild)->PageControl1->ActivePageIndex==3) NextPage->Enabled=false; else NextPage->Enabled=true;
               break;
            default:
                NextPage->Enabled=false;
        }
    } else NextPage->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::NextPageExecute(TObject *Sender)
{
    ((TMDIChild *) ActiveMDIChild)->PageControl1->ActivePageIndex=((TMDIChild *) ActiveMDIChild)->PageControl1->ActivePageIndex+1;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PrevPageExecute(TObject *Sender)
{
    ((TMDIChild *) ActiveMDIChild)->PageControl1->ActivePageIndex=((TMDIChild *) ActiveMDIChild)->PageControl1->ActivePageIndex-1;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FileSaveAs1Execute(TObject *Sender)
{
    switch(ActiveMDIChild->Tag)
    {
        case 2: ((TMDIReport *) ActiveMDIChild)->FileSaveAs();
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FilePrintUpdate(TObject *Sender)
{
    if (ActiveMDIChild!=NULL)
    {
        switch(ActiveMDIChild->Tag)
        {
            case 2 :
                FilePrint->Enabled=true;break;
            default:
                FilePrint->Enabled=false;
        }
    } else FilePrint->Enabled=false;
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::FilePrintExecute(TObject *Sender)
{
    if (PrintDialog1->Execute()) ((TMDIReport *) ActiveMDIChild)->Print();
}
//---------------------------------------------------------------------------



void __fastcall TMainForm::WindowSwapUpdate(TObject *Sender)
{
    if (ActiveMDIChild!=NULL)
    {
        switch(ActiveMDIChild->Tag)
        {
            case 2 :
                if (((TMDIReport * ) ActiveMDIChild)->ChildWin!=NULL) WindowSwap->Enabled=true;
                    else WindowSwap->Enabled=false;
                break;
            case 1:
                if (((TMDIChild * ) ActiveMDIChild)->Report!=NULL) WindowSwap->Enabled=true;
                    else WindowSwap->Enabled=false;
                break;

            default:
                WindowSwap->Enabled=false;
        }
    } else WindowSwap->Enabled=false;

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::WindowSwapExecute(TObject *Sender)
{
    if (ActiveMDIChild!=NULL)
    {
        switch(ActiveMDIChild->Tag)
        {
            case 2 :
                if (((TMDIReport * ) ActiveMDIChild)->ChildWin!=NULL) ((TMDIReport * ) ActiveMDIChild)->ChildWin->Show();
                    else WindowSwap->Enabled=false;
                break;
            case 1:
                if (((TMDIChild * ) ActiveMDIChild)->Report!=NULL) ((TMDIChild * ) ActiveMDIChild)->Report->Show();
                    else WindowSwap->Enabled=false;
                break;

            default:
                WindowSwap->Enabled=false;
        }
    } else WindowSwap->Enabled=false;
}
//---------------------------------------------------------------------------

