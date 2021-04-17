#include "Log.h"

std::atomic_int Semaphore = 0;
std::condition_variable cv;
std::queue<Log::Log> LogQueue;

#if defined(_WIN_PLATFORM_)
extern wchar_t DataPath[261];
#endif

#if defined(_LINUX_PLATFORM_)
extern char DataPath[261];
#endif

sqlite3* Database_Data, * Database_Log = nullptr;


std::u8string Message::ParseMsg(Message::Msg* Msg)
{
    std::u8string MsgSteam;
    do
    {
        switch (Msg->MsgType)
        {
        case Message::MsgType::text:
            if (((Message::text*)Msg->Message)->text != nullptr) MsgSteam += ((Message::text*)Msg->Message)->text;//Todo 内存泄露
            else
            {
                MsgSteam += u8"[MQ:at,qq=";
                MsgSteam += (char8_t*)std::to_string(((Message::text*)Msg->Message)->AtQQ).c_str();
                MsgSteam += u8"]";
            }
            break;
        case Message::MsgType::classcal_face:
            MsgSteam += u8"[MQ:cface,id=";
            MsgSteam += (char8_t*)std::to_string(((Message::classcal_face*)Msg->Message)->id).c_str();
            MsgSteam += u8"]";
            break;
        case Message::MsgType::expression:
            MsgSteam += u8"[MQ:expression,id=";
            MsgSteam += ((Message::expression*)Msg->Message)->id;
            MsgSteam += u8",MD5=";
            MsgSteam += (char8_t*)XBin::Bin2HexEx(((Message::expression*)Msg->Message)->MD5, 16);
            MsgSteam += u8"]";
            break;
        case Message::MsgType::picture:
            MsgSteam += u8"[MQ:picture,MD5=";
            MsgSteam += (char8_t*)XBin::Bin2HexEx(((Message::picture*)Msg->Message)->MD5, 16);
            MsgSteam += u8",Width=";
            MsgSteam += (char8_t*)std::to_string(((Message::picture*)Msg->Message)->Width).c_str();
            MsgSteam += u8",Height=";
            MsgSteam += (char8_t*)std::to_string(((Message::picture*)Msg->Message)->Height).c_str();
            MsgSteam += u8",Length=";
            MsgSteam += (char8_t*)std::to_string(((Message::picture*)Msg->Message)->Data.Length).c_str();
            MsgSteam += u8"]";
            break;
        case Message::MsgType::xml:
            MsgSteam += u8"[MQ:xml,text=";
            MsgSteam += ((Message::xml*)Msg->Message)->text;
            MsgSteam += u8"]";
            break;
        case Message::MsgType::reply:
            MsgSteam += u8"[MQ:reply,MsgId=";
            MsgSteam += (char8_t*)std::to_string(((Message::reply*)Msg->Message)->MsgId).c_str();
            MsgSteam += u8",QQ=";
            MsgSteam += (char8_t*)std::to_string(((Message::reply*)Msg->Message)->QQ).c_str();
            MsgSteam += u8",Time=";
            MsgSteam += (char8_t*)std::to_string(((Message::reply*)Msg->Message)->Time).c_str();
            MsgSteam += u8",Msg=";
            {
                const Message::Msg* ReplyMsg = ((Message::reply*)Msg->Message)->Msg;
                do
                {
                    switch (ReplyMsg->MsgType)
                    {
                    case Message::MsgType::text:
                        MsgSteam += ((Message::text*)ReplyMsg->Message)->text;//Todo 内存泄露
                        break;
                    case Message::MsgType::classcal_face:
                        MsgSteam += u8"[MQ:cface,id=";
                        MsgSteam += (char8_t*)std::to_string(((Message::classcal_face*)ReplyMsg->Message)->id).c_str();
                        MsgSteam += u8"]";
                        break;
                    }
                    ReplyMsg->NextPoint;
                } while ((ReplyMsg = ReplyMsg->NextPoint) != nullptr);
            }
            MsgSteam += u8"]";
            break;
        case Message::MsgType::json:
            MsgSteam += u8"[MQ:json,text=";
            MsgSteam += ((Message::json*)Msg->Message)->text;
            MsgSteam += u8"]";
            break;
        default:
            break;
        }
    } while ((Msg = Msg->NextPoint) != nullptr);
    return MsgSteam;
}

void Message::DestoryMsg(Message::Msg* Msg)
{
    while (Msg != nullptr)
    {
        switch (Msg->MsgType)
        {
        case Message::MsgType::text:
            if (((Message::text*)Msg->Message)->text != nullptr) delete[]((Message::text*)Msg->Message)->text;
            break;
        case Message::MsgType::classcal_face:
            break;
        case Message::MsgType::expression:
            delete[]((Message::expression*)Msg->Message)->MD5;
            break;
        case Message::MsgType::picture:
            delete[]((Message::picture*)Msg->Message)->MD5;
            delete[]((Message::picture*)Msg->Message)->Data.URL;
            break;
        case Message::MsgType::xml:
            delete[]((Message::xml*)Msg->Message)->text;
            break;
        case Message::MsgType::reply:
        {
            Message::Msg* ReplyMsg = ((Message::reply*)Msg->Message)->Msg;
            while (ReplyMsg != nullptr)
            {
                switch (ReplyMsg->MsgType)
                {
                case Message::MsgType::text:
                    delete[]((Message::text*)ReplyMsg->Message)->text;
                    break;
                case Message::MsgType::classcal_face:
                    break;
                }
                delete ReplyMsg->Message;
                Message::Msg* tmp = ReplyMsg->NextPoint;
                delete ReplyMsg;
                ReplyMsg = tmp;
            }
        }
        break;
        case Message::MsgType::json:
            delete[]((Message::json*)Msg->Message)->text;
            break;
        default:
            break;
        }
        delete Msg->Message;
        Message::Msg* tmp = Msg->NextPoint;
        delete Msg;
        Msg = tmp;
    };
}


void Database::Init()
{
    #if defined(_WIN_PLATFORM_)
    char* zErrMsg = nullptr;
    wchar_t DatabaseFilePath[261], DatabaseLogPath[261] = { 0 };

    wcscpy(DatabaseLogPath, DataPath);
    wcscat(DatabaseLogPath, L"log.db");
    if (sqlite3_open_v2((const char*)(Iconv::UnicodeToUtf8(DatabaseLogPath).c_str()), &Database_Log, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL) != SQLITE_OK)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Open Datebase 'log.db' error", zErrMsg);
        sqlite3_free(zErrMsg);
    };

    wcscpy(DatabaseFilePath, DataPath);
    wcscat(DatabaseFilePath, L"data.db");
    if (sqlite3_open_v2((const char*)(Iconv::UnicodeToUtf8(DatabaseFilePath).c_str()), &Database_Data, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL) != SQLITE_OK)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Open Datebase 'data.db' error", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    #endif

    #if defined(_LINUX_PLATFORM_)
    char* zErrMsg = nullptr;
    char DatabaseFilePath[261], DatabaseLogPath[261] = { 0 };

    strcpy(DatabaseLogPath, DataPath);
    strcat(DatabaseLogPath, "log.db");
    if (sqlite3_open_v2(DatabaseLogPath, &Database_Log, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL) != SQLITE_OK)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Open Datebase 'log.db' error", zErrMsg);
        sqlite3_free(zErrMsg);
    };

    strcpy(DatabaseFilePath, DataPath);
    strcat(DatabaseFilePath, "data.db");
    if (sqlite3_open_v2(DatabaseFilePath, &Database_Data, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL) != SQLITE_OK)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Open Datebase 'data.db' error", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    #endif

    if (sqlite3_exec(Database_Log,
        "CREATE TABLE IF NOT EXISTS Log("  \
        "LogType    INTEGER ," \
        "MsgType    INTEGER ," \
        "Type       TEXT    ," \
        "Msg        TEXT    );"
        , 0, 0, &zErrMsg) != SQLITE_OK)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Create table 'Log' error", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    if (sqlite3_exec(Database_Data,
        "CREATE TABLE IF NOT EXISTS PrivateMsg("  \
        "ID         INTEGER  PRIMARY KEY  AUTOINCREMENT," \
        "FromQQ     INTEGER     ," \
        "SendTime   DATETIME    ," \
        "State      INTEGER     ," \
        "MsgType    INTEGER     ," \
        "MsgID      INTEGER     ," \
        "MsgRand    INTEGER     ," \
        "Msg        TEXT        );"
        , 0, 0, &zErrMsg) != SQLITE_OK)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Create table 'PrivateMsg' error", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    if (sqlite3_exec(Database_Data,
        "CREATE TABLE IF NOT EXISTS GroupMsg("  \
        "ID         INTEGER  PRIMARY KEY  AUTOINCREMENT ," \
        "FromGroup  INTEGER     ," \
        "FromQQ     INTEGER     ," \
        "SendTime   DATETIME    ," \
        "State      INTEGER     ," \
        "MsgType    INTEGER     ," \
        "MsgID      INTEGER     ," \
        "MsgRand    INTEGER     ," \
        "Msg        TEXT        );"
        , 0, 0, &zErrMsg) != SQLITE_OK)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Create table 'GroupMsg' error", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    if (sqlite3_exec(Database_Data,
        "CREATE TABLE IF NOT EXISTS Picture("  \
        "MD5        CHAR(16) PRIMARY KEY ," \
        "Url        TEXT         ," \
        "Length     INTEGER      ," \
        "Width      INTEGER      ," \
        "Height     INTEGER      );"
        , 0, 0, &zErrMsg) != SQLITE_OK)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Create table 'Picture' error", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    if (sqlite3_exec(Database_Data,
        "CREATE TABLE IF NOT EXISTS Voice("  \
        "MD5        CHAR(16) PRIMARY KEY ," \
        "Url        TEXT         );"
        , 0, 0, &zErrMsg) != SQLITE_OK)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Create table 'Voice' error", zErrMsg);
        sqlite3_free(zErrMsg);
    }
}

void Database::UnInit()
{
    sqlite3_close(Database_Data);
    sqlite3_close(Database_Log);
}

uint64_t Database::AddPrivateMsg(const Event::PrivateMsg* PrivateMsg)
{
    sqlite3_stmt* pStmt;
    if (sqlite3_prepare_v2(Database_Data,
        "INSERT INTO PrivateMsg(FromQQ,SendTime,State,MsgType,MsgID,MsgRand,Msg) VALUES(?,?,0,?,?,?,?);"
        , 95, &pStmt, nullptr) != SQLITE_OK) {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Insert into 'PrivateMsg' error", sqlite3_errmsg(Database_Data));
        return 0;
    }

    sqlite3_bind_int64(pStmt, 1, PrivateMsg->FromQQ);
    sqlite3_bind_int64(pStmt, 2, PrivateMsg->SendTime);
    sqlite3_bind_int64(pStmt, 3, PrivateMsg->MsgType);
    sqlite3_bind_int64(pStmt, 4, PrivateMsg->MsgID);
    sqlite3_bind_int64(pStmt, 5, PrivateMsg->MsgRand);
    std::u8string Msg = Message::ParseMsg(PrivateMsg->Msg);
    sqlite3_bind_text(pStmt, 6, (char*)Msg.c_str(), Msg.length(), SQLITE_STATIC);

    if (sqlite3_step(pStmt) != SQLITE_DONE) {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Insert into 'PrivateMsg' error", sqlite3_errmsg(Database_Data));
        sqlite3_finalize(pStmt);
        return 0;
    }
    uint MsgID = sqlite3_last_insert_rowid(Database_Data);
    sqlite3_finalize(pStmt);

    Log::AddLog(Log::LogType::INFORMATION, Log::MsgType::PRIVATE, u8"Simple Message", Msg.c_str());

    return(MsgID);
}

uint64_t Database::AddGroupMsg(const Event::GroupMsg* GroupMsg)
{
    sqlite3_stmt* pStmt;
    if (sqlite3_prepare_v2(Database_Data,
        "INSERT INTO GroupMsg(FromGroup,FromQQ,SendTime,State,MsgType,MsgID,MsgRand,Msg) VALUES(?,?,?,0,?,?,?,?);"
        , 105, &pStmt, nullptr) != SQLITE_OK) {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Insert into 'GroupMsg' error", sqlite3_errmsg(Database_Data));
        return 0;
    }

    sqlite3_bind_int64(pStmt, 1, GroupMsg->FromGroup);
    sqlite3_bind_int64(pStmt, 2, GroupMsg->FromQQ);
    sqlite3_bind_int64(pStmt, 3, GroupMsg->SendTime);
    sqlite3_bind_int64(pStmt, 4, GroupMsg->MsgType);
    sqlite3_bind_int64(pStmt, 5, GroupMsg->MsgID);
    sqlite3_bind_int64(pStmt, 6, GroupMsg->MsgRand);
    std::u8string Msg = Message::ParseMsg(GroupMsg->Msg);
    sqlite3_bind_text(pStmt, 7, (char*)Msg.c_str(), Msg.length(), SQLITE_STATIC);

    if (sqlite3_step(pStmt) != SQLITE_DONE) {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Insert into 'GroupMsg' error", sqlite3_errmsg(Database_Data));
        sqlite3_finalize(pStmt);
        return 0;
    }
    uint MsgID = sqlite3_last_insert_rowid(Database_Data);
    sqlite3_finalize(pStmt);

    Log::AddLog(Log::LogType::INFORMATION, Log::MsgType::_GROUP, u8"Simple Message", Msg.c_str());

    return(MsgID);
}

void Database::AddPicture(const char MD5[16], const char8_t* Url, const unsigned short Length, const unsigned short Width, const unsigned short Height)
{
    sqlite3_stmt* pStmt;
    if (sqlite3_prepare_v2(Database_Data,
        "INSERT OR REPLACE INTO Picture(MD5,Url,Length,Width,Height) VALUES(?,?,?,?,?)"
        , 78, &pStmt, nullptr) != SQLITE_OK) {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Insert into 'Picture' error", sqlite3_errmsg(Database_Data));
        return;
    }

    sqlite3_bind_blob(pStmt, 1, MD5, 16, SQLITE_STATIC);
    sqlite3_bind_text(pStmt, 2, (char*)Url, -1, SQLITE_STATIC);
    sqlite3_bind_int(pStmt, 3, Length);
    sqlite3_bind_int(pStmt, 4, Width);
    sqlite3_bind_int(pStmt, 5, Height);

    if (sqlite3_step(pStmt) != SQLITE_DONE) {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Insert into 'Picture' error", sqlite3_errmsg(Database_Data));
        sqlite3_finalize(pStmt);
        return;
    }
    sqlite3_finalize(pStmt);
}

void Database::AddVoice(const char MD5[16], const char8_t* Url)
{
    sqlite3_stmt* pStmt;
    if (sqlite3_prepare_v2(Database_Data,
        "INSERT OR REPLACE INTO Voice(MD5,Url) VALUES(?,?)"
        , 50, &pStmt, nullptr) != SQLITE_OK) {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Insert into 'Voice' error", sqlite3_errmsg(Database_Data));
        return;
    }

    sqlite3_bind_blob(pStmt, 1, MD5, 16, SQLITE_STATIC);
    sqlite3_bind_text(pStmt, 2, (char*)Url, -1, SQLITE_STATIC);

    if (sqlite3_step(pStmt) != SQLITE_DONE) {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Insert into 'Voice' error", sqlite3_errmsg(Database_Data));
        sqlite3_finalize(pStmt);
        return;
    }
    sqlite3_finalize(pStmt);

}

void Database::AddLog(const Log::LogType LogType, const Log::MsgType MsgType, const char8_t* Type, const char8_t* Msg)
{
    sqlite3_stmt* pStmt;
    if (sqlite3_prepare_v2(Database_Log,
        "INSERT INTO Log(LogType,MsgType,Type,Msg) VALUES(?,?,?,?);"
        , 59, &pStmt, nullptr) != SQLITE_OK) {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Insert into 'Log' error", sqlite3_errmsg(Database_Log));
        return;
    }
    sqlite3_bind_int64(pStmt, 1, static_cast<int>(LogType));
    sqlite3_bind_int64(pStmt, 2, static_cast<int>(MsgType));
    sqlite3_bind_text(pStmt, 3, (const char*)Type, -1, 0);
    sqlite3_bind_text(pStmt, 4, (const char*)Msg, -1, 0);

    if (sqlite3_step(pStmt) != SQLITE_DONE) {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Insert into 'Log' error", sqlite3_errmsg(Database_Log));
        sqlite3_finalize(pStmt);
        return;
    }
    sqlite3_finalize(pStmt);
}

std::tuple<uint, uint> Database::GetPrivateMsg(const uint64_t MsgID_)
{
    sqlite3_stmt* pStmt;
    if (sqlite3_prepare_v2(Database_Data, "SELECT MsgID,MsgRand FROM PrivateMsg WHERE Id = ?", 50, &pStmt, nullptr) != SQLITE_OK) {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Select 'PrivateMsg' error", sqlite3_errmsg(Database_Data));
        return { 0,0 };
    }

    sqlite3_bind_int64(pStmt, 1, MsgID_);

    if (sqlite3_step(pStmt) != SQLITE_ROW) {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Select 'PrivateMsg' error", sqlite3_errmsg(Database_Data));
        sqlite3_finalize(pStmt);
        return { 0,0 };
    }

    uint MsgID = sqlite3_column_int64(pStmt, 0);
    uint MsgRand = sqlite3_column_int64(pStmt, 1);
    sqlite3_finalize(pStmt);

    return { MsgID, MsgRand };
}

std::tuple<uint, uint> Database::GetGroupMsg(const uint64_t MsgID_)
{
    sqlite3_stmt* pStmt;
    if (sqlite3_prepare_v2(Database_Data, "SELECT MsgID,MsgRand FROM GroupMsg WHERE Id = ?", 48, &pStmt, nullptr) != SQLITE_OK) {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Select 'GroupMsg' error", sqlite3_errmsg(Database_Data));
        return { 0,0 };
    }

    sqlite3_bind_int64(pStmt, 1, MsgID_);

    if (sqlite3_step(pStmt) != SQLITE_ROW) {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Select 'GroupMsg' error", sqlite3_errmsg(Database_Data));
        sqlite3_finalize(pStmt);
        return { 0,0 };
    }

    uint MsgID = sqlite3_column_int64(pStmt, 0);
    uint MsgRand = sqlite3_column_int64(pStmt, 1);
    sqlite3_finalize(pStmt);

    return { MsgID, MsgRand };
}

std::u8string Database::GetPictureUrl(const char MD5[16])
{
    sqlite3_stmt* pStmt;
    if (sqlite3_prepare_v2(Database_Data, "SELECT Url FROM Picture WHERE Id = ?", 37, &pStmt, nullptr) != SQLITE_OK) {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Select 'Picture' error", sqlite3_errmsg(Database_Data));
        return std::u8string();
    }

    sqlite3_bind_blob(pStmt, 1, MD5, 16, SQLITE_STATIC);

    if (sqlite3_step(pStmt) != SQLITE_ROW) {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Select 'Picture' error", sqlite3_errmsg(Database_Data));
        sqlite3_finalize(pStmt);
        return std::u8string();
    }

    std::u8string Url = u8"http://gchat.qpic.cn";
    Url += (char8_t*)sqlite3_column_text(pStmt, 0);
    sqlite3_finalize(pStmt);

    return Url;
}

std::u8string Database::GetVoiceUrl(const char MD5[16])
{
    sqlite3_stmt* pStmt;
    if (sqlite3_prepare_v2(Database_Data, "SELECT Url FROM Voice WHERE Id = ?", 35, &pStmt, nullptr) != SQLITE_OK) {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Select 'Voice' error", sqlite3_errmsg(Database_Data));
        return std::u8string();
    }

    sqlite3_bind_blob(pStmt, 1, MD5, 16, SQLITE_STATIC);

    if (sqlite3_step(pStmt) != SQLITE_ROW) {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Select 'Voice' error", sqlite3_errmsg(Database_Data));
        sqlite3_finalize(pStmt);
        return std::u8string();
    }

    std::u8string Url = u8"http://grouptalk.c2c.qq.com";
    Url += (char8_t*)sqlite3_column_text(pStmt, 0);
    sqlite3_finalize(pStmt);

    return Url;
}


void Log::DesplayThread()
{
    std::mutex lock;
    std::unique_lock<std::mutex> ulock(lock);
    while (true)
    {
        cv.wait(ulock);
        while (Semaphore > 0)
        {
            Log Log_ = LogQueue.front();
            LogQueue.pop();
            switch (Log_.LogType) {
            case LogType::__DEBUG:
                std::wcout << L"Debug";
                break;
            case LogType::INFORMATION:
                std::wcout << L"Information";
                break;
            case LogType::NOTICE:
                std::wcout << L"Notice";
                break;
            case LogType::WARNING:
                std::wcout << L"Warning";
                break;
            case LogType::_ERROR:
                std::wcout << L"Error";
                break;
            }
            std::wcout << L" ";
            switch (Log_.MsgType)
            {
            case MsgType::OTHER:
                std::wcout << L"Other";
                break;
            case MsgType::_GROUP:
                std::wcout << L"Group";
                break;
            case MsgType::PRIVATE:
                std::wcout << L"Private";
                break;
            case MsgType::PROGRAM:
                std::wcout << L"Program";
                break;
            case MsgType::SERVER:
                std::wcout << L"Server";
                break;
            default:
                throw "Known MsgType";
                break;
            }
            std::cout << " " << (char*)Log_.Type.c_str() << " " << (char*)Log_.Msg.c_str() << std::endl;

            Database::AddLog(Log_.LogType, Log_.MsgType, Log_.Type.c_str(), Log_.Msg.c_str());
            --Semaphore;
        }
    }
}

void Log::Init()
{
    std::thread Thread(DesplayThread);
    Thread.detach();
}

#if defined(_WIN_PLATFORM_)

void Log::AddLog(const LogType LogType, const MsgType MsgType, const char* Type, const char* Msg)
{
    LogQueue.push(Log({LogType,MsgType,Iconv::AnsiToUtf8(Type),Iconv::AnsiToUtf8(Msg)}));
    ++Semaphore;
    cv.notify_one();
}

void Log::AddLog(const LogType LogType, const MsgType MsgType, const char* Type, const char8_t* Msg)
{
    LogQueue.push(Log({LogType,MsgType,Iconv::AnsiToUtf8(Type),Msg}));
    ++Semaphore;
    cv.notify_one();
}

void Log::AddLog(const LogType LogType, const MsgType MsgType, const char8_t* Type, const char* Msg)
{
    LogQueue.push(Log({LogType,MsgType,Type,Iconv::AnsiToUtf8(Msg)}));
    ++Semaphore;
    cv.notify_one();
}

void Log::AddLog(const LogType LogType, const MsgType MsgType, const wchar_t* Type, const wchar_t* Msg)
{
    LogQueue.push(Log({LogType,MsgType,Iconv::UnicodeToUtf8(Type),Iconv::UnicodeToUtf8(Msg)}));
    ++Semaphore;
    cv.notify_one();
}

#endif

void Log::AddLog(const LogType LogType, const MsgType MsgType, const char8_t* Type, const char8_t* Msg)
{
    LogQueue.push(Log({LogType,MsgType,Type,Msg}));
    ++Semaphore;
    cv.notify_one();
}

void Log::AddLog(const LogType LogType, const MsgType MsgType, const char8_t* Type, const char8_t* MsgFormat, ...)
{
    char8_t* Msg;
    va_list args;

    va_start(args, MsgFormat);
    vsprintf((char*)Msg, (char*)MsgFormat, args);
    va_end(args);

    LogQueue.push(Log({LogType,MsgType,Type,Msg}));
    ++Semaphore;
    cv.notify_one();
}

void Log::AddLog(const LogType LogType, const MsgType MsgType, const Event::NoticeEvent::NoticeEvent* NoticeEvent)
{
    std::u8string MsgSteam;
    switch (NoticeEvent->NoticeEventType)
    {
    case Event::NoticeEvent::NoticeEventType::group_fileupload:
        LogQueue.push(Log({LogType,MsgType,u8"group_fileupload",}));
        break;
    case Event::NoticeEvent::NoticeEventType::group_adminchange:
        MsgSteam += ((Event::NoticeEvent::group_adminchange*)NoticeEvent->Information)->FromGroup;
        MsgSteam += u8" ";
        MsgSteam += ((Event::NoticeEvent::group_adminchange*)NoticeEvent->Information)->FromQQ;
        MsgSteam += u8" ";
        MsgSteam += (((Event::NoticeEvent::group_adminchange*)NoticeEvent->Information)->Type ? u8"Set" : u8"UnSet");
        LogQueue.push(Log({LogType,MsgType,u8"group_adminchange",MsgSteam}));
        break;
    case Event::NoticeEvent::NoticeEventType::group_memberchange:
        MsgSteam += ((Event::NoticeEvent::group_memberchange*)NoticeEvent->Information)->FromGroup;
        MsgSteam += u8" ";
        MsgSteam += ((Event::NoticeEvent::group_memberchange*)NoticeEvent->Information)->FromQQ;
        MsgSteam += u8" ";
        MsgSteam += ((Event::NoticeEvent::group_memberchange*)NoticeEvent->Information)->OperateQQ;
        MsgSteam += u8" ";
        MsgSteam += ((Event::NoticeEvent::group_memberchange*)NoticeEvent->Information)->Type;
        LogQueue.push(Log({LogType,MsgType,u8"group_memberchange",MsgSteam}));
        break;
    case Event::NoticeEvent::NoticeEventType::group_mute:
        LogQueue.push(Log({LogType,MsgType,u8"group_mute",}));
        break;
    case Event::NoticeEvent::NoticeEventType::friend_added:
        LogQueue.push(Log({LogType,MsgType,u8"friend_added",}));
        break;
    }
    ++Semaphore;
    cv.notify_one();
}

void Log::AddLog(const LogType LogType, const MsgType MsgType, const Event::RequestEvent::RequestEvent* RequestEvent)
{
    std::u8string MsgSteam;
    switch (RequestEvent->RequestEventType)
    {
    case Event::RequestEvent::RequestEventType::add_friend:
        MsgSteam += ((Event::RequestEvent::add_friend*)RequestEvent->Information)->FromQQ;
        MsgSteam += u8" ";
        MsgSteam += ((Event::RequestEvent::add_friend*)RequestEvent->Information)->msg;
        LogQueue.push(Log({LogType,MsgType,u8"add_friend",MsgSteam}));
        break;
    case Event::RequestEvent::RequestEventType::add_group:
        MsgSteam += ((Event::RequestEvent::add_group*)RequestEvent->Information)->FromGroup;
        MsgSteam += u8" ";
        MsgSteam += ((Event::RequestEvent::add_group*)RequestEvent->Information)->FromQQ;
        MsgSteam += u8" ";
        MsgSteam += ((Event::RequestEvent::add_group*)RequestEvent->Information)->Type;
        //MsgSteam += ((Event::RequestEvent::add_group*)RequestEvent->Information)->msg;
        LogQueue.push(Log({LogType,MsgType,u8"add_group",MsgSteam}));
        break;
    }
    ++Semaphore;
    cv.notify_one();
}
