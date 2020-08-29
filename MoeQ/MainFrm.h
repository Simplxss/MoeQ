#pragma once


// MainFrm dialog

class MainFrm : public CDialogEx
{
	DECLARE_DYNAMIC(MainFrm)

public:
	MainFrm(CWnd* pParent = nullptr);   // standard constructor
	virtual ~MainFrm();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WINDOW_MOEQ };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLogin();
};
