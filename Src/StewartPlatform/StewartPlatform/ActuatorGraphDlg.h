#pragma once


class CMultiPlotWindow;
class CActuatorGraphDlg : public CDialogEx
{
public:
	CActuatorGraphDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CActuatorGraphDlg();

	enum { IDD = IDD_DIALOG_GRAPH };
	void Update(const float deltaSeconds);


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


protected:
	CMultiPlotWindow *m_multiPlot;


	DECLARE_MESSAGE_MAP()
	DECLARE_ANCHOR_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	int m_graphMode;
};
