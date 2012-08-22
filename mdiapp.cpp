//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------
USEFORM("Main.cpp", MainForm);
USEFORM("ChildWin.cpp", MDIChild);
USERES("mdiapp.res");
USEFORM("about.cpp", AboutBox);
USEFORM("ReportUnit.cpp", MDIReport);
USEUNIT("DiskSystem.cpp");
USEFORM("UnitExec.cpp", FormExec);
USEUNIT("MathMethod.cpp");
USEUNIT("Liw.cpp");
USEUNIT("TrubyLiw.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR Command, int)
{
	Application->Initialize();
	Application->Title = " анализационные сети города";
    //double x=time(NULL);
    //if (x>1022028563) return 0;
         Application->CreateForm(__classid(TMainForm), &MainForm);
         Application->CreateForm(__classid(TFormExec), &FormExec);
         HANDLE hOpen=CreateEvent(NULL,TRUE,FALSE,"KansExeOpenFileEvent");
         if (GetLastError() == ERROR_ALREADY_EXISTS) // ≈сли приложение уже запущено
         {
            // Ёта возможность пока не используетс€
         } else Application->Run();
         CloseHandle(hOpen);
	return 0;
}
//---------------------------------------------------------------------
