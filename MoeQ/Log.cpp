#include "pch.h"
#include "Log.h"

HANDLE hwnd;
std::atomic_int Semaphore = 0;
std::condition_variable cv;
std::queue<Log::Log> LogQueue;


extern wchar_t DataPath[MAX_PATH + 1];
sqlite3* Database_Data, * Database_Log = nullptr;

std::u8string Message::ParseMsg(Message::Msg* Msg)
{
	std::u8string MsgSteam;
	do
	{
		switch (Msg->MsgType)
		{
		case Message::MsgType::text:
			if (((Message::text*)Msg->Message)->text != nullptr) MsgSteam += ((Message::text*)Msg->Message)->text;//Todo ÄÚ´æÐ¹Â¶
			else
			{
				MsgSteam += u8"[MQ:at,qq=";
				MsgSteam += ((Message::text*)Msg->Message)->AtQQ;
				MsgSteam += u8"]";
			}
			break;
		case Message::MsgType::classcal_face:
			MsgSteam += u8"[MQ:cface,id=";
			MsgSteam += ((Message::classcal_face*)Msg->Message)->id;
			MsgSteam += u8"]";
			break;
		case Message::MsgType::expression:
			MsgSteam += u8"[MQ:expression,id=";
			MsgSteam += ((Message::expression*)Msg->Message)->id;
			MsgSteam += u8",MD5=";
			MsgSteam += (char8_t*)XBin::Bin2Hex(((Message::expression*)Msg->Message)->MD5, 16);
			MsgSteam += u8"]";
			break;
		case Message::MsgType::picture:
			MsgSteam += u8"[MQ:picture,MD5=";
			MsgSteam += (char8_t*)XBin::Bin2Hex(((Message::picture*)Msg->Message)->MD5, 16);
			MsgSteam += u8",Width=";
			MsgSteam += ((Message::picture*)Msg->Message)->Width;
			MsgSteam += u8",Height=";
			MsgSteam += ((Message::picture*)Msg->Message)->Height;
			MsgSteam += u8",Length=";
			MsgSteam += ((Message::picture*)Msg->Message)->Data.Length;
			MsgSteam += u8"]";
			break;
		case Message::MsgType::xml:
			MsgSteam += u8"[MQ:xml,text=";
			MsgSteam += ((Message::xml*)Msg->Message)->text;
			MsgSteam += u8"]";
			break;
		case Message::MsgType::reply:
			MsgSteam += u8"[MQ:reply,MsgId=";
			MsgSteam += ((Message::reply*)Msg->Message)->MsgId;
			MsgSteam += u8",QQ=";
			MsgSteam += ((Message::reply*)Msg->Message)->QQ;
			MsgSteam += u8",Time=";
			MsgSteam += ((Message::reply*)Msg->Message)->Time;
			MsgSteam += u8",Msg=";
			{
				const Message::Msg* ReplyMsg = ((Message::reply*)Msg->Message)->Msg;
				do
				{
					switch (ReplyMsg->MsgType)
					{
					case Message::MsgType::text:
						MsgSteam += ((Message::text*)ReplyMsg->Message)->text;//Todo ÄÚ´æÐ¹Â¶
						break;
					case Message::MsgType::classcal_face:
						MsgSteam += u8"[MQ:cface,id=";
						MsgSteam += ((Message::classcal_face*)ReplyMsg->Message)->id;
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
	char* zErrMsg = nullptr;
	wchar_t DatabaseFilePath[MAX_PATH + 1], DatabaseLogPath[MAX_PATH + 1] = { 0 };

	wcscpy(DatabaseFilePath, DataPath);
	wcscat(DatabaseFilePath, L"data.db");
	if (sqlite3_open_v2(Iconv::Unicode2Utf8(DatabaseFilePath), &Database_Data, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL) != SQLITE_OK)
	{
		//error
	}
	wcscpy(DatabaseLogPath, DataPath);
	wcscat(DatabaseLogPath, L"log.db");
	if (sqlite3_open_v2(Iconv::Unicode2Utf8(DatabaseLogPath), &Database_Log, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL) != SQLITE_OK)
	{
		//error
	};


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
		Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, L"Create table 'PrivateMsg' erroru8", zErrMsg);
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
		Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, L"Create table 'GroupMsg' erroru8", zErrMsg);
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
		Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, L"Create table 'Picture' erroru8", zErrMsg);
		sqlite3_free(zErrMsg);
	}

	if (sqlite3_exec(Database_Data,
		"CREATE TABLE IF NOT EXISTS Voice("  \
		"MD5        CHAR(16) PRIMARY KEY ," \
		"Url        TEXT         );"
		, 0, 0, &zErrMsg) != SQLITE_OK)
	{
		Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, L"Create table 'Voice' erroru8", zErrMsg);
		sqlite3_free(zErrMsg);
	}

	if (sqlite3_exec(Database_Log,
		"CREATE TABLE IF NOT EXISTS Log("  \
		"LogType    INTEGER ," \
		"MsgType    INTEGER ," \
		"Type       TEXT    ," \
		"Msg        TEXT    );"
		, 0, 0, &zErrMsg) != SQLITE_OK)
	{
		Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, L"Create table 'Log' erroru8", zErrMsg);
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
	sqlite3_stmt* pStmt;
	if (sqlite3_prepare16_v2(Database_Data,
		"INSERT INTO PrivateMsg(FromQQ,SendTime,State,MsgType,MsgID,MsgRand,Msg) VALUES(?,?,0,?,?,?,?,?);"
		, -1, &pStmt, nullptr) != SQLITE_OK){
		Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, L"Insert into 'PrivateMsg' error", sqlite3_errmsg(Database_Data));
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
		Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, L"Insert into 'PrivateMsg' error", sqlite3_errmsg(Database_Data));
		sqlite3_finalize(pStmt);
		return 0;
	}
	sqlite3_finalize(pStmt);

	//std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
	Log::AddLog(Log::LogType::INFORMATION, Log::MsgType::PRIVATE, L"Simple Message", Iconv::Utf82Unicode((char*)Msg.c_str()));


}

uint Database::AddGroupMsg(const Event::GroupMsg* GroupMsg)
{
	sqlite3_stmt* pStmt;
	if (sqlite3_prepare16_v2(Database_Data,
		"INSERT INTO GroupMsg(FromGroup,FromQQ,SendTime,State,MsgType,MsgID,MsgRand,Msg) VALUES(?,?,?,0,?,?,?,?,?);"
		, -1, &pStmt, nullptr) != SQLITE_OK) {
		Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, L"Insert into 'GroupMsg' error", sqlite3_errmsg(Database_Data));
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
		Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, L"Insert into 'GroupMsg' error", sqlite3_errmsg(Database_Data));
		sqlite3_finalize(pStmt);
		return 0;
	}
	sqlite3_finalize(pStmt);

	//std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
	Log::AddLog(Log::LogType::INFORMATION, Log::MsgType::_GROUP, L"Simple Message", Iconv::Utf82Unicode((char*)Msg.c_str()));
}

void Database::AddPicture(const char MD5[16], const char* Url, const unsigned short Length, const unsigned short Width, const unsigned short Height)
{

}

void Database::AddVoice(const char MD5[16], const char* Url)
{
}

void Database::AddLog(const Log::LogType LogType, const Log::MsgType MsgType, const wchar_t* Type, const wchar_t* Msg)
{
	sqlite3_stmt* pStmt;
	if (sqlite3_prepare16_v2(Database_Log,
		"INSERT INTO Log(LogType,MsgType,Type,Msg) VALUES(?,?,?,?)"
		, -1, &pStmt, nullptr) != SQLITE_OK) {
		Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, L"Insert into 'Log' error", sqlite3_errmsg(Database_Log));
		return;
	}
	sqlite3_bind_int64(pStmt, 1, static_cast<int>(LogType));
	sqlite3_bind_int64(pStmt, 2, static_cast<int>(MsgType));
	sqlite3_bind_text(pStmt, 3, Iconv::Unicode2Utf8(Type), -1, 0);
	sqlite3_bind_text(pStmt, 4, Iconv::Unicode2Utf8(Msg), -1, 0);

	if (sqlite3_step(pStmt) != SQLITE_DONE) {
		Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, L"Insert into 'Log' error", sqlite3_errmsg(Database_Log));
		sqlite3_finalize(pStmt);
		return;
	}
	sqlite3_finalize(pStmt);
}

Event::PrivateMsg* Database::GetPrivateMsg(const uint MsgID)
{
	return nullptr;
}

Event::GroupMsg* Database::GetGroupMsg(const uint MsgID)
{
	return nullptr;
}

std::string Database::GetPictureUrl(const char MD5[16])
{
	return std::string();
}

std::string Database::GetVoiceUrl(const char MD5[16])
{
	return std::string();
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
			CListCtrl* LogList = (CListCtrl*)((CDialog*)hwnd)->GetDlgItem(IDC_LOG);
			int Index = LogList->InsertItem(0, L"");
			if (Index < 0)	return;
			Log Log_ = LogQueue.front();
			LogQueue.pop();
			switch (Log_.LogType) {
			case LogType::__DEBUG:
				LogList->SetItemText(Index, 0, L"Debug");
				break;
			case LogType::INFORMATION:
				LogList->SetItemText(Index, 0, L"Information");
				break;
			case LogType::NOTICE:
				LogList->SetItemText(Index, 0, L"Notice");
				break;
			case LogType::WARNING:
				LogList->SetItemText(Index, 0, L"Warning");
				break;
			case LogType::_ERROR:
				LogList->SetItemText(Index, 0, L"Error");
				break;
			}
			switch (Log_.MsgType)
			{
			case MsgType::OTHER:
				LogList->SetItemText(Index, 1, L"Other");
				break;
			case MsgType::_GROUP:
				LogList->SetItemText(Index, 1, L"Group");
				break;
			case MsgType::PRIVATE:
				LogList->SetItemText(Index, 1, L"Private");
				break;
			case MsgType::PROGRAM:
				LogList->SetItemText(Index, 1, L"Program");
				break;
			case MsgType::SERVER:
				LogList->SetItemText(Index, 1, L"Server");
				break;
			default:
				throw "Known MsgType";
				break;
			}
			LogList->SetItemText(Index, 2, Log_.Type);
			LogList->SetItemText(Index, 3, Log_.Msg);
			Database::AddLog(Log_.LogType, Log_.MsgType, Log_.Type, Log_.Msg);
			--Semaphore;
		}
	}
}

void Log::Init(HANDLE Handle)
{
	hwnd = Handle;
	std::thread Thread(DesplayThread);
	Thread.detach();
}

void Log::AddLog(const LogType LogType, const MsgType MsgType, const char* Type, const char* Msg)
{
	Log Log_;
	Log_.LogType = LogType;
	Log_.MsgType = MsgType;
	Log_.Type = Iconv::Ansi2Unicode(Type);
	Log_.Msg = Iconv::Ansi2Unicode(Msg);

	LogQueue.push(Log_);
	++Semaphore;
	cv.notify_one();
}

void Log::AddLog(const LogType LogType, const MsgType MsgType, const char* Type, const wchar_t* Msg)
{
	Log Log_;
	Log_.LogType = LogType;
	Log_.MsgType = MsgType;
	Log_.Type = Iconv::Ansi2Unicode(Type);
	Log_.Msg = Msg;

	LogQueue.push(Log_);
	++Semaphore;
	cv.notify_one();
}

void Log::AddLog(const LogType LogType, const MsgType MsgType, const wchar_t* Type, const char* Msg)
{
	Log Log_;
	Log_.LogType = LogType;
	Log_.MsgType = MsgType;
	Log_.Type = Type;
	Log_.Msg = Iconv::Ansi2Unicode(Msg);

	LogQueue.push(Log_);
	++Semaphore;
	cv.notify_one();
}

void Log::AddLog(const LogType LogType, const MsgType MsgType, const wchar_t* Type, const wchar_t* Msg)
{
	Log Log_;
	Log_.LogType = LogType;
	Log_.MsgType = MsgType;
	Log_.Type = Type;
	Log_.Msg = Msg;

	LogQueue.push(Log_);
	++Semaphore;
	cv.notify_one();
}

void Log::AddLog(const LogType LogType, const MsgType MsgType, const Event::NoticeEvent::NoticeEvent* NoticeEvent)
{
	Log Log_;
	Log_.LogType = LogType;
	Log_.MsgType = MsgType;

	std::wstringstream MsgSteam;
	switch (NoticeEvent->NoticeEventType)
	{
	case Event::NoticeEvent::NoticeEventType::group_fileupload:
		Log_.Type = L"group_fileupload";
		break;
	case Event::NoticeEvent::NoticeEventType::group_adminchange:
		Log_.Type = L"group_adminchange";
		MsgSteam << ((Event::NoticeEvent::group_adminchange*)NoticeEvent->Information)->FromGroup << " ";
		MsgSteam << ((Event::NoticeEvent::group_adminchange*)NoticeEvent->Information)->FromQQ << " ";
		MsgSteam << (((Event::NoticeEvent::group_adminchange*)NoticeEvent->Information)->Type ? "Set" : "UnSet");
		break;
	case Event::NoticeEvent::NoticeEventType::group_memberchange:
		Log_.Type = L"group_memberchange";
		MsgSteam << ((Event::NoticeEvent::group_memberchange*)NoticeEvent->Information)->FromGroup << " ";
		MsgSteam << ((Event::NoticeEvent::group_memberchange*)NoticeEvent->Information)->FromQQ << " ";
		MsgSteam << ((Event::NoticeEvent::group_memberchange*)NoticeEvent->Information)->OperateQQ << " ";
		MsgSteam << ((Event::NoticeEvent::group_memberchange*)NoticeEvent->Information)->Type;
		break;
	case Event::NoticeEvent::NoticeEventType::group_mute:
		Log_.Type = L"group_mute";
		break;
	case Event::NoticeEvent::NoticeEventType::friend_added:
		Log_.Type = L"friend_added";
		break;
	default:
		break;
	}
	std::wstring wstr = MsgSteam.str();
	Log_.Msg = new wchar_t[wstr.size() + 1];
	memcpy((wchar_t*)Log_.Msg, wstr.c_str(), wstr.size() * sizeof(wchar_t));
	((wchar_t*)Log_.Msg)[wstr.size()] = L'\0';

	LogQueue.push(Log_);
	++Semaphore;
	cv.notify_one();
}

void Log::AddLog(const LogType LogType, const MsgType MsgType, const Event::RequestEvent::RequestEvent* RequestEvent)
{
	Log Log_;
	Log_.LogType = LogType;
	Log_.MsgType = MsgType;

	std::wstringstream MsgSteam;
	switch (RequestEvent->RequestEventType)
	{
	case Event::RequestEvent::RequestEventType::add_friend:
		Log_.Type = L"add_friend";
		MsgSteam << ((Event::RequestEvent::add_friend*)RequestEvent->Information)->FromQQ << " ";
		MsgSteam << Iconv::Utf82Unicode((char*)((Event::RequestEvent::add_friend*)RequestEvent->Information)->msg) << " ";
		break;
	case Event::RequestEvent::RequestEventType::add_group:
		Log_.Type = L"add_group";
		MsgSteam << ((Event::RequestEvent::add_group*)RequestEvent->Information)->FromGroup << " ";
		MsgSteam << ((Event::RequestEvent::add_group*)RequestEvent->Information)->FromQQ << " ";
		MsgSteam << ((Event::RequestEvent::add_group*)RequestEvent->Information)->Type << " ";
		//MsgSteam << ((Event::RequestEvent::add_group*)RequestEvent->Information)->msg << " ";
		break;
	default:
		break;
	}

	std::wstring wstr = MsgSteam.str();
	Log_.Msg = new wchar_t[wstr.size() + 1];
	memcpy((wchar_t*)Log_.Msg, wstr.c_str(), wstr.size() * sizeof(wchar_t));
	((wchar_t*)Log_.Msg)[wstr.size()] = L'\0';

	LogQueue.push(Log_);
	++Semaphore;
	cv.notify_one();

}
