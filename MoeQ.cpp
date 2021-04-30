#include "MoeQ.h"

#if defined(_WIN_PLATFORM_)
wchar_t DataPath[MAX_PATH + 1];
#endif

#if defined(_LINUX_PLATFORM_)
char DataPath[PATH_MAX + 1];
#endif

bool DevMode = true;

PluginSystem Plugin;

//GUID 86A445BF44A2C287597618F6F36EB68C   MAC 4F923C3D4568   4F:92:3C:3D:45:68
Android Sdk("861891778567", "460013521635791", (const byte *)"\x86\xA4\x45\xBF\x44\xA2\xC2\x87\x59\x76\x18\xF6\xF3\x6E\xB6\x8C", (const byte *)"\x4F\x92\x3C\x3D\x45\x68", "Alpha", "XiaoMi");

void Debug()
{
}

void SaveToken(
#if defined(_WIN_PLATFORM_)
    const wchar_t *
#endif

#if defined(_LINUX_PLATFORM_)
    const char *
#endif
        QQ,
    const Android::Token *Token,
#if defined(_WIN_PLATFORM_)
    const wchar_t *
#endif

#if defined(_LINUX_PLATFORM_)
    const char *
#endif
        DataFilePath)
{

    rapidjson::Document d;
    d["QQ"].SetString((const char *)Iconv::UnicodeToUtf8(QQ).c_str(), Iconv::UnicodeToUtf8(QQ).length());
    d["A2"].SetString(rapidjson::StringRef(XBin::Bin2HexEx(Token->A2, 64), 128));
    d["TGTQQ"].SetString(rapidjson::StringRef(XBin::Bin2HexEx(Token->TGT, 72), 144));
    d["D2Key"].SetString(rapidjson::StringRef(XBin::Bin2HexEx(Token->D2Key, 16), 32));
    d["wtSessionTicket"].SetString(rapidjson::StringRef(XBin::Bin2HexEx(Token->wtSessionTicket, 48), 96));
    d["wtSessionTicketKey"].SetString(rapidjson::StringRef(XBin::Bin2HexEx(Token->wtSessionTicketKey, 56), 112));
    d["token_16A"].SetString(rapidjson::StringRef(XBin::Bin2HexEx(Token->token_16A, 16), 32));
    d["md5"].SetString(rapidjson::StringRef(XBin::Bin2HexEx(Token->md5, 16), 32));
    d["TGTkey"].SetString(rapidjson::StringRef(XBin::Bin2HexEx(Token->TGTkey, 16), 32));
    d["ksid"].SetString(rapidjson::StringRef(XBin::Bin2HexEx(Token->ksid, 16), 32));
#if defined(_WIN_PLATFORM_)
    std::ofstream output;
    output.open(DataFilePath);
    if (!output.is_open())
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"SaveData", u8"Save Json error");
    }
    output.write(d.GetString(), d.GetStringLength());
    output.close();
#endif

#if defined(_LINUX_PLATFORM_)
    std::ofstream output;
    output.open(DataFilePath);
    if (!output.is_open())
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"SaveData", u8"Save Json error");
    }
    output.write(d.GetString(), d.GetStringLength());
    output.close();
#endif
}

int main()
{
    Android::Token Token;
#if defined(_WIN_PLATFORM_)
    SetConsoleOutputCP(65001);
    wchar_t szFilePath[MAX_PATH + 1], DataFilePath[MAX_PATH + 1], DllFilePath[MAX_PATH + 1] = {0};
    _wgetcwd(szFilePath, MAX_PATH);
    wcscpy(DataPath, szFilePath);
    wcscat(DataPath, L"\\data\\");

    if (!std::filesystem::exists(DataPath))
        std::filesystem::create_directory(DataPath);

    Log::Init();
    Database::Init();
    Plugin.Load(szFilePath);

    wchar_t QQ[12];
    wchar_t str[256];
    char Json[10000] = {'0'};
    wcscpy(DataFilePath, DataPath);
    wcscat(DataFilePath, L"data.ini");

    std::ifstream input;
    input.open(DataFilePath);
    if (!input.is_open())
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadData", u8"Read Json error");
        goto login;
    }
    input.read(Json, 10000);
    if (input.gcount() == 10000)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadData", u8"Json is too big");
        input.close();
        goto login;
    }
    input.close();
#endif

#if defined(_LINUX_PLATFORM_)
    char szFilePath[PATH_MAX + 1], DataFilePath[PATH_MAX + 1], DllFilePath[PATH_MAX + 1] = {0};
    getcwd(szFilePath, PATH_MAX);
    strcpy(DataPath, szFilePath);
    strcat(DataPath, "/data/");

    if (!std::filesystem::exists(DataPath))
        std::filesystem::create_directory(DataPath);

    Log::Init();
    Database::Init();
    Plugin.Load(szFilePath);

    char QQ[12];
    char str[256];
    char Json[10000] = {'0'};
    strcpy(DataFilePath, DataPath);
    strcat(DataFilePath, "data.json");

    std::ifstream input;
    input.open(DataFilePath);
    if (!input.is_open())
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadData", u8"Read Json error");
        goto login;
    }
    input.read(Json, 10000);
    if (input.gcount() == 10000)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadData", u8"Json is too big");
        input.close();
        goto login;
    }
    input.close();

#endif

    try
    {
        rapidjson::Document d;
        d.Parse<rapidjson::kParseCommentsFlag>(Json);

        if (!d.HasParseError())
        {
            memcpy(QQ, d["QQ"].GetString(), d["QQ"].GetStringLength());

            if (XBin::Hex2BinEx(d["A2"].GetString(), Token.A2) != 64)
                throw "A2 len error";

            if (XBin::Hex2BinEx(d["TGT"].GetString(), Token.TGT) != 72)
                throw "TGT len error";

            if (XBin::Hex2BinEx(d["D2Key"].GetString(), Token.D2Key) != 16)
                throw "D2Key len error";

            if (XBin::Hex2BinEx(d["wtSessionTicket"].GetString(), Token.wtSessionTicket) != 48)
                throw "wtSessionTicket len error";

            if (XBin::Hex2BinEx(d["wtSessionTicketKey"].GetString(), Token.wtSessionTicketKey) != 16)
                throw "wtSessionTicketKey len error";

            if (XBin::Hex2BinEx(d["token_16A"].GetString(), Token.token_16A) != 56)
                throw "token_16A len error";

            if (XBin::Hex2BinEx(d["md5"].GetString(), Token.md5) != 16)
                throw "md5 len error";

            if (XBin::Hex2BinEx(d["TGTkey"].GetString(), Token.TGTkey) != 16)
                throw "TGTkey len error";

            if (XBin::Hex2BinEx(d["ksid"].GetString(), Token.ksid) != 16)
                throw "ksid len error";
        }
    }
    catch (...)
    {
    }

    if (true)
    {
#if defined(_WIN_PLATFORM_)
        Sdk.QQ_Init(Iconv::UnicodeToAnsi(QQ).c_str());
#endif
#if defined(_LINUX_PLATFORM_)
        Sdk.QQ_Init(QQ);
#endif
        Sdk.QQ_Set_Token(&Token);
        Sdk.QQ_Login_Second();
        Sdk.QQ_Login_Finish();
    }
    else
    {
    login:
        char Password[20];
        std::wcin >> QQ;
        std::cin >> Password;
        byte state;
        Sdk.QQ_Init(Iconv::UnicodeToAnsi(QQ).c_str());
        state = Sdk.QQ_Login(Password);
    check:
        char SmsCode[7], Ticket[200];
        switch (state)
        {
        case LOGIN_SUCCESS:
            Log::AddLog(Log::LogType::INFORMATION, Log::MsgType::OTHER, u8"Login", u8"Login Successfully!");
            goto online;
        case LOGIN_VERIY:
            Log::AddLog(Log::LogType::INFORMATION, Log::MsgType::OTHER, u8"Login", u8"Slider verification code");
            std::cout << Sdk.QQ_Get_Viery_Ticket();
            std::cin >> Ticket;
            state = Sdk.QQ_Viery_Ticket(Ticket);
            goto check;
        case LOGIN_VERIY_SMS:
            Log::AddLog(Log::LogType::INFORMATION, Log::MsgType::OTHER, u8"Login", u8"Driver Lock");
            char notice[200];
            strcpy(notice, "Send Sms to ");
            strcat(notice, Sdk.QQ_Get_Viery_PhoneNumber());
            strcat(notice, " ?");
            /*
            switch (MessageBoxA(nullptr, notice, "Driver Lock", MB_OKCANCEL))
            {
            case IDOK:
                Sdk.QQ_Send_Sms();
                std::cin >> SmsCode;
                state = Sdk.QQ_Viery_Sms(SmsCode);
                break;
            case IDCANCEL:
                return 0;
            }
            */
        case LOGIN_ERROR:
            Log::AddLog(Log::LogType::INFORMATION, Log::MsgType::OTHER, u8"Login", u8"Login failed");
            Log::AddLog(Log::LogType::INFORMATION, Log::MsgType::OTHER, u8"Login", Sdk.QQ_GetErrorMsg());
            return 0;
        default:
            break;
        }
        Sdk.QQ_Login_Finish();
    }
online:
    SaveToken(QQ, Sdk.QQ_Get_Token(), DataFilePath);

    Sdk.QQ_Online();
#if defined(DEBUG)
    Debug();
#endif

    char a[99];
    std::cin >> a;

    SaveToken(QQ, Sdk.QQ_Get_Token(), DataFilePath);

    return 0;
}