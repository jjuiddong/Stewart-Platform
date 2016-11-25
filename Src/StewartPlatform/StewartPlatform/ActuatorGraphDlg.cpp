// ActuatorGraphDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StewartPlatform.h"
#include "ActuatorGraphDlg.h"
#include "afxdialogex.h"
#include "ControlDlg.h"

CActuatorGraphDlg *g_actuatorDlg = NULL;


CActuatorGraphDlg::CActuatorGraphDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_GRAPH, pParent)
	, m_multiPlot(NULL)
	, m_graphMode(0)
{
}

CActuatorGraphDlg::~CActuatorGraphDlg()
{
}

void CActuatorGraphDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_LENGTH, m_graphMode);
}


BEGIN_MESSAGE_MAP(CActuatorGraphDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CActuatorGraphDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CActuatorGraphDlg::OnBnClickedCancel)
	ON_WM_SIZE()
END_MESSAGE_MAP()

BEGIN_ANCHOR_MAP(CActuatorGraphDlg)
	ANCHOR_MAP_ENTRY(IDC_STATIC_GRAPH, ANF_TOPLEFT | ANF_BOTTOMRIGHT)
END_ANCHOR_MAP()


// CActuatorGraphDlg message handlers
void CActuatorGraphDlg::OnBnClickedOk()
{
	//CDialogEx::OnOK();
}

void CActuatorGraphDlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}


BOOL CActuatorGraphDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitAnchors();

	CRect rect;
	GetDlgItem(IDC_STATIC_GRAPH)->GetWindowRect(rect);
	ScreenToClient(rect);

	m_multiPlot = new CMultiPlotWindow();
	m_multiPlot->Create(NULL, NULL, WS_VISIBLE | WS_CHILD, rect, this, 0);
	m_multiPlot->SetScrollSizes(MM_TEXT, CSize(rect.Width() - 30, 100));
	m_multiPlot->ShowWindow(SW_SHOW);

	CString cmd = L""
		L"plot1 = 0, 0, 0, 0, 0 \n"
		L"string1 = %f \n"
		L"name1 = actuator1 \n"
		L"plot2 = 0, 0, 0, 0, 0 \n"
		L"string2 = %*f; %f; \n"
		L"name2 = actuator2 \n"
		L"plot3 = 0, 0, 0, 0, 0 \n"
		L"string3 = %*f; %*f; %f \n"
		L"name3 = actuator3 \n"
		L"plot4 = 0, 0, 0, 0, 0 \n"
		L"string4 = %*f; %*f; %*f; %f \n"
		L"name4 = actuator4 \n"
		L"plot5 = 0, 0, 0, 0, 0 \n"
		L"string5 = %*f; %*f; %*f; %*f; %f \n"
		L"name5 = actuator5 \n"
		L"plot6 = 0, 0, 0, 0, 0 \n"
		L"string6 = %*f; %*f; %*f; %*f; %*f; %f \n"
		L"name6 = actuator6 \n"
		;
	m_multiPlot->ProcessPlotCommand(cmd, 1);

	return TRUE;
}


void CActuatorGraphDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	CRect rcWnd;
	GetWindowRect(&rcWnd);
	HandleAnchors(&rcWnd);

	if (CWnd *wnd = GetDlgItem(IDC_STATIC_GRAPH))
	{
		CRect rect;
		wnd->GetWindowRect(rect);
		ScreenToClient(rect);
		m_multiPlot->MoveWindow(rect);
	}
}


void CActuatorGraphDlg::Update(const float deltaSeconds)
{
	if (m_multiPlot)
	{
		const string str = format("%f; %f; %f; %f; %f; %f;", 
			g_controlDlg->m_actuator[0], 
			g_controlDlg->m_actuator[1],
			g_controlDlg->m_actuator[2],
			g_controlDlg->m_actuator[3],
			g_controlDlg->m_actuator[4],
			g_controlDlg->m_actuator[5]
			);
		m_multiPlot->SetString(str.c_str());
		m_multiPlot->DrawGraph(deltaSeconds);
	}
}
