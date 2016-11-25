
#include "stdafx.h"
#include "StewartPlatform.h"
#include "StewartPlatformDlg.h"
#include "afxdialogex.h"
#include "C3DView.h"
#include "ControlDlg.h"
#include "ActuatorGraphDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CStewartPlatformDlg::CStewartPlatformDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_STEWARTPLATFORM_DIALOG, pParent)
	, m_isLoop(true)
	, m_3dView(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStewartPlatformDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CStewartPlatformDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CStewartPlatformDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CStewartPlatformDlg::OnBnClickedCancel)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CStewartPlatformDlg message handlers
BOOL CStewartPlatformDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CRect wr(0, 0, 800 + 14, 600 + 48);
	MoveWindow(wr);

	CRect cr;
	GetClientRect(cr);
	m_3dView = new C3DView();
	m_3dView->Create(NULL, L"CamWindow", WS_VISIBLE | WS_CHILDWINDOW, cr, this, 1100);
	m_3dView->Init();
	m_3dView->ShowWindow(SW_SHOW);

	m_controlDlg = new CControlDlg();
	m_controlDlg->Create(CControlDlg::IDD);
	m_controlDlg->ShowWindow(SW_SHOW);
	
	const int w = GetSystemMetrics(SM_CXSCREEN);
	const int h = GetSystemMetrics(SM_CYSCREEN);
	CRect ccr;
	m_controlDlg->GetWindowRect(ccr);
	ccr.OffsetRect(-CPoint(ccr.left, ccr.top));
	ccr.OffsetRect(CPoint(w/2-wr.Width()/2+wr.Width(), h/2-wr.Height()/2));
	m_controlDlg->MoveWindow(ccr);
	g_controlDlg = m_controlDlg;

	m_actuatorDlg = new CActuatorGraphDlg();
	m_actuatorDlg->Create(CActuatorGraphDlg::IDD);
	m_actuatorDlg->ShowWindow(SW_SHOW);
	CRect acr;
	m_actuatorDlg->GetWindowRect(acr);
	acr.OffsetRect(-CPoint(acr.left, acr.top));
	acr.OffsetRect(CPoint(w / 2 - wr.Width() / 2 - acr.Width(), h / 2 - wr.Height() / 2));
	m_actuatorDlg->MoveWindow(acr);
	g_actuatorDlg = m_actuatorDlg;

	return TRUE;
}

void CStewartPlatformDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CStewartPlatformDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CStewartPlatformDlg::OnBnClickedOk()
{
	//CDialogEx::OnOK();
}

void CStewartPlatformDlg::OnBnClickedCancel()
{
	m_isLoop = false;
	CDialogEx::OnCancel();
}

bool CStewartPlatformDlg::Run()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	int fps = 0;
	int lastFpsTime = timeGetTime();
	int oldT = timeGetTime();
	while (m_isLoop)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		const int curT = timeGetTime();
		const float deltaSeconds = (float)(curT - oldT) * 0.001f;
		if (deltaSeconds > 0.02f) // 50 frames
		{
			oldT = curT;

			// Check FPS
			++fps;
			if (curT - lastFpsTime > 1000)
			{
				//m_staticFPS.SetWindowText(common::formatw("FPS : %d", fps).c_str());
				fps = 0;
				lastFpsTime = curT;
			}

			MainLoop(deltaSeconds);
		}

		Sleep(1);
	}

	return true;
}


void CStewartPlatformDlg::MainLoop(const float deltaSeconds)
{
	if (m_3dView)
	{
		m_3dView->Update(deltaSeconds);
		m_3dView->Render();
	}

	if (m_actuatorDlg)
	{
		m_actuatorDlg->Update(deltaSeconds);
	}
}


void CStewartPlatformDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (m_3dView)
		m_3dView->MoveWindow(CRect(0,0,cx, cy));	
}


BOOL CStewartPlatformDlg::OnEraseBkgnd(CDC* pDC)
{
	//return CDialogEx::OnEraseBkgnd(pDC);
	return TRUE;
}
