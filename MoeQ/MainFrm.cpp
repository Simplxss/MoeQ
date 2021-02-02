#include "pch.h"
#include "MoeQ.h"
#include "MainFrm.h"
#include "afxdialogex.h"

#include "ExportFunction.h"

#define CreateWkeWindows 1999

wchar_t DataPath[MAX_PATH + 1];
bool DevMode = true;

PluginSystem Plugin;

Android::Token Token;
Android Sdk("861891778567", "460013521635791", (const byte*)"\x86\xA4\x45\xBF\x44\xA2\xC2\x87\x59\x76\x18\xF6\xF3\x6E\xB6\x8C", (const byte*)"\0\0\0\0\0\2", "XiaoMi", "MIX Alpha");

std::condition_variable Slider;
char* Ticket = nullptr;

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
	ON_WM_DESTROY()
	ON_EN_CHANGE(IDC_ACCOUNT, &MainFrm::OnEnChangeAccount)
	ON_EN_CHANGE(IDC_PASSWORD, &MainFrm::OnEnChangePassword)
	ON_BN_CLICKED(IDC_LOGIN, &MainFrm::OnBnClickedLogin)
	ON_BN_CLICKED(IDC_SIGNOUT, &MainFrm::OnBnClickedSignout)
	ON_REGISTERED_MESSAGE((WM_CREATE_WKE_WINDOWS), &MainFrm::OnCreatewkewindows)
END_MESSAGE_MAP()

//Thread function declare
void (WINAPI Login)(_In_ MainFrm* MainFrm);

// MainFrm message handlers

BOOL MainFrm::OnInitDialog()
{
	CDialog::OnInitDialog();

	((CComboBox*)GetDlgItem(IDC_LOG_TYPE))->SetCurSel(1);

	CListCtrl* Log = (CListCtrl*)GetDlgItem(IDC_LOG);
	Log->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	Log->InsertColumn(0, L"LogType", LVCFMT_CENTER, 64);
	Log->InsertColumn(1, L"MsgType", LVCFMT_CENTER, 82);
	Log->InsertColumn(2, L"Type", LVCFMT_CENTER, 74);
	Log->InsertColumn(3, L"Msg", LVCFMT_CENTER, 315);

	Log::Init((HANDLE)this);

	wchar_t szFilePath[MAX_PATH + 1], DataFilePath[MAX_PATH + 1], DllFilePath[MAX_PATH + 1] = { 0 };
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0; // delete the file name
	wcscpy(DataPath, szFilePath);
	wcscat(DataPath, L"data\\");

	Database::Init();

	wchar_t _QQ[12];
	wchar_t str[256];
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

	wcscpy(DllFilePath, szFilePath);
	wcscat(DllFilePath, L"bin\\miniblink.dll");
	if (!::PathFileExists(DllFilePath)) {
		Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, L"Init", L"miniblink.dll is not found");
		return 0;
	}
	wkeSetWkeDllPath(DllFilePath);
	wkeInitialize();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void MainFrm::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
	Sdk.QQ_Offline();
}

void MainFrm::OnOK()
{
	// ·ÀÖ¹°´EnterÏú»ÙÁË
	//CDialog::OnOK();
}

void MainFrm::OnCancel()
{
	CDialog::OnCancel();
	exit(0);
}

void MainFrm::OnEnChangeAccount()
{
	if (((CButton*)GetDlgItem(IDC_SECOND_LOGIN))->GetCheck())
	{
		GetDlgItem(IDC_PASSWORD)->SetWindowTextW(L"");
		((CButton*)GetDlgItem(IDC_SECOND_LOGIN))->SetCheck(BST_UNCHECKED);
	}
	wchar_t str[13];
	GetDlgItem(IDC_ACCOUNT)->GetWindowTextW(str, 11);
	//if (str==) TODO
	{

	}
	if (GetDlgItem(IDC_ACCOUNT)->GetWindowTextLengthW() >= 12) GetDlgItem(IDC_ACCOUNT)->SetWindowTextW(str);
}

void MainFrm::OnEnChangePassword()
{
	if (((CButton*)GetDlgItem(IDC_SECOND_LOGIN))->GetCheck())
	{
		GetDlgItem(IDC_PASSWORD)->SetWindowTextW(L"");
		((CButton*)GetDlgItem(IDC_SECOND_LOGIN))->SetCheck(BST_UNCHECKED);
		((CButton*)GetDlgItem(IDC_SECOND_LOGIN))->EnableWindow(FALSE);
	}
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

void OnWindowDestroy(wkeWebView webWindow, void* param)
{
	Slider.notify_one();
}

bool OnNavigation(wkeWebView webView, void* param, wkeNavigationType navigationType, wkeString url)
{
	if (!memcmp(wkeGetString(url), "jsbridge://CAPTCHA/onVerifyCAPTCHA", 34))
	{
		const utf8* date = wkeUtilDecodeURLEscape(wkeGetString(url));
		rapidjson::Document Document;
		Document.Parse(date + 37, strlen(date + 37) - 2);
		Ticket = new char[Document["ticket"].GetStringLength() + 1];
		memcpy(Ticket, Document["ticket"].GetString(), Document["ticket"].GetStringLength() + 1);
		wkeDestroyWebView(webView);
		Slider.notify_one();
	}
	return true;
}

afx_msg LRESULT MainFrm::OnCreatewkewindows(WPARAM wParam, LPARAM lParam)
{
	wkeWebView wke = wkeCreateWebWindow(WKE_WINDOW_TYPE_POPUP, this->GetSafeHwnd(), 0, 0, 376, 396);
	wkeMoveToCenter(wke);
	wkeShowWindow(wke, true);
	wkeSetUserAgent(wke, (utf8*)u8"Mozilla/5.0 (iPhone; CPU iPhone OS 11_0 like Mac OS X) AppleWebKit/604.1.38 (KHTML, like Gecko) Version/11.0 Mobile/15A372 Safari/604.1");
	wkeLoadURL(wke, (const utf8*)lParam);
	wkeOnNavigation(wke, OnNavigation, NULL);
	wkeOnWindowDestroy(wke, OnWindowDestroy, NULL);
	return NULL;
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
		MainFrm->GetDlgItem(IDC_PASSWORD)->GetWindowTextW(Password, MainFrm->GetDlgItem(IDC_PASSWORD)->GetWindowTextLengthW() + 1);
		Sdk.QQ_Init(Iconv::Unicode2Ansi(QQ));
		state = Sdk.QQ_Login(Iconv::Unicode2Ansi(Password));
		delete[] Password;
	check:
		char SmsCode[7];
		switch (state)
		{
		case LOGIN_SUCCESS:
			Log::AddLog(Log::LogType::INFORMATION, Log::MsgType::OTHER, L"Login", L"Login Successfully!");
			goto online;
		case LOGIN_VERIY:
			Log::AddLog(Log::LogType::INFORMATION, Log::MsgType::OTHER, L"Login", L"Slider verification code");
			PostMessage(MainFrm->GetSafeHwnd(), WM_CREATE_WKE_WINDOWS, NULL, (LPARAM)Sdk.QQ_Get_Viery_Ticket());
			{
				std::mutex lock;
				std::unique_lock<std::mutex> ulock(lock);
				Slider.wait(ulock);
			}
			if (Ticket == nullptr)
			{
				Log::AddLog(Log::LogType::INFORMATION, Log::MsgType::OTHER, L"Login", L"Cancel Login");
				((CButton*)MainFrm->GetDlgItem(IDC_LOGIN))->EnableWindow(TRUE);
				return;
			}
			else
			{
				state = Sdk.QQ_Viery_Ticket(Ticket);
				delete[] Ticket;
				Ticket = nullptr;
				goto check;
			}
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
				//Todo
				state = Sdk.QQ_Viery_Sms(SmsCode);
				break;
			case IDCANCEL:
				((CButton*)MainFrm->GetDlgItem(IDC_LOGIN))->EnableWindow(TRUE);
				return;
			}
		case LOGIN_ERROR:
			Log::AddLog(Log::LogType::INFORMATION, Log::MsgType::OTHER, L"Login", L"Login failed");
			Log::AddLog(Log::LogType::INFORMATION, Log::MsgType::OTHER, L"Login", Iconv::Utf82Unicode(Sdk.QQ_GetErrorMsg()));
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
}