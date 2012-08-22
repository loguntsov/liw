//----------------------------------------------------------------------------
#ifndef MainH
#define MainH
//----------------------------------------------------------------------------
#include "ChildWin.h"
#include <vcl\ComCtrls.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Messages.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\Dialogs.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Menus.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Classes.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Windows.hpp>
#include <vcl\System.hpp>
#include <ActnList.hpp>
#include <ImgList.hpp>
#include <StdActns.hpp>
#include <ToolWin.hpp>
//----------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:
	TMainMenu *MainMenu1;
	TMenuItem *File1;
	TMenuItem *FileNewItem;
	TMenuItem *FileOpenItem;
	TMenuItem *FileCloseItem;
	TMenuItem *Window1;
	TMenuItem *Help1;
	TMenuItem *N1;
	TMenuItem *FileExitItem;
	TMenuItem *WindowCascadeItem;
	TMenuItem *WindowTileItem;
	TMenuItem *WindowArrangeItem;
	TMenuItem *HelpAboutItem;
	TOpenDialog *OpenDialog;
	TMenuItem *FileSaveItem;
	TMenuItem *FileSaveAsItem;
	TMenuItem *WindowMinimizeItem;
        TStatusBar *StatusBar;
        TActionList *ActionList1;
        TEditCut *EditCut1;
        TEditCopy *EditCopy1;
        TEditPaste *EditPaste1;
        TAction *FileNew1;
        TAction *FileSave1;
        TAction *FileExit1;
        TAction *FileOpen1;
        TAction *FileSaveAs1;
        TWindowCascade *WindowCascade1;
        TWindowTileHorizontal *WindowTileHorizontal1;
        TWindowArrange *WindowArrangeAll1;
        TWindowMinimizeAll *WindowMinimizeAll1;
        TAction *HelpAbout1;
        TWindowClose *FileClose1;
        TWindowTileVertical *WindowTileVertical1;
        TMenuItem *WindowTileItem2;
        TImageList *ImageList1;
    TCoolBar *CoolBar1;
    TToolBar *ToolBar1;
    TToolBar *ToolBar2;
    TAction *CalculateCalculation;
    TAction *CalculateRefresh;
    TToolButton *ToolButton1;
    TToolButton *ToolButton2;
    TToolButton *ToolButton3;
    TToolButton *ToolButton4;
    TAction *PrevPage;
    TAction *NextPage;
    TToolButton *ToolButton5;
    TToolButton *ToolButton6;
    TPrintDialog *PrintDialog1;
    TAction *FilePrint;
    TMenuItem *FilePrintItem;
    TMenuItem *N6;
    TToolButton *ToolButton7;
    TToolButton *ToolButton8;
    TToolButton *BtnWindowSwap;
    TAction *WindowSwap;
    TToolButton *ToolButton9;
        void __fastcall FileNew1Execute(TObject *Sender);
        void __fastcall FileOpen1Execute(TObject *Sender);
        void __fastcall HelpAbout1Execute(TObject *Sender);
        void __fastcall FileExit1Execute(TObject *Sender);
    void __fastcall FileSave1Execute(TObject *Sender);
    void __fastcall FileSave1Update(TObject *Sender);
    void __fastcall CalculateCalculationExecute(TObject *Sender);
    void __fastcall CalculateCalculationUpdate(TObject *Sender);
    void __fastcall PrevPageUpdate(TObject *Sender);
    void __fastcall NextPageUpdate(TObject *Sender);
    void __fastcall NextPageExecute(TObject *Sender);
    void __fastcall PrevPageExecute(TObject *Sender);
    void __fastcall FileSaveAs1Execute(TObject *Sender);
    void __fastcall FilePrintUpdate(TObject *Sender);
    void __fastcall FilePrintExecute(TObject *Sender);
    void __fastcall WindowSwapUpdate(TObject *Sender);
    void __fastcall WindowSwapExecute(TObject *Sender);
private:
	void __fastcall CreateMDIChild(const String Name);
public:
	virtual __fastcall TMainForm(TComponent *Owner);
};
//----------------------------------------------------------------------------
extern TMainForm *MainForm;
extern TMDIChild *__fastcall MDIChildCreate(void);
//----------------------------------------------------------------------------
#endif    
