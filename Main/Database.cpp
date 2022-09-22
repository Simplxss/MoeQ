#include "Log.h"

#if defined(_WIN_PLATFORM_)
extern wchar_t DataPath[261];
#endif

#if defined(_LINUX_PLATFORM_)
extern char DataPath[261];
#endif

sqlite3 *Database_Data, *Database_Log = nullptr;

void Database::Init()
{
    char *zErrMsg = nullptr;
#if defined(_WIN_PLATFORM_)
    wchar_t DatabaseFilePath[261], DatabaseLogPath[261] = {0};

    wcscpy(DatabaseLogPath, DataPath);
    wcscat(DatabaseLogPath, L"log.db");
    if (sqlite3_open_v2((const char *)(Iconv::UnicodeToUtf8(DatabaseLogPath).c_str()), &Database_Log, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL) != SQLITE_OK)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Open Datebase 'log.db' error", (const char8_t *)zErrMsg);
        sqlite3_free(zErrMsg);
    };

    wcscpy(DatabaseFilePath, DataPath);
    wcscat(DatabaseFilePath, L"data.db");
    if (sqlite3_open_v2((const char *)(Iconv::UnicodeToUtf8(DatabaseFilePath).c_str()), &Database_Data, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL) != SQLITE_OK)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Open Datebase 'data.db' error", (const char8_t *)zErrMsg);
        sqlite3_free(zErrMsg);
    }
#endif

#if defined(_LINUX_PLATFORM_)
    char DatabaseFilePath[261], DatabaseLogPath[261] = {0};

    strcpy(DatabaseLogPath, DataPath);
    strcat(DatabaseLogPath, "log.db");
    if (sqlite3_open_v2(DatabaseLogPath, &Database_Log, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL) != SQLITE_OK)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Open Datebase 'log.db' error", (const char8_t *)zErrMsg);
        sqlite3_free(zErrMsg);
    };

    strcpy(DatabaseFilePath, DataPath);
    strcat(DatabaseFilePath, "data.db");
    if (sqlite3_open_v2(DatabaseFilePath, &Database_Data, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL) != SQLITE_OK)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Open Datebase 'data.db' error", (const char8_t *)zErrMsg);
        sqlite3_free(zErrMsg);
    }
#endif

    if (sqlite3_exec(Database_Log,
                     "CREATE TABLE IF NOT EXISTS Log("
                     "Time       INTEGER ,"
                     "LogType    INTEGER ,"
                     "MsgType    INTEGER ,"
                     "Type       TEXT    ,"
                     "Msg        TEXT    );",
                     0, 0, &zErrMsg) != SQLITE_OK)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Create table 'Log' error", (const char8_t *)zErrMsg);
        sqlite3_free(zErrMsg);
    }

    if (sqlite3_exec(Database_Data,
                     "CREATE TABLE IF NOT EXISTS PrivateMsg("
                     "ID         INTEGER  PRIMARY KEY  AUTOINCREMENT,"
                     "FromQQ     INTEGER     ,"
                     "SendTime   DATETIME    ,"
                     "State      INTEGER     ,"
                     "MsgType    INTEGER     ,"
                     "MsgID      INTEGER     ,"
                     "MsgRand    INTEGER     ,"
                     "Msg        TEXT        );",
                     0, 0, &zErrMsg) != SQLITE_OK)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Create table 'PrivateMsg' error", (const char8_t *)zErrMsg);
        sqlite3_free(zErrMsg);
    }

    if (sqlite3_exec(Database_Data,
                     "CREATE TABLE IF NOT EXISTS GroupMsg("
                     "ID         INTEGER  PRIMARY KEY  AUTOINCREMENT ,"
                     "FromGroup  INTEGER     ,"
                     "FromQQ     INTEGER     ,"
                     "SendTime   DATETIME    ,"
                     "State      INTEGER     ,"
                     "MsgType    INTEGER     ,"
                     "MsgID      INTEGER     ,"
                     "MsgRand    INTEGER     ,"
                     "Msg        TEXT        );",
                     0, 0, &zErrMsg) != SQLITE_OK)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Create table 'GroupMsg' error", (const char8_t *)zErrMsg);
        sqlite3_free(zErrMsg);
    }

    if (sqlite3_exec(Database_Data,
                     "CREATE TABLE IF NOT EXISTS FriendRequestMsg("
                     "ID         INTEGER  PRIMARY KEY  AUTOINCREMENT,"
                     "MsgSeq     INTEGER  UNIQUE,"
                     "FromQQ     INTEGER     ,"
                     "msg        TEXT        );",
                     0, 0, &zErrMsg) != SQLITE_OK)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Create table 'FriendRequestMsg' error", (const char8_t *)zErrMsg);
        sqlite3_free(zErrMsg);
    }

    if (sqlite3_exec(Database_Data,
                     "CREATE TABLE IF NOT EXISTS GroupRequestMsg("
                     "ID         INTEGER  PRIMARY KEY  AUTOINCREMENT,"
                     "MsgSeq     INTEGER  UNIQUE,"
                     "FromGroup  INTEGER     ,"
                     "FromQQ     INTEGER     ,"
                     "InvitorQQ  INTEGER     ,"
                     "msg        TEXT        );",
                     0, 0, &zErrMsg) != SQLITE_OK)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Create table 'GroupRequestMsg' error", (const char8_t *)zErrMsg);
        sqlite3_free(zErrMsg);
    }

    if (sqlite3_exec(Database_Data,
                     "CREATE TABLE IF NOT EXISTS Picture("
                     "MD5        CHAR(16) PRIMARY KEY ,"
                     "Url        TEXT         ,"
                     "Length     INTEGER      ,"
                     "Width      INTEGER      ,"
                     "Height     INTEGER      );",
                     0, 0, &zErrMsg) != SQLITE_OK)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Create table 'Picture' error", (const char8_t *)zErrMsg);
        sqlite3_free(zErrMsg);
    }

    if (sqlite3_exec(Database_Data,
                     "CREATE TABLE IF NOT EXISTS Voice("
                     "MD5        CHAR(16) PRIMARY KEY ,"
                     "Url        TEXT         );",
                     0, 0, &zErrMsg) != SQLITE_OK)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Create table 'Voice' error", (const char8_t *)zErrMsg);
        sqlite3_free(zErrMsg);
    }
}

void Database::UnInit()
{
    sqlite3_close(Database_Data);
    sqlite3_close(Database_Log);
}

uint64_t Database::AddPrivateMsg(const Event::PrivateMsg *PrivateMsg)
{
    sqlite3_stmt *pStmt;
    if (sqlite3_prepare_v2(Database_Data,
                           "INSERT INTO PrivateMsg(FromQQ,SendTime,State,MsgType,MsgID,MsgRand,Msg) VALUES(?,?,0,?,?,?,?);", 95, &pStmt, nullptr) != SQLITE_OK)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Insert into 'PrivateMsg' error", (const char8_t *)sqlite3_errmsg(Database_Data));
        return 0;
    }

    sqlite3_bind_int64(pStmt, 1, PrivateMsg->FromQQ);
    sqlite3_bind_int64(pStmt, 2, PrivateMsg->SendTime);
    sqlite3_bind_int64(pStmt, 3, PrivateMsg->MsgType);
    sqlite3_bind_int64(pStmt, 4, PrivateMsg->MsgID);
    sqlite3_bind_int64(pStmt, 5, PrivateMsg->MsgRand);
    std::u8string Msg = Message::ParseMsg(PrivateMsg->Msg);
    sqlite3_bind_text(pStmt, 6, (char *)Msg.c_str(), Msg.length(), SQLITE_STATIC);

    if (sqlite3_step(pStmt) != SQLITE_DONE)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Insert into 'PrivateMsg' error", (const char8_t *)sqlite3_errmsg(Database_Data));
        sqlite3_finalize(pStmt);
        return 0;
    }
    uint64_t MsgID = sqlite3_last_insert_rowid(Database_Data);
    sqlite3_finalize(pStmt);

    Log::AddLog(Log::LogType::INFORMATION, Log::MsgType::PRIVATE, u8"Simple Message", Msg.c_str());

    return MsgID;
}

uint64_t Database::AddGroupMsg(const Event::GroupMsg *GroupMsg)
{
    sqlite3_stmt *pStmt;
    if (sqlite3_prepare_v2(Database_Data,
                           "INSERT INTO GroupMsg(FromGroup,FromQQ,SendTime,State,MsgType,MsgID,MsgRand,Msg) VALUES(?,?,?,0,?,?,?,?);", 105, &pStmt, nullptr) != SQLITE_OK)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Insert into 'GroupMsg' error", (const char8_t *)sqlite3_errmsg(Database_Data));
        return 0;
    }

    sqlite3_bind_int64(pStmt, 1, GroupMsg->FromGroup);
    sqlite3_bind_int64(pStmt, 2, GroupMsg->FromQQ);
    sqlite3_bind_int64(pStmt, 3, GroupMsg->SendTime);
    sqlite3_bind_int64(pStmt, 4, GroupMsg->MsgType);
    sqlite3_bind_int64(pStmt, 5, GroupMsg->MsgID);
    sqlite3_bind_int64(pStmt, 6, GroupMsg->MsgRand);
    std::u8string Msg = Message::ParseMsg(GroupMsg->Msg);
    sqlite3_bind_text(pStmt, 7, (char *)Msg.c_str(), Msg.length(), SQLITE_STATIC);

    if (sqlite3_step(pStmt) != SQLITE_DONE)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Insert into 'GroupMsg' error", (const char8_t *)sqlite3_errmsg(Database_Data));
        sqlite3_finalize(pStmt);
        return 0;
    }
    uint64_t MsgID = sqlite3_last_insert_rowid(Database_Data);
    sqlite3_finalize(pStmt);

    Log::AddLog(Log::LogType::INFORMATION, Log::MsgType::_GROUP, u8"Simple Message", Msg.c_str());

    return MsgID;
}

uint64_t Database::AddRequestMsg(const Event::RequestEvent::RequestEvent *RequestMsg, const int64_t MsgSeq)
{
    sqlite3_stmt *pStmt;
    uint64_t responseFlag = 0;
    switch (RequestMsg->RequestEventType)
    {
    case Event::RequestEvent::RequestEventType::add_friend:
        if (sqlite3_prepare_v2(Database_Data,
                               "INSERT INTO FriendRequestMsg(MsgSeq,FromQQ,msg) VALUES(?,?,?);", 63, &pStmt, nullptr) != SQLITE_OK)
        {
            Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Insert into 'FriendRequestMsg' error", (const char8_t *)sqlite3_errmsg(Database_Data));
            return 0;
        }

        sqlite3_bind_int64(pStmt, 1, MsgSeq);
        sqlite3_bind_int64(pStmt, 2, ((Event::RequestEvent::add_friend *)RequestMsg->Information)->FromQQ);
        sqlite3_bind_text(pStmt, 3, (char *)((Event::RequestEvent::add_friend *)RequestMsg->Information)->msg, strlen((char *)((Event::RequestEvent::add_friend *)RequestMsg->Information)->msg), SQLITE_STATIC);

        if (sqlite3_step(pStmt) != SQLITE_DONE)
        {
            Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Insert into 'FriendRequestMsg' error", (const char8_t *)sqlite3_errmsg(Database_Data));
            sqlite3_finalize(pStmt);
            return 0;
        }
        responseFlag = sqlite3_last_insert_rowid(Database_Data);
        sqlite3_finalize(pStmt);
        break;
    case Event::RequestEvent::RequestEventType::self_invited:
        if (sqlite3_prepare_v2(Database_Data,
                               "INSERT INTO GroupRequestMsg(MsgSeq,FromGroup,InvitorQQ) VALUES(?,?,?);", 71, &pStmt, nullptr) != SQLITE_OK)
        {
            Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Insert into 'GroupRequestMsg' error", (const char8_t *)sqlite3_errmsg(Database_Data));
            return 0;
        }

        sqlite3_bind_int64(pStmt, 1, MsgSeq);
        sqlite3_bind_int64(pStmt, 2, ((Event::RequestEvent::self_invited *)RequestMsg->Information)->FromGroup);
        sqlite3_bind_int64(pStmt, 3, ((Event::RequestEvent::self_invited *)RequestMsg->Information)->InvitorQQ);
        if (sqlite3_step(pStmt) != SQLITE_DONE)
        {
            Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Insert into 'GroupRequestMsg' error", (const char8_t *)sqlite3_errmsg(Database_Data));
            sqlite3_finalize(pStmt);
            return 0;
        }
        responseFlag = sqlite3_last_insert_rowid(Database_Data);
        sqlite3_finalize(pStmt);
        break;
    case Event::RequestEvent::RequestEventType::other_join_group:
        if (sqlite3_prepare_v2(Database_Data,
                               "INSERT INTO GroupRequestMsg(MsgSeq,FromGroup,FromQQ,InvitorQQ,msg) VALUES(?,?,?,?,?);", 86, &pStmt, nullptr) != SQLITE_OK)
        {
            Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Insert into 'GroupRequestMsg' error", (const char8_t *)sqlite3_errmsg(Database_Data));
            return 0;
        }

        sqlite3_bind_int64(pStmt, 1, MsgSeq);
        sqlite3_bind_int64(pStmt, 2, ((Event::RequestEvent::other_join_group *)RequestMsg->Information)->FromGroup);
        sqlite3_bind_int64(pStmt, 3, ((Event::RequestEvent::other_join_group *)RequestMsg->Information)->FromQQ);
        sqlite3_bind_int64(pStmt, 4, ((Event::RequestEvent::other_join_group *)RequestMsg->Information)->InvitorQQ);
        sqlite3_bind_text(pStmt, 5, (char *)((Event::RequestEvent::other_join_group *)RequestMsg->Information)->msg, strlen((char *)((Event::RequestEvent::other_join_group *)RequestMsg->Information)->msg), SQLITE_STATIC);

        if (sqlite3_step(pStmt) != SQLITE_DONE)
        {
            Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Insert into 'GroupRequestMsg' error", (const char8_t *)sqlite3_errmsg(Database_Data));
            sqlite3_finalize(pStmt);
            return 0;
        }
        responseFlag = sqlite3_last_insert_rowid(Database_Data);
        sqlite3_finalize(pStmt);
        break;
    default:
        break;
    }

    Log::AddLog(Log::LogType::INFORMATION, Log::MsgType::OTHER, RequestMsg);

    return responseFlag;
}

void Database::AddPicture(const char MD5[16], const char8_t *Url, const unsigned short Length, const unsigned short Width, const unsigned short Height)
{
    sqlite3_stmt *pStmt;
    if (sqlite3_prepare_v2(Database_Data,
                           "INSERT OR REPLACE INTO Picture(MD5,Url,Length,Width,Height) VALUES(?,?,?,?,?)", 78, &pStmt, nullptr) != SQLITE_OK)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Insert into 'Picture' error", (const char8_t *)sqlite3_errmsg(Database_Data));
        return;
    }

    sqlite3_bind_blob(pStmt, 1, MD5, 16, SQLITE_STATIC);
    sqlite3_bind_text(pStmt, 2, (char *)Url, -1, SQLITE_STATIC);
    sqlite3_bind_int(pStmt, 3, Length);
    sqlite3_bind_int(pStmt, 4, Width);
    sqlite3_bind_int(pStmt, 5, Height);

    if (sqlite3_step(pStmt) != SQLITE_DONE)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Insert into 'Picture' error", (const char8_t *)sqlite3_errmsg(Database_Data));
        sqlite3_finalize(pStmt);
        return;
    }
    sqlite3_finalize(pStmt);
}

void Database::AddVoice(const char MD5[16], const char8_t *Url)
{
    sqlite3_stmt *pStmt;
    if (sqlite3_prepare_v2(Database_Data,
                           "INSERT OR REPLACE INTO Voice(MD5,Url) VALUES(?,?)", 50, &pStmt, nullptr) != SQLITE_OK)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Insert into 'Voice' error", (const char8_t *)sqlite3_errmsg(Database_Data));
        return;
    }

    sqlite3_bind_blob(pStmt, 1, MD5, 16, SQLITE_STATIC);
    sqlite3_bind_text(pStmt, 2, (char *)Url, -1, SQLITE_STATIC);

    if (sqlite3_step(pStmt) != SQLITE_DONE)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Insert into 'Voice' error", (const char8_t *)sqlite3_errmsg(Database_Data));
        sqlite3_finalize(pStmt);
        return;
    }
    sqlite3_finalize(pStmt);
}

void Database::AddLog(const Log::LogType LogType, const Log::MsgType MsgType, const char8_t *Type, const char8_t *Msg)
{
    sqlite3_stmt *pStmt;
    if (sqlite3_prepare_v2(Database_Log,
                           "INSERT INTO Log(Time,LogType,MsgType,Type,Msg) VALUES(?,?,?,?,?);", 66, &pStmt, nullptr) != SQLITE_OK)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Insert into 'Log' error", (const char8_t *)sqlite3_errmsg(Database_Log));
        return;
    }
    sqlite3_bind_int64(pStmt, 1, time(NULL));
    sqlite3_bind_int64(pStmt, 2, static_cast<int>(LogType));
    sqlite3_bind_int64(pStmt, 3, static_cast<int>(MsgType));
    sqlite3_bind_text(pStmt, 4, (const char *)Type, -1, 0);
    sqlite3_bind_text(pStmt, 5, (const char *)Msg, -1, 0);

    if (sqlite3_step(pStmt) != SQLITE_DONE)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Insert into 'Log' error", (const char8_t *)sqlite3_errmsg(Database_Log));
        sqlite3_finalize(pStmt);
        return;
    }
    sqlite3_finalize(pStmt);
}

std::tuple<uint, uint> Database::GetPrivateMsg(const uint64_t MsgID_)
{
    sqlite3_stmt *pStmt;
    if (sqlite3_prepare_v2(Database_Data, "SELECT MsgID,MsgRand FROM PrivateMsg WHERE ID = ?", 50, &pStmt, nullptr) != SQLITE_OK)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Select 'PrivateMsg' error", (const char8_t *)sqlite3_errmsg(Database_Data));
        return {0, 0};
    }

    sqlite3_bind_int64(pStmt, 1, MsgID_);

    if (sqlite3_step(pStmt) != SQLITE_ROW)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Select 'PrivateMsg' error", (const char8_t *)sqlite3_errmsg(Database_Data));
        sqlite3_finalize(pStmt);
        return {0, 0};
    }

    uint MsgID = sqlite3_column_int64(pStmt, 0);
    uint MsgRand = sqlite3_column_int64(pStmt, 1);
    sqlite3_finalize(pStmt);

    return {MsgID, MsgRand};
}

std::tuple<uint, uint> Database::GetGroupMsg(const uint64_t MsgID_)
{
    sqlite3_stmt *pStmt;
    if (sqlite3_prepare_v2(Database_Data, "SELECT MsgID,MsgRand FROM GroupMsg WHERE ID = ?", 48, &pStmt, nullptr) != SQLITE_OK)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Select 'GroupMsg' error", (const char8_t *)sqlite3_errmsg(Database_Data));
        return {0, 0};
    }

    sqlite3_bind_int64(pStmt, 1, MsgID_);

    if (sqlite3_step(pStmt) != SQLITE_ROW)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Select 'GroupMsg' error", (const char8_t *)sqlite3_errmsg(Database_Data));
        sqlite3_finalize(pStmt);
        return {0, 0};
    }

    uint MsgID = sqlite3_column_int64(pStmt, 0);
    uint MsgRand = sqlite3_column_int64(pStmt, 1);
    sqlite3_finalize(pStmt);

    return {MsgID, MsgRand};
}

uint64_t Database::UpdataPrivateMsgState(uint MsgID, uint MsgRand)
{
    sqlite3_stmt *pStmt;
    if (sqlite3_prepare_v2(Database_Data, "SELECT ID FROM PrivateMsg WHERE MsgID = ? AND MsgRand = ?", 58, &pStmt, nullptr) != SQLITE_OK)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Select 'PrivateMsg' error", (const char8_t *)sqlite3_errmsg(Database_Data));
        return 0;
    }

    sqlite3_bind_int64(pStmt, 1, MsgID);
    sqlite3_bind_int64(pStmt, 2, MsgRand);

    if (sqlite3_step(pStmt) != SQLITE_DONE)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Select 'PrivateMsg' error", (const char8_t *)sqlite3_errmsg(Database_Data));
        sqlite3_finalize(pStmt);
        return 0;
    }
    
    uint MsgID_ = sqlite3_column_int64(pStmt, 0);

    if (sqlite3_prepare_v2(Database_Data, "UPDATE PrivateMsg SET State = 1 WHERE ID = ?", 45, &pStmt, nullptr) != SQLITE_OK)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Update 'PrivateMsg' error", (const char8_t *)sqlite3_errmsg(Database_Data));
        return 0;
    }

    sqlite3_bind_int64(pStmt, 1, MsgID_);

    if (sqlite3_step(pStmt) != SQLITE_DONE)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Update 'PrivateMsg' error", (const char8_t *)sqlite3_errmsg(Database_Data));
        sqlite3_finalize(pStmt);
        return 0;
    }

    sqlite3_finalize(pStmt);
    return MsgID_;
}

uint64_t Database::UpdataGroupMsgState(uint MsgID, uint MsgRand)
{
    sqlite3_stmt *pStmt;
    if (sqlite3_prepare_v2(Database_Data, "SELECT ID FROM GroupMsg WHERE MsgID = ? AND MsgRand = ?", 58, &pStmt, nullptr) != SQLITE_OK)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Select 'GroupMsg' error", (const char8_t *)sqlite3_errmsg(Database_Data));
        return 0;
    }

    sqlite3_bind_int64(pStmt, 1, MsgID);
    sqlite3_bind_int64(pStmt, 2, MsgRand);

    if (sqlite3_step(pStmt) != SQLITE_DONE)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Select 'GroupMsg' error", (const char8_t *)sqlite3_errmsg(Database_Data));
        sqlite3_finalize(pStmt);
        return 0;
    }
    
    uint MsgID_ = sqlite3_column_int64(pStmt, 0);

    if (sqlite3_prepare_v2(Database_Data, "UPDATE GroupMsg SET State = 1 WHERE ID = ?", 45, &pStmt, nullptr) != SQLITE_OK)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Update 'GroupMsg' error", (const char8_t *)sqlite3_errmsg(Database_Data));
        return 0;
    }

    sqlite3_bind_int64(pStmt, 1, MsgID_);

    if (sqlite3_step(pStmt) != SQLITE_DONE)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Update 'GroupMsg' error", (const char8_t *)sqlite3_errmsg(Database_Data));
        sqlite3_finalize(pStmt);
        return 0;
    }

    sqlite3_finalize(pStmt);
    return MsgID_;
}

std::tuple<uint, uint> Database::GetFriendRequestMsg(const uint64_t ResponseFlag)
{
    sqlite3_stmt *pStmt;
    if (sqlite3_prepare_v2(Database_Data, "SELECT MsgSeq,FromQQ FROM FriendRequestMsg WHERE ID = ?", 56, &pStmt, nullptr) != SQLITE_OK)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Select 'FriendRequestMsg' error", (const char8_t *)sqlite3_errmsg(Database_Data));
        return {0, 0};
    }

    sqlite3_bind_int64(pStmt, 1, ResponseFlag);

    if (sqlite3_step(pStmt) != SQLITE_ROW)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Select 'FriendRequestMsg' error", (const char8_t *)sqlite3_errmsg(Database_Data));
        sqlite3_finalize(pStmt);
        return {0, 0};
    }

    uint MsgSeq = sqlite3_column_int64(pStmt, 0);
    uint FromQQ = sqlite3_column_int64(pStmt, 1);
    sqlite3_finalize(pStmt);

    return {MsgSeq, FromQQ};
}

std::tuple<uint, uint, uint, uint> Database::GetGroupRequestMsg(const uint64_t ResponseFlag)
{
    sqlite3_stmt *pStmt;
    if (sqlite3_prepare_v2(Database_Data, "SELECT MsgSeq,FromGroup,FromQQ,InvitorQQ FROM GroupRequestMsg WHERE ID = ?", 56, &pStmt, nullptr) != SQLITE_OK)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Select 'GroupRequestMsg' error", (const char8_t *)sqlite3_errmsg(Database_Data));
        return {0, 0, 0, 0};
    }

    sqlite3_bind_int64(pStmt, 1, ResponseFlag);

    if (sqlite3_step(pStmt) != SQLITE_ROW)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Select 'GroupRequestMsg' error", (const char8_t *)sqlite3_errmsg(Database_Data));
        sqlite3_finalize(pStmt);
        return {0, 0, 0, 0};
    }

    uint MsgSeq = sqlite3_column_int64(pStmt, 0);
    uint FromGroup = sqlite3_column_int64(pStmt, 1);
    uint FromQQ = sqlite3_column_int64(pStmt, 2);
    uint InvitorQQ = sqlite3_column_int64(pStmt, 3);
    sqlite3_finalize(pStmt);

    return {MsgSeq, FromGroup, FromQQ, InvitorQQ};
}

std::u8string Database::GetPictureUrl(const char MD5[16])
{
    sqlite3_stmt *pStmt;
    if (sqlite3_prepare_v2(Database_Data, "SELECT Url FROM Picture WHERE Id = ?", 37, &pStmt, nullptr) != SQLITE_OK)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Select 'Picture' error", (const char8_t *)sqlite3_errmsg(Database_Data));
        return std::u8string();
    }

    sqlite3_bind_blob(pStmt, 1, MD5, 16, SQLITE_STATIC);

    if (sqlite3_step(pStmt) != SQLITE_ROW)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Select 'Picture' error", (const char8_t *)sqlite3_errmsg(Database_Data));
        sqlite3_finalize(pStmt);
        return std::u8string();
    }

    std::u8string Url = u8"http://gchat.qpic.cn";
    Url += (char8_t *)sqlite3_column_text(pStmt, 0);
    sqlite3_finalize(pStmt);

    return Url;
}

std::u8string Database::GetVoiceUrl(const char MD5[16])
{
    sqlite3_stmt *pStmt;
    if (sqlite3_prepare_v2(Database_Data, "SELECT Url FROM Voice WHERE Id = ?", 35, &pStmt, nullptr) != SQLITE_OK)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Select 'Voice' error", (const char8_t *)sqlite3_errmsg(Database_Data));
        return std::u8string();
    }

    sqlite3_bind_blob(pStmt, 1, MD5, 16, SQLITE_STATIC);

    if (sqlite3_step(pStmt) != SQLITE_ROW)
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"Select 'Voice' error", (const char8_t *)sqlite3_errmsg(Database_Data));
        sqlite3_finalize(pStmt);
        return std::u8string();
    }

    std::u8string Url = u8"http://grouptalk.c2c.qq.com";
    Url += (char8_t *)sqlite3_column_text(pStmt, 0);
    sqlite3_finalize(pStmt);

    return Url;
}
