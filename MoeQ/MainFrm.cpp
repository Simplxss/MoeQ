// MainFrm.cpp : implementation file
//

#include "pch.h"
#include "MoeQ.h"
#include "MainFrm.h"
#include "afxdialogex.h"


// MainFrm dialog

IMPLEMENT_DYNAMIC(MainFrm, CDialogEx)

MainFrm::MainFrm(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WINDOW_MOEQ, pParent)
{

}

MainFrm::~MainFrm()
{
}

void MainFrm::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MainFrm, CDialogEx)
	ON_BN_CLICKED(IDC_LOGIN, &MainFrm::OnBnClickedLogin)
END_MESSAGE_MAP()


// MainFrm message handlers


void MainFrm::OnBnClickedLogin()
{
	// TODO: Add your control notification handler code here

}
