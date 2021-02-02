#include "pch.h"
#include "Event.h"
#include "PluginSystem.h"

extern PluginSystem Plugin;
extern wchar_t DataPath[MAX_PATH + 1];

void Message::DestoryMsg(Message::Msg* Msg)
{
	while (Msg != nullptr)
	{
		switch (Msg->MsgType)
		{
		case Message::MsgType::text:
			if (((Message::text*)Msg->Message)->text != nullptr) delete[] ((Message::text*)Msg->Message)->text;
			break;
		case Message::MsgType::classcal_face:
			break;
		case Message::MsgType::expression:
			delete[]((Message::expression*)Msg->Message)->MD5;
			break;
		case Message::MsgType::picture:
			delete[]((Message::picture*)Msg->Message)->MD5;
			delete[]((Message::picture*)Msg->Message)->URL;
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

void Event::OnGroupMsg(const GroupMsg* GroupMsg)
{
	Target::Target Target{ Target::TargetType::group,(void*)new Target::group{GroupMsg->FromGroup,GroupMsg->FromQQ } };
	uint MsgID = Database::AddGroupMsg(GroupMsg);
	Plugin.BroadcastMessageEvent(&Target, GroupMsg->Msg, MsgID);
}

void Event::OnPrivateMsg(const PrivateMsg* PrivateMsg)
{
	Target::Target Target{ Target::TargetType::_private,(void*)new Target::_private{PrivateMsg->FromQQ,0 } };//Todo
	uint MsgID = Database::AddPrivateMsg(PrivateMsg);
	Plugin.BroadcastMessageEvent(&Target, PrivateMsg->Msg, MsgID);
}

void Event::OnNoticeMsg(const NoticeEvent::NoticeEvent* NoticeEvent)
{
	Plugin.BroadcastNoticeEvent(NoticeEvent);
}

void Event::OnRequestMsg(const RequestEvent::RequestEvent* RequestEvent)
{
	//Todo
	Plugin.BroadcastRequestEvent(RequestEvent,0);
}


sqlite3 *Database_Data, *Database_Log = nullptr;

void Database::Init()
{
	wchar_t DatabaseFilePath[MAX_PATH + 1], DatabaseLogPath[MAX_PATH + 1] = { 0 };

	wcscpy(DatabaseFilePath, DataPath);
	wcscat(DatabaseFilePath, L"data.db");
	sqlite3_open_v2(Iconv::Unicode2Utf8(DatabaseFilePath), &Database_Data, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, "");
	wcscpy(DatabaseLogPath, DataPath);
	wcscat(DatabaseLogPath, L"log.db");
	sqlite3_open_v2(Iconv::Unicode2Utf8(DatabaseLogPath), &Database_Log, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, "");
	
	char* zErrMsg = nullptr;
	if (sqlite3_exec(Database_Data,
		"CREATE TABLE IF NOT EXISTS GroupMsg("  \
		"ID         INTEGER  KEY ," \
		"FromGroup  INTEGER     ," \
		"FromQQ     INTEGER     ," \
		"SendTime   DATETIME    ," \
		"State      INTEGER     ," \
		"MsgType    INTEGER     ," \
		"MsgID      INTEGER     ," \
		"MsgRand    INTEGER     ," \
		"Msg        TEXT        ,);"
		, 0, 0, &zErrMsg) != SQLITE_OK)
	{
		Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, L"Create table 'GroupMsg' error", zErrMsg);
		sqlite3_free(zErrMsg);
	}

	if (sqlite3_exec(Database_Data,
		"CREATE TABLE IF NOT EXISTS PrivateMsg("  \
		"ID         INTEGER KEY ," \
		"FromQQ     INTEGER     ," \
		"SendTime   DATETIME    ," \
		"State      INTEGER     ," \
		"MsgType    INTEGER     ," \
		"MsgID      INTEGER     ," \
		"MsgRand    INTEGER     ," \
		"Msg        TEXT        ,);"
		, 0, 0, &zErrMsg) != SQLITE_OK)
	{
		Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, L"Create table 'PrivateMsg' error", zErrMsg);
		sqlite3_free(zErrMsg);
	}

	if (sqlite3_exec(Database_Data,
		"CREATE TABLE IF NOT EXISTS Picture("  \
		"MD5        CHAR(16) KEY ," \
		"Url        TEXT         ," \
		"Length     INTEGER      ," \
		"Width      INTEGER      ," \
		"Height     INTEGER      ,);"
		, 0, 0, &zErrMsg) != SQLITE_OK)
	{
		Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, L"Create table 'Picture' error", zErrMsg);
		sqlite3_free(zErrMsg);
	}

	if (sqlite3_exec(Database_Data,
		"CREATE TABLE IF NOT EXISTS Voice("  \
		"MD5        CHAR(16) KEY ," \
		"Url        TEXT         ,);"
		, 0, 0, &zErrMsg) != SQLITE_OK)
	{
		Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, L"Create table 'Voice' error", zErrMsg);
		sqlite3_free(zErrMsg);
	}

	if (sqlite3_exec(Database_Log,
		"CREATE TABLE IF NOT EXISTS Log("  \
		"LogType    INTEGER ," \
		"MsgType    INTEGER ," \
		"Type       TEXT    ," \
		"Msg        TEXT    ,);"
		, 0, 0, &zErrMsg) != SQLITE_OK)
	{
		Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, L"Create table 'Log' error", zErrMsg);
		sqlite3_free(zErrMsg);
	}
}

void Database::UnInit()
{
	sqlite3_close(Database_Data);
	sqlite3_close(Database_Log);
}

uint Database::AddPrivateMsg(const Event::PrivateMsg* PrivateMsg)
{

	return ;
}

uint Database::AddGroupMsg(const Event::GroupMsg* GroupMsg)
{
	
	return uint();
}

void Database::AddPicture(const char MD5[16], const char* Url, const unsigned short Length, const unsigned short Width, const unsigned short Height)
{

}

void Database::AddVoice(const char MD5[16], const char* Url)
{
}

void Database::AddLog(const Log::LogType LogType, const Log::MsgType MsgType, const wchar_t* Type, const wchar_t* Msg)
{
}