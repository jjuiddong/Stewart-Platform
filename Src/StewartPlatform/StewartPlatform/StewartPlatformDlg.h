//
// Main Dialog
//
#pragma once


class C3DView;
class CControlDlg;

class CStewartPlatformDlg : public CDialogEx
{
public:
	CStewartPlatformDlg(CWnd* pParent = NULL);	// standard constructor
	enum { IDD = IDD_STEWARTPLATFORM_DIALOG };

	bool Run();


protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	void MainLoop(const float deltaSeconds);


protected:
	HICON m_hIcon;
	bool m_isLoop;
	C3DView *m_3dView;
	CControlDlg *m_controlDlg;

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
