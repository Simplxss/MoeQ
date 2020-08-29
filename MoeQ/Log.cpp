#include "pch.h"
#include "Log.h"

void Log::AddLog(const LogType LogType, const MsgType MsgType, const wchar_t* Type, const wchar_t* Msg)
{
	switch (LogType) {
	case LogType::__DEBUG:
		std::wcout << "DEBUG ";
		break;
	case LogType::INFORMATION:
		std::wcout << "INFORMATION ";
		break;
	case LogType::NOTICE:
		std::wcout << "NOTICE ";
		break;
	case LogType::WARNING:
		std::wcout << "WARNING ";
		break;
	case LogType::_ERROR:
		std::wcout << "ERROR ";
		break;
	default:
		throw "Known LogType";
		break;
	}
	switch (MsgType)
	{
	case MsgType::OTHER:
		std::wcout << "OTHER ";
		break;
	case MsgType::_GROUP:
		std::wcout << "GROUP ";
		break;
	case MsgType::PRIVATE:
		std::wcout << "PRIVATE ";
		break;
	case MsgType::PROGRAM:
		std::wcout << "PROGRAM ";
		break;
	case MsgType::SERVER:
		std::wcout << "SERVER ";
		break;
	default:
		throw "Known MsgType";
		break;
	}
	std::wcout << Type << " ";
	std::wcout << Msg << std::endl;
}

void Log::AddLog(const LogType LogType, const MsgType MsgType, const wchar_t* Type, const Message::Msg* Msg)
{
	switch (LogType) {
	case LogType::__DEBUG:
		std::wcout << "DEBUG ";
		break;
	case LogType::INFORMATION:
		std::wcout << "INFORMATION ";
		break;
	case LogType::NOTICE:
		std::wcout << "NOTICE ";
		break;
	case LogType::WARNING:
		std::wcout << "WARNING ";
		break;
	case LogType::_ERROR:
		std::wcout << "ERROR ";
		break;
	default:
		throw "Known LogType";
		break;
	}
	switch (MsgType)
	{
	case MsgType::OTHER:
		std::wcout << "OTHER ";
		break;
	case MsgType::_GROUP:
		std::wcout << "GROUP ";
		break;
	case MsgType::PRIVATE:
		std::wcout << "PRIVATE ";
		break;
	case MsgType::PROGRAM:
		std::wcout << "PROGRAM ";
		break;
	case MsgType::SERVER:
		std::wcout << "SERVER ";
		break;
	default:
		throw "Known MsgType";
		break;
	}
	std::wcout << Type << " ";
	do
	{
		switch (Msg->MsgType)
		{
		case Message::MsgType::text:
			if (((Message::text*)Msg->Message)->text != nullptr) std::wcout << Iconv::Utf82Unicode(((Message::text*)Msg->Message)->text);//Todo ÄÚ´æÐ¹Â¶
			else
			{
				std::wcout << "[MQ:at,qq=";
				std::wcout << ((Message::text*)Msg->Message)->AtQQ;
				std::wcout << "]";
			}
			break;
		case Message::MsgType::classcal_face:
			std::wcout << "[MQ:cface,id=";
			std::wcout << ((Message::classcal_face*)Msg->Message)->id;
			std::wcout << "]";
			break;
		case Message::MsgType::expression:
			std::wcout << "[MQ:expression,id=";
			std::wcout << ((Message::expression*)Msg->Message)->id;
			std::wcout << ",MD5=";
			std::wcout << XBin::Bin2Hex(((Message::expression*)Msg->Message)->MD5, 16);
			std::wcout << "]";
			break;
		case Message::MsgType::picture:
			std::wcout << "[MQ:picture,MD5=";
			std::wcout << XBin::Bin2Hex(((Message::picture*)Msg->Message)->MD5, 16);
			std::wcout << ",Width=";
			std::wcout << ((Message::picture*)Msg->Message)->Width;
			std::wcout << ",Height=";
			std::wcout << ((Message::picture*)Msg->Message)->Height;
			std::wcout << ",Length=";
			std::wcout << ((Message::picture*)Msg->Message)->Length;
			std::wcout << "]";
			break;
		case Message::MsgType::xml:
			std::wcout << "[MQ:xml,text=";
			std::wcout << ((Message::xml*)Msg->Message)->text;
			std::wcout << "]";
			break;
		case Message::MsgType::reply:
			std::wcout << "[MQ:reply,MsgId=";
			std::wcout << ((Message::reply*)Msg->Message)->MsgId;
			std::wcout << ",QQ=";
			std::wcout << ((Message::reply*)Msg->Message)->QQ;
			std::wcout << ",Time=";
			std::wcout << ((Message::reply*)Msg->Message)->Time;
			std::wcout << ",Msg=";
			{
				const Message::Msg* ReplyMsg = ((Message::reply*)Msg->Message)->Msg;
				do
				{
					switch (ReplyMsg->MsgType)
					{
					case Message::MsgType::text:
						std::wcout << Iconv::Utf82Unicode(((Message::text*)ReplyMsg->Message)->text);//Todo ÄÚ´æÐ¹Â¶
						break;
					case Message::MsgType::classcal_face:
						std::wcout << "[MQ:cface,id=";
						std::wcout << ((Message::classcal_face*)ReplyMsg->Message)->id;
						std::wcout << "]";
						break;
					}
					ReplyMsg->NextPoint;
				} while ((ReplyMsg = ReplyMsg->NextPoint) != nullptr);
			}
			std::wcout << "]";
			break;
		case Message::MsgType::json:
			std::wcout << "[MQ:json,text=";
			std::wcout << Iconv::Utf82Unicode(((Message::json*)Msg->Message)->text);
			std::wcout << "]";
			break;
		default:
			break;
		}
	}while ((Msg = Msg->NextPoint) != nullptr);
	std::wcout << std::endl;
}

void Log::AddLog(const LogType LogType, const MsgType MsgType, const Event::NoticeEvent::NoticeEvent* NoticeEvent)
{
	switch (LogType) {
	case LogType::__DEBUG:
		std::wcout << "DEBUG ";
		break;
	case LogType::INFORMATION:
		std::wcout << "INFORMATION ";
		break;
	case LogType::NOTICE:
		std::wcout << "NOTICE ";
		break;
	case LogType::WARNING:
		std::wcout << "WARNING ";
		break;
	case LogType::_ERROR:
		std::wcout << "ERROR ";
		break;
	default:
		throw "Known LogType";
		break;
	}
	switch (MsgType)
	{
	case MsgType::OTHER:
		std::wcout << "OTHER ";
		break;
	case MsgType::_GROUP:
		std::wcout << "GROUP ";
		break;
	case MsgType::PRIVATE:
		std::wcout << "PRIVATE ";
		break;
	case MsgType::PROGRAM:
		std::wcout << "PROGRAM ";
		break;
	case MsgType::SERVER:
		std::wcout << "SERVER ";
		break;
	default:
		throw "Known MsgType";
		break;
	}
	switch (NoticeEvent->NoticeEventType)
	{
	case Event::NoticeEvent::NoticeEventType::group_fileupload:
		std::wcout << "group_fileupload";
		break;
	case Event::NoticeEvent::NoticeEventType::group_adminchange:
		std::wcout << "group_adminchange";
		std::wcout << ((Event::NoticeEvent::group_adminchange*)NoticeEvent->Information)->FromGroup << " ";
		std::wcout << ((Event::NoticeEvent::group_adminchange*)NoticeEvent->Information)->FromQQ << " ";
		std::wcout << (((Event::NoticeEvent::group_adminchange*)NoticeEvent->Information)->Type ? "Set":"UnSet");
		break;
	case Event::NoticeEvent::NoticeEventType::group_memberchange:
		std::wcout << "group_memberchange";
		std::wcout << ((Event::NoticeEvent::group_memberchange*)NoticeEvent->Information)->FromGroup << " ";
		std::wcout << ((Event::NoticeEvent::group_memberchange*)NoticeEvent->Information)->FromQQ << " ";
		std::wcout << ((Event::NoticeEvent::group_memberchange*)NoticeEvent->Information)->OperateQQ << " ";
		std::wcout << ((Event::NoticeEvent::group_memberchange*)NoticeEvent->Information)->Type;
		break;
	case Event::NoticeEvent::NoticeEventType::group_mute:
		std::wcout << "group_mute";
		break;
	case Event::NoticeEvent::NoticeEventType::friend_added:
		std::wcout << "friend_added";
		break;
	default:
		break;
	}
	std::wcout << std::endl;
}

void Log::AddLog(const LogType LogType, const MsgType MsgType, const Event::RequestEvent::RequestEvent* RequestEvent)
{
	switch (LogType) {
	case LogType::__DEBUG:
		std::wcout << "DEBUG ";
		break;
	case LogType::INFORMATION:
		std::wcout << "INFORMATION ";
		break;
	case LogType::NOTICE:
		std::wcout << "NOTICE ";
		break;
	case LogType::WARNING:
		std::wcout << "WARNING ";
		break;
	case LogType::_ERROR:
		std::wcout << "ERROR ";
		break;
	default:
		throw "Known LogType";
		break;
	}
	switch (MsgType)
	{
	case MsgType::OTHER:
		std::wcout << "OTHER ";
		break;
	case MsgType::_GROUP:
		std::wcout << "GROUP ";
		break;
	case MsgType::PRIVATE:
		std::wcout << "PRIVATE ";
		break;
	case MsgType::PROGRAM:
		std::wcout << "PROGRAM ";
		break;
	case MsgType::SERVER:
		std::wcout << "SERVER ";
		break;
	default:
		throw "Known MsgType";
		break;
	}
	switch (RequestEvent->RequestEventType)
	{
	case Event::RequestEvent::RequestEventType::add_friend:
		std::wcout << "add_friend";
		std::wcout << ((Event::RequestEvent::add_friend*)RequestEvent->Information)->FromQQ << " ";
		std::wcout << ((Event::RequestEvent::add_friend*)RequestEvent->Information)->msg << " ";
		break;
	case Event::RequestEvent::RequestEventType::add_group:
		std::wcout << "add_group";
		std::wcout << ((Event::RequestEvent::add_group*)RequestEvent->Information)->FromGroup << " ";
		std::wcout << ((Event::RequestEvent::add_group*)RequestEvent->Information)->FromQQ << " ";
		std::wcout << ((Event::RequestEvent::add_group*)RequestEvent->Information)->Type;
		//std::wcout << ((Event::RequestEvent::add_group*)RequestEvent->Information)->msg << " ";
		break;
	default:
		break;
	}
	std::wcout << std::endl;
}
