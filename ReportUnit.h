//---------------------------------------------------------------------------

#ifndef ReportUnitH
#define ReportUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>

class TMDIChild;

#include "ChildWin.h"



//---------------------------------------------------------------------------
class TMDIReport : public TForm
{
__published:	// IDE-managed Components
    TRichEdit *RichBox;
    TSaveDialog *SaveDialog;
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TMDIReport(TComponent* Owner);
    void FileSave(void); // Запись отчета
    void FileSaveAs(void); // Запись отчета как ...
    AnsiString FileName; // Имя файла отчета
    void FileLoad(AnsiString FileName); // Открытие отчета
    void Print(void);
    bool Clear(void);
    TMDIChild *ChildWin;
};
//---------------------------------------------------------------------------
extern PACKAGE TMDIReport *MDIReport;
//---------------------------------------------------------------------------
#endif
