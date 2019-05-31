// TextEditor.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "TextEditor.h"
#include "TextEditorDlg.h"
#include "splash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextEditorApp

BEGIN_MESSAGE_MAP(CTextEditorApp, CWinApp)
	//{{AFX_MSG_MAP(CTextEditorApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextEditorApp construction

CTextEditorApp::CTextEditorApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTextEditorApp object

CTextEditorApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTextEditorApp initialization

BOOL CTextEditorApp::InitInstance()
{

	CCommandLineInfo cmdInfo;

	//ParseCommandLine(cmdInfo);
	//CString m_sFileName = cmdInfo.m_strFileName;   //m_sFileName   为当前要打开的程序路径  
	//CString strCmdLine = GetCommandLine();
	
	CSplashWnd::EnableSplashScreen(cmdInfo.m_bShowSplash);

	AfxEnableControlContainer();
     

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CTextEditorDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	if (!ProcessShellCommand(cmdInfo)) 
        return FALSE;
	return TRUE;
	//return FALSE;
}
