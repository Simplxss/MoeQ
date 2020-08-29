// MainFrm.cpp : implementation file
//

#include "pch.h"
#include "MoeQ.h"
#include "MainFrm.h"
#include "afxdialogex.h"

#include "ExportFunction.h"


wchar_t DataPath[MAX_PATH + 1];
bool DevMode = true;

PluginSystem Plugin;

Android::Token Token;
Android Sdk("861891778567", "460013521635791", (const byte*)"\x86\xA4\x45\xBF\x44\xA2\xC2\x87\x59\x76\x18\xF6\xF3\x6E\xB6\x8C", (const byte*)"\0\0\0\0\0\2", "XiaoMi", "MIX Alpha");


// MainFrm dialog

IMPLEMENT_DYNAMIC(MainFrm, CDialogEx)

MainFrm::MainFrm()
	: CDialog()
{
	Create(IDD_WINDOW_MOEQ);
}

MainFrm::~MainFrm()
{
}

void MainFrm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

// Msg Loop
BEGIN_MESSAGE_MAP(MainFrm, CDialog)
	ON_EN_CHANGE(IDC_ACCOUNT, &MainFrm::OnEnChangeAccount)
	ON_EN_CHANGE(IDC_PASSWORD, &MainFrm::OnEnChangePassword)
	ON_BN_CLICKED(IDC_LOGIN, &MainFrm::OnBnClickedLogin)
	ON_BN_CLICKED(IDC_SIGNOUT, &MainFrm::OnBnClickedSignout)
END_MESSAGE_MAP()

//Thread function declare
void (WINAPI Login)(_In_ MainFrm* MainFrm);

// MainFrm message handlers

BOOL MainFrm::OnInitDialog()
{
	CDialog::OnInitDialog();

	TCHAR szFilePath[MAX_PATH + 1] = { 0 };
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0; // delete the file name
	wcscpy(DataPath, szFilePath);
	wcscat(DataPath, L"data\\");

	wchar_t _QQ[12];
	wchar_t str[256];
	wchar_t DataFilePath[256];
	wcscpy(DataFilePath, DataPath);
	wcscat(DataFilePath, L"data.ini");

	GetPrivateProfileString(L"Token", L"QQ", NULL, _QQ, 50, DataFilePath);

	GetPrivateProfileString(L"Token", L"A2", NULL, str, 256, DataFilePath);
	if (XBin::Hex2Bin(Iconv::Unicode2Ansi(str), Token.A2) != 64) throw "A2 len error";

	GetPrivateProfileString(L"Token", L"TGT", NULL, str, 256, DataFilePath);
	if (XBin::Hex2Bin(Iconv::Unicode2Ansi(str), Token.TGT) != 72) throw "TGT len error";

	GetPrivateProfileString(L"Token", L"D2Key", NULL, str, 256, DataFilePath);
	if (XBin::Hex2Bin(Iconv::Unicode2Ansi(str), Token.D2Key) != 16) throw "D2Key len error";

	GetPrivateProfileString(L"Token", L"wtSessionTicket", NULL, str, 256, DataFilePath);
	if (XBin::Hex2Bin(Iconv::Unicode2Ansi(str), Token.wtSessionTicket) != 48) throw "wtSessionTicket len error";

	GetPrivateProfileString(L"Token", L"wtSessionTicketKey", NULL, str, 256, DataFilePath);
	if (XBin::Hex2Bin(Iconv::Unicode2Ansi(str), Token.wtSessionTicketKey) != 16) throw "wtSessionTicketKey len error";

	GetPrivateProfileString(L"Token", L"token_16A", NULL, str, 256, DataFilePath);
	if (XBin::Hex2Bin(Iconv::Unicode2Ansi(str), Token.token_16A) != 48) throw "token_16A len error";

	GetPrivateProfileString(L"Token", L"md5", NULL, str, 256, DataFilePath);
	if (XBin::Hex2Bin(Iconv::Unicode2Ansi(str), Token.md5) != 16) throw "md5 len error";

	GetPrivateProfileString(L"Token", L"TGTkey", NULL, str, 256, DataFilePath);
	if (XBin::Hex2Bin(Iconv::Unicode2Ansi(str), Token.TGTkey) != 16) throw "TGTkey len error";

	GetPrivateProfileString(L"Token", L"ksid", NULL, str, 256, DataFilePath);
	if (XBin::Hex2Bin(Iconv::Unicode2Ansi(str), Token.ksid) != 16) throw "ksid len error";

	if (lstrcmpW(_QQ, L""))
	{
		GetDlgItem(IDC_ACCOUNT)->SetWindowTextW(_QQ);
		GetDlgItem(IDC_PASSWORD)->SetWindowTextW(L"******");
		((CButton*)GetDlgItem(IDC_SAVE_PASSWORD))->SetCheck(BST_CHECKED);
		((CButton*)GetDlgItem(IDC_SECOND_LOGIN))->SetCheck(BST_CHECKED);
		((CButton*)GetDlgItem(IDC_SECOND_LOGIN))->EnableWindow(TRUE);
	}

	Plugin.Load(Iconv::Unicode2Ansi(szFilePath));

	((CComboBox*)GetDlgItem(IDC_LOG_TYPE))->SetCurSel(1);

	CListCtrl* Log = (CListCtrl*)GetDlgItem(IDC_LOG);
	Log->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	Log->InsertColumn(0, L"LogType", LVCFMT_CENTER, 64);
	Log->InsertColumn(1, L"MsgType", LVCFMT_CENTER, 82);
	Log->InsertColumn(2, L"Type", LVCFMT_CENTER, 74);
	Log->InsertColumn(3, L"Msg", LVCFMT_CENTER, 315);

	Log::Init((HANDLE)this);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void MainFrm::OnOK()
{
	// 防止按Enter销毁了了
	//CDialog::OnOK();
}

void MainFrm::OnCancel()
{
	CDialog::OnCancel();
	exit(0);
}

void MainFrm::OnEnChangeAccount()
{
	if (GetDlgItem(IDC_ACCOUNT)->GetWindowTextLengthW() >= 12)
	{
		wchar_t str[13];
		GetDlgItem(IDC_ACCOUNT)->GetWindowTextW(str, 11);
		GetDlgItem(IDC_ACCOUNT)->SetWindowTextW(str);
	};
}

void MainFrm::OnEnChangePassword()
{
	if (GetDlgItem(IDC_PASSWORD)->GetWindowTextLengthW() >= 36)
	{
		wchar_t str[37];
		GetDlgItem(IDC_PASSWORD)->GetWindowTextW(str, 36);
		GetDlgItem(IDC_PASSWORD)->SetWindowTextW(str);
	};
}

void MainFrm::OnBnClickedLogin()
{
	((CButton*)GetDlgItem(IDC_LOGIN))->EnableWindow(FALSE);
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Login, this, 0, nullptr);
}

void MainFrm::OnBnClickedSignout()
{
	((CButton*)GetDlgItem(IDC_SIGNOUT))->EnableWindow(FALSE);
	Sdk.QQ_Offline();
	((CButton*)GetDlgItem(IDC_LOGIN))->EnableWindow(TRUE);
}


void WINAPI Login(MainFrm* MainFrm)
{
	(CListCtrl*)MainFrm->GetDlgItem(IDC_LOG);
	Log::AddLog(Log::LogType::INFORMATION, Log::MsgType::OTHER, L"Login", L"Start login");
	wchar_t* QQ = new wchar_t[MainFrm->GetDlgItem(IDC_ACCOUNT)->GetWindowTextLengthW() + 1];
	MainFrm->GetDlgItem(IDC_ACCOUNT)->GetWindowTextW(QQ, MainFrm->GetDlgItem(IDC_ACCOUNT)->GetWindowTextLengthW() + 1);
	if (((CButton*)MainFrm->GetDlgItem(IDC_SECOND_LOGIN))->GetCheck())
	{
		Sdk.QQ_Init(Iconv::Unicode2Ansi(QQ));
		Sdk.QQ_Set_Token(&Token);
		Sdk.QQ_Login_Second();
		Sdk.QQ_Login_Finish();
	}
	else
	{
		byte state;
		wchar_t* Password = new wchar_t[MainFrm->GetDlgItem(IDC_PASSWORD)->GetWindowTextLengthW() + 1];
		MainFrm->GetDlgItem(IDC_PASSWORD)->GetWindowTextW(Password, MainFrm->GetDlgItem(IDC_PASSWORD)->GetWindowTextLengthW()+1);
		Sdk.QQ_Init(Iconv::Unicode2Ansi(QQ));
		state = Sdk.QQ_Login(Iconv::Unicode2Ansi(Password));
		delete[] Password;
	check:
		char Ticket[125], SmsCode[7];
		switch (state)
		{
		case LOGIN_SUCCESS:
			Log::AddLog(Log::LogType::INFORMATION, Log::MsgType::OTHER, L"Login", L"Login Successfully!");
			goto online;
		case LOGIN_VERIY:
			Log::AddLog(Log::LogType::INFORMATION, Log::MsgType::OTHER, L"Login", L"Slider verification code");
			//std::wcout << Sdk.QQ_Get_Viery_Ticket() << std::endl;
			//std::cin.getline(Ticket, 125);
			state = Sdk.QQ_Viery_Ticket(Ticket);
			goto check;
		case LOGIN_VERIY_SMS:
			Log::AddLog(Log::LogType::INFORMATION, Log::MsgType::OTHER, L"Login", L"Driver Lock");
			char notice[200];
			strcpy(notice, "Send Sms to ");
			strcat(notice, Sdk.QQ_Get_Viery_PhoneNumber());
			strcat(notice, " ?");

			switch (MessageBoxA(nullptr, notice, "Driver Lock", MB_OKCANCEL))
			{
			case IDOK:
				Sdk.QQ_Send_Sms();

				state = Sdk.QQ_Viery_Sms(SmsCode);
				break;
			case IDCANCEL:
				((CButton*)MainFrm->GetDlgItem(IDC_LOGIN))->EnableWindow(TRUE);
				return;
			}
		case LOGIN_ERROR:
			//std::wcout << (int)state << std::endl;
			((CButton*)MainFrm->GetDlgItem(IDC_LOGIN))->EnableWindow(TRUE);
			return;
		default:
			break;
		}
		Sdk.QQ_Login_Finish();
	}
online:
	//Save Tokens
	Token = *Sdk.QQ_Get_Token();

	wchar_t DataFilePath[256];
	wcscpy(DataFilePath, DataPath);
	wcscat(DataFilePath, L"data.ini");

	WritePrivateProfileString(L"Token", L"QQ", QQ, DataFilePath);
	WritePrivateProfileString(L"Token", L"A2", Iconv::Ansi2Unicode(XBin::Bin2Hex(Token.A2, 64)), DataFilePath);
	WritePrivateProfileString(L"Token", L"TGT", Iconv::Ansi2Unicode(XBin::Bin2Hex(Token.TGT, 72)), DataFilePath);
	WritePrivateProfileString(L"Token", L"D2Key", Iconv::Ansi2Unicode(XBin::Bin2Hex(Token.D2Key, 16)), DataFilePath);
	WritePrivateProfileString(L"Token", L"wtSessionTicket", Iconv::Ansi2Unicode(XBin::Bin2Hex(Token.wtSessionTicket, 48)), DataFilePath);
	WritePrivateProfileString(L"Token", L"wtSessionTicketKey", Iconv::Ansi2Unicode(XBin::Bin2Hex(Token.wtSessionTicketKey, 16)), DataFilePath);
	WritePrivateProfileString(L"Token", L"token_16A", Iconv::Ansi2Unicode(XBin::Bin2Hex(Token.token_16A, 48)), DataFilePath);
	WritePrivateProfileString(L"Token", L"md5", Iconv::Ansi2Unicode(XBin::Bin2Hex(Token.md5, 16)), DataFilePath);
	WritePrivateProfileString(L"Token", L"TGTkey", Iconv::Ansi2Unicode(XBin::Bin2Hex(Token.TGTkey, 16)), DataFilePath);
	WritePrivateProfileString(L"Token", L"ksid", Iconv::Ansi2Unicode(XBin::Bin2Hex(Token.ksid, 16)), DataFilePath);

	delete[] QQ;

	Sdk.QQ_Online();

	((CButton*)MainFrm->GetDlgItem(IDC_SIGNOUT))->EnableWindow(TRUE);
	
	while (true)
	{
		Sleep(45000);
		if (Sdk.QQ_Status()) Sdk.QQ_Heart_Beat();
	}
	return;
}