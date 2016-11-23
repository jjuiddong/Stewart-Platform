// ControlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StewartPlatform.h"
#include "ControlDlg.h"
#include "afxdialogex.h"

CControlDlg *g_controlDlg = NULL;


CControlDlg::CControlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_CONTROL, pParent)
	, m_editRoll(0)
	, m_editPitch(0)
	, m_editYaw(0)
	, m_editHeave(0)
	, m_editSurge(0)
	, m_editSway(0)
	, m_controlMode(0)
{

}

CControlDlg::~CControlDlg()
{
}

void CControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ROLL, m_editRoll);
	DDX_Text(pDX, IDC_EDIT_PITCH, m_editPitch);
	DDX_Text(pDX, IDC_EDIT_YAW, m_editYaw);
	DDX_Text(pDX, IDC_EDIT_HEAVE, m_editHeave);
	DDX_Text(pDX, IDC_EDIT_SURGE, m_editSurge);
	DDX_Text(pDX, IDC_EDIT_SWAY, m_editSway);
	DDX_Control(pDX, IDC_SLIDER_ROLL, m_sliderRoll);
	DDX_Control(pDX, IDC_SLIDER_PITCH, m_sliderPitch);
	DDX_Control(pDX, IDC_SLIDER3_YAW, m_sliderYaw);
	DDX_Control(pDX, IDC_SLIDER_HEAVE, m_sliderHeave);
	DDX_Control(pDX, IDC_SLIDER_SURGE, m_sliderSurge);
	DDX_Control(pDX, IDC_SLIDER_SWAY, m_sliderSway);
	DDX_Radio(pDX, IDC_RADIO_AUTO, m_controlMode);
}


BEGIN_MESSAGE_MAP(CControlDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CControlDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CControlDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_RADIO_AUTO, &CControlDlg::OnBnClickedRadioAuto)
	ON_BN_CLICKED(IDC_RADIO_MANUAL, &CControlDlg::OnBnClickedRadioManual)
END_MESSAGE_MAP()


// CControlDlg message handlers
BOOL CControlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_sliderRoll.SetRange(0, 1000);
	m_sliderPitch.SetRange(0, 1000);
	m_sliderYaw.SetRange(0, 1000);
	m_sliderHeave.SetRange(0, 1000);
	m_sliderSurge.SetRange(0, 1000);
	m_sliderSway.SetRange(0, 1000);

	return TRUE;
}


void CControlDlg::OnBnClickedOk()
{
//	CDialogEx::OnOK();
}


void CControlDlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}


void CControlDlg::OnBnClickedRadioAuto()
{
	UpdateData();
}


void CControlDlg::OnBnClickedRadioManual()
{
	UpdateData();
}
