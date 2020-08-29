#include "pch.h"
#include "Event.h"
#include "PluginSystem.h"

extern PluginSystem Plugin;

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
	Plugin.BroadcastMessageEvent(&Target, GroupMsg->Msg, 0);//Todo
}

void Event::OnPrivateMsg(const PrivateMsg* PrivateMsg)
{
	Target::Target Target{ Target::TargetType::_private,(void*)new Target::_private{PrivateMsg->FromQQ,0 } };//Todo
	Plugin.BroadcastMessageEvent(&Target, PrivateMsg->Msg, 0);//Todo

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