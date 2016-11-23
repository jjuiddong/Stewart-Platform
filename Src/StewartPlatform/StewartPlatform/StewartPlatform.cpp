
#include "stdafx.h"
#include "StewartPlatform.h"
#include "StewartPlatformDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CStewartPlatformApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

CStewartPlatformApp::CStewartPlatformApp()
{
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
}

CStewartPlatformApp theApp;

BOOL CStewartPlatformApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	CWinApp::InitInstance();
	AfxEnableControlContainer();
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
	CStewartPlatformDlg *dlg = new CStewartPlatformDlg();
	dlg->Create(CStewartPlatformDlg::IDD);
	m_pMainWnd = dlg;
	dlg->ShowWindow(SW_SHOW);
	dlg->Run();
	//INT_PTR nResponse = dlg.DoModal();
#ifndef _AFXDLL
	ControlBarCleanUp();
#endif
	delete dlg;
	return FALSE;
}

