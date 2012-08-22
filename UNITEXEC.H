//---------------------------------------------------------------------------

#ifndef UnitExecH
#define UnitExecH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TFormExec : public TForm
{
__published:	// IDE-managed Components
    TProgressBar *ProgressBar1;
private:	// User declarations
public:		// User declarations
    __fastcall TFormExec(TComponent* Owner);
    void Next(void);

};
//---------------------------------------------------------------------------
extern PACKAGE TFormExec *FormExec;
//---------------------------------------------------------------------------
#endif
