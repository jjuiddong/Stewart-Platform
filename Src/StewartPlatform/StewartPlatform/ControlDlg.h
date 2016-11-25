#pragma once
#include "afxcmn.h"

class CControlDlg : public CDialogEx
{
public:
	CControlDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CControlDlg();

	enum { IDD = IDD_DIALOG_CONTROL };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


public:
	float m_actuator[6];		// actuator length


	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	float m_editRoll;
	float m_editPitch;
	float m_editYaw;
	float m_editHeave;
	float m_editSurge;
	float m_editSway;
	CSliderCtrl m_sliderRoll;
	CSliderCtrl m_sliderPitch;
	CSliderCtrl m_sliderYaw;
	CSliderCtrl m_sliderHeave;
	CSliderCtrl m_sliderSurge;
	CSliderCtrl m_sliderSway;
	int m_controlMode;
	afx_msg void OnBnClickedRadioAuto();
	afx_msg void OnBnClickedRadioManual();
};


