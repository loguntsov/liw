//----------------------------------------------------------------------------
#ifndef ChildWinH
#define ChildWinH
//----------------------------------------------------------------------------
#include <vcl\Controls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Windows.hpp>
#include <vcl\System.hpp>
#include <StdCtrls.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Dialogs.hpp>

class TMDIReport;

#include "ReportUnit.h"
#include <Dialogs.hpp>
//----------------------------------------------------------------------------

// Признак того, что программа является ДЕМО версией.
//#define IsDemo;
// Чтобы программа была не демо, нужно закоментировать строчку выше этой.

class TMDIChild : public TForm
{
__published:
    TPageControl *PageControl1;
    TTabSheet *TabSheet1;
    TTabSheet *TabSheet2;
    TTabSheet *TabSheet3;
    TStringGrid *GeodezicCells;
    TStringGrid *SegmentCells;
    TPanel *Panel1;
    TPanel *Panel3;
    TSpeedButton *SpeedButton1;
    TScrollBox *ScrollBox1;
    TLabel *Label1;
    TEdit *NumberSegment;
    TComboBox *SortamentBox;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label7;
    TEdit *HminEdit;
    TEdit *HmaxEdit;
    TEdit *dHmaxEdit;
    TLabel *Label2;
    TUpDown *UpDown;
    TScrollBox *ScrollBox2;
    TStaticText *StaticText1;
    TComboBox *BegGeoPointBox;
    TComboBox *EndGeoPointBox;
    TStaticText *StaticText2;
    TStaticText *StaticText3;
    TEdit *SegmentLen;
    TStaticText *StaticText4;
    TEdit *SegmentHBeg;
    TLabel *Label3;
    TComboBox *SegmentSortamentBox;
    TLabel *Label9;
    TEdit *NDogdEdit;
    TSaveDialog *SaveDialog;
    TLabel *Label10;
    TEdit *MdEdit;
    TLabel *Label6;
    TComboBox *MdComboBox;
    TLabel *Label8;
    TComboBox *ComboType;
    TTabSheet *TabSheet4;
    TSpeedButton *SpeedButton2;
        TLabel *Label11;
        TEdit *q20Edit;
        TLabel *Label12;
        TEdit *F0Edit;
        TLabel *Label13;
    TEdit *pEdit;
        TLabel *Label14;
        TEdit *ZSEdit;
    TLabel *Label15;
    TEdit *GammaEdit;
    TLabel *Label16;
    TEdit *TkEdit;
    TLabel *Label17;
    TEdit *TlEdit;
    TUpDown *UpDown1;
    TUpDown *UpDown2;
    TLabel *Label18;
    TEdit *MEdit;
    TLabel *Label19;
    TEdit *FEEdit;
    TLabel *Label20;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall SegmentCellsSelectCell(TObject *Sender, int ACol,
          int ARow, bool &CanSelect);
    void __fastcall SegmentCellsSetEditText(TObject *Sender, int ACol,
          int ARow, const AnsiString Value);
    void __fastcall BegGeoPointBoxChange(TObject *Sender);
    void __fastcall SpeedButton1Click(TObject *Sender);
    void __fastcall UpDownChanging(TObject *Sender, bool &AllowChange);
    void __fastcall NumberSegmentChange(TObject *Sender);
    void __fastcall MdComboBoxChange(TObject *Sender);
    void __fastcall SpeedButton2Click(TObject *Sender);
    void __fastcall SegmentCellsKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall SegmentCellsKeyPress(TObject *Sender, char &Key);
private:
    int x;
    int y;
    bool f;
    void LoadSegmentData(int ACol,int ARow);
    void TMDIChild::DownloadSegmentData(void);
public:
	virtual __fastcall TMDIChild(TComponent *Owner);
    void __fastcall Calculate(void);
    TMDIReport *Report;
    void FileSave(void); // Запись исходных данных
    void FileSaveAs(void); // Запись исходных данных как ...
    AnsiString FileName; // Имя файла отчета
    void FileLoad(AnsiString FileName); // Открытие исходных данных
    bool IsChange;
    bool Clear(void);
    void CreateReport(TMDIReport *Rep,int NumReport);
};
//----------------------------------------------------------------------------
#endif	
