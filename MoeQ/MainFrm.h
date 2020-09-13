#pragma once


// MainFrm dialog

class MainFrm : public CDialog
{
	DECLARE_DYNAMIC(MainFrm)

public:
	MainFrm();   // standard constructor
	virtual ~MainFrm();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WINDOW_MOEQ };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnEnChangeAccount();
	afx_msg void OnEnChangePassword();
	afx_msg void OnBnClickedLogin();
	afx_msg void OnBnClickedSignout();
	afx_msg void OnDestroy();
};
