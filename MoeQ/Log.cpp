#include "pch.h"
#include "Log.h"

HANDLE hwnd;
std::atomic_int Semaphore = 0;
std::condition_variable cv;
std::queue<Log::Log> LogQueue;

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
			Database::AddLog(Log_->LogType, Log_->MsgType, Log_->Type, Log_->Msg);
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

void Log::AddLog(const LogType LogType, const MsgType MsgType, const wchar_t* Type, const Message::Msg* Msg)
{
	std::wstringstream MsgSteam;
	do
	{
		switch (Msg->MsgType)
		{
		case Message::MsgType::text:
			if (((Message::text*)Msg->Message)->text != nullptr) MsgSteam << Iconv::Utf82Unicode(((Message::text*)Msg->Message)->text);//Todo ÄÚ´æÐ¹Â¶
			else
			{
				MsgSteam << "[MQ:at,qq=";
				MsgSteam << ((Message::text*)Msg->Message)->AtQQ;
				MsgSteam << "]";
			}
			break;
		case Message::MsgType::classcal_face:
			MsgSteam << "[MQ:cface,id=";
			MsgSteam << ((Message::classcal_face*)Msg->Message)->id;
			MsgSteam << "]";
			break;
		case Message::MsgType::expression:
			MsgSteam << "[MQ:expression,id=";
			MsgSteam << ((Message::expression*)Msg->Message)->id;
			MsgSteam << ",MD5=";
			MsgSteam << XBin::Bin2Hex(((Message::expression*)Msg->Message)->MD5, 16);
			MsgSteam << "]";
			break;
		case Message::MsgType::picture:
			MsgSteam << "[MQ:picture,MD5=";
			MsgSteam << XBin::Bin2Hex(((Message::picture*)Msg->Message)->MD5, 16);
			MsgSteam << ",Width=";
			MsgSteam << ((Message::picture*)Msg->Message)->Width;
			MsgSteam << ",Height=";
			MsgSteam << ((Message::picture*)Msg->Message)->Height;
			MsgSteam << ",Length=";
			MsgSteam << ((Message::picture*)Msg->Message)->Length;
			MsgSteam << "]";
			break;
		case Message::MsgType::xml:
			MsgSteam << "[MQ:xml,text=";
			MsgSteam << ((Message::xml*)Msg->Message)->text;
			MsgSteam << "]";
			break;
		case Message::MsgType::reply:
			MsgSteam << "[MQ:reply,MsgId=";
			MsgSteam << ((Message::reply*)Msg->Message)->MsgId;
			MsgSteam << ",QQ=";
			MsgSteam << ((Message::reply*)Msg->Message)->QQ;
			MsgSteam << ",Time=";
			MsgSteam << ((Message::reply*)Msg->Message)->Time;
			MsgSteam << ",Msg=";
			{
				const Message::Msg* ReplyMsg = ((Message::reply*)Msg->Message)->Msg;
				do
				{
					switch (ReplyMsg->MsgType)
					{
					case Message::MsgType::text:
						MsgSteam << Iconv::Utf82Unicode(((Message::text*)ReplyMsg->Message)->text);//Todo ÄÚ´æÐ¹Â¶
						break;
					case Message::MsgType::classcal_face:
						MsgSteam << "[MQ:cface,id=";
						MsgSteam << ((Message::classcal_face*)ReplyMsg->Message)->id;
						MsgSteam << "]";
						break;
					}
					ReplyMsg->NextPoint;
				} while ((ReplyMsg = ReplyMsg->NextPoint) != nullptr);
			}
			MsgSteam << "]";
			break;
		case Message::MsgType::json:
			MsgSteam << "[MQ:json,text=";
			MsgSteam << Iconv::Utf82Unicode(((Message::json*)Msg->Message)->text);
			MsgSteam << "]";
			break;
		default:
			break;
		}
	} while ((Msg = Msg->NextPoint) != nullptr);

	Log Log_;
	Log_.LogType = LogType;
	Log_.MsgType = MsgType;
	Log_.Type = Type;
	std::wstring wstr = MsgSteam.str();
	Log_.Msg = new wchar_t[wstr.size()+1];
	memcpy((wchar_t*)Log_.Msg, wstr.c_str(), wstr.size() * sizeof(wchar_t));
	((wchar_t*)Log_.Msg)[wstr.size()] = L'\0';

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
		MsgSteam << ((Event::RequestEvent::add_friend*)RequestEvent->Information)->msg << " ";
		break;
	case Event::RequestEvent::RequestEventType::add_group:
		Log_.Type = L"add_group";
		MsgSteam << ((Event::RequestEvent::add_group*)RequestEvent->Information)->FromGroup << " ";
		MsgSteam << ((Event::RequestEvent::add_group*)RequestEvent->Information)->FromQQ << " ";
		MsgSteam << ((Event::RequestEvent::add_group*)RequestEvent->Information)->Type;
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
