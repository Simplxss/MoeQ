#include "pch.h"
#include "Log.h"

HANDLE hwnd;

void Log::Init(HANDLE Handle)
{
	hwnd = Handle;
}

void Log::AddLog(const LogType LogType, const MsgType MsgType, const wchar_t* Type, const wchar_t* Msg)
{
	CListCtrl* LogList = (CListCtrl*)((CDialog*)hwnd)->GetDlgItem(IDC_LOG);
	int Index = LogList->InsertItem(0, L"");
	if (Index < 0)	return;
	switch (LogType) {
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
	switch (MsgType)
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
	LogList->SetItemText(Index, 2, Type);
	LogList->SetItemText(Index, 3, Msg);
}

void Log::AddLog(const LogType LogType, const MsgType MsgType, const wchar_t* Type, const Message::Msg* Msg)
{
	CListCtrl* LogList = (CListCtrl*)((CDialog*)hwnd)->GetDlgItem(IDC_LOG);
	int Index = LogList->InsertItem(0, L"");
	if (Index < 0)	return;
	switch (LogType) {
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
	switch (MsgType)
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
	LogList->SetItemText(Index, 2, Type);
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
	}while ((Msg = Msg->NextPoint) != nullptr);
	LogList->SetItemText(Index, 3, MsgSteam.str().c_str());
}

void Log::AddLog(const LogType LogType, const MsgType MsgType, const Event::NoticeEvent::NoticeEvent* NoticeEvent)
{
	CListCtrl* LogList = (CListCtrl*)((CDialog*)hwnd)->GetDlgItem(IDC_LOG);
	int Index = LogList->InsertItem(0, L"");
	if (Index < 0)	return;
	switch (LogType) {
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
	switch (MsgType)
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
	std::wstringstream MsgSteam;
	switch (NoticeEvent->NoticeEventType)
	{
	case Event::NoticeEvent::NoticeEventType::group_fileupload:
		LogList->SetItemText(Index, 0, L"group_fileupload");
		break;
	case Event::NoticeEvent::NoticeEventType::group_adminchange:
		LogList->SetItemText(Index, 0, L"group_adminchange");
		MsgSteam << ((Event::NoticeEvent::group_adminchange*)NoticeEvent->Information)->FromGroup << " ";
		MsgSteam << ((Event::NoticeEvent::group_adminchange*)NoticeEvent->Information)->FromQQ << " ";
		MsgSteam << (((Event::NoticeEvent::group_adminchange*)NoticeEvent->Information)->Type ? "Set":"UnSet");
		break;
	case Event::NoticeEvent::NoticeEventType::group_memberchange:
		LogList->SetItemText(Index, 0, L"group_memberchange");
		MsgSteam << ((Event::NoticeEvent::group_memberchange*)NoticeEvent->Information)->FromGroup << " ";
		MsgSteam << ((Event::NoticeEvent::group_memberchange*)NoticeEvent->Information)->FromQQ << " ";
		MsgSteam << ((Event::NoticeEvent::group_memberchange*)NoticeEvent->Information)->OperateQQ << " ";
		MsgSteam << ((Event::NoticeEvent::group_memberchange*)NoticeEvent->Information)->Type;
		break;
	case Event::NoticeEvent::NoticeEventType::group_mute:
		LogList->SetItemText(Index, 0, L"group_mute");
		break;
	case Event::NoticeEvent::NoticeEventType::friend_added:
		LogList->SetItemText(Index, 0, L"friend_added");
		break;
	default:
		break;
	}
	LogList->SetItemText(Index, 3, MsgSteam.str().c_str());
}

void Log::AddLog(const LogType LogType, const MsgType MsgType, const Event::RequestEvent::RequestEvent* RequestEvent)
{
	CListCtrl* LogList = (CListCtrl*)((CDialog*)hwnd)->GetDlgItem(IDC_LOG);
	int Index = LogList->InsertItem(0, L"");
	if (Index < 0)	return;
	switch (LogType) {
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
	switch (MsgType)
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
	std::wstringstream MsgSteam;
	switch (RequestEvent->RequestEventType)
	{
	case Event::RequestEvent::RequestEventType::add_friend:
		LogList->SetItemText(Index, 0, L"add_friend");
		MsgSteam << ((Event::RequestEvent::add_friend*)RequestEvent->Information)->FromQQ << " ";
		MsgSteam << ((Event::RequestEvent::add_friend*)RequestEvent->Information)->msg << " ";
		break;
	case Event::RequestEvent::RequestEventType::add_group:
		LogList->SetItemText(Index, 0, L"add_group");
		MsgSteam << ((Event::RequestEvent::add_group*)RequestEvent->Information)->FromGroup << " ";
		MsgSteam << ((Event::RequestEvent::add_group*)RequestEvent->Information)->FromQQ << " ";
		MsgSteam << ((Event::RequestEvent::add_group*)RequestEvent->Information)->Type;
		//MsgSteam << ((Event::RequestEvent::add_group*)RequestEvent->Information)->msg << " ";
		break;
	default:
		break;
	}
	LogList->SetItemText(Index, 3, MsgSteam.str().c_str());
}
