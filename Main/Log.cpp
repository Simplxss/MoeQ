#include "Log.h"

std::atomic_int Semaphore = 0;
std::condition_variable cv;
std::queue<Log::Log> LogQueue;

std::u8string Message::ParseMsg(Message::Msg *Msg)
{
    std::u8string MsgSteam;
    do
    {
        switch (Msg->MsgType)
        {
        case Message::MsgType::text:
            if (((Message::text *)Msg->Message)->text != nullptr)
                MsgSteam += ((Message::text *)Msg->Message)->text;
            else
            {
                MsgSteam += u8"[MQ:at,qq=";
                MsgSteam += (char8_t *)std::to_string(((Message::text *)Msg->Message)->AtQQ).c_str();
                MsgSteam += u8"]";
            }
            break;
        case Message::MsgType::classcal_face:
            MsgSteam += u8"[MQ:cface,id=";
            MsgSteam += (char8_t *)std::to_string(((Message::classcal_face *)Msg->Message)->id).c_str();
            MsgSteam += u8"]";
            break;
        case Message::MsgType::expression:
            MsgSteam += u8"[MQ:expression,id=";
            MsgSteam += (char8_t *)std::to_string(((Message::expression *)Msg->Message)->id).c_str();
            MsgSteam += u8",MD5=";
            MsgSteam += (char8_t *)XBin::Bin2HexEx(((Message::expression *)Msg->Message)->MD5, 16);
            MsgSteam += u8"]";
            break;
        case Message::MsgType::picture:
            MsgSteam += u8"[MQ:picture,MD5=";
            MsgSteam += (char8_t *)XBin::Bin2HexEx(((Message::picture *)Msg->Message)->MD5, 16);
            MsgSteam += u8",Width=";
            MsgSteam += (char8_t *)std::to_string(((Message::picture *)Msg->Message)->Width).c_str();
            MsgSteam += u8",Height=";
            MsgSteam += (char8_t *)std::to_string(((Message::picture *)Msg->Message)->Height).c_str();
            MsgSteam += u8",Length=";
            MsgSteam += (char8_t *)std::to_string(((Message::picture *)Msg->Message)->Data.Length).c_str();
            MsgSteam += u8"]";
            break;
        case Message::MsgType::xml:
            MsgSteam += u8"[MQ:xml,text=";
            MsgSteam += ((Message::xml *)Msg->Message)->text;
            MsgSteam += u8"]";
            break;
        case Message::MsgType::reply:
            MsgSteam += u8"[MQ:reply,MsgId=";
            MsgSteam += (char8_t *)std::to_string(((Message::reply *)Msg->Message)->MsgId).c_str();
            MsgSteam += u8",QQ=";
            MsgSteam += (char8_t *)std::to_string(((Message::reply *)Msg->Message)->QQ).c_str();
            MsgSteam += u8",Time=";
            MsgSteam += (char8_t *)std::to_string(((Message::reply *)Msg->Message)->Time).c_str();
            MsgSteam += u8",Msg=";
            {
                const Message::Msg *ReplyMsg = ((Message::reply *)Msg->Message)->Msg;
                do
                {
                    switch (ReplyMsg->MsgType)
                    {
                    case Message::MsgType::text:
                        MsgSteam += ((Message::text *)ReplyMsg->Message)->text;
                        break;
                    case Message::MsgType::classcal_face:
                        MsgSteam += u8"[MQ:cface,id=";
                        MsgSteam += (char8_t *)std::to_string(((Message::classcal_face *)ReplyMsg->Message)->id).c_str();
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
            MsgSteam += ((Message::json *)Msg->Message)->text;
            MsgSteam += u8"]";
            break;
        default:
            break;
        }
    } while ((Msg = Msg->NextPoint) != nullptr);
    return MsgSteam;
}

void Message::DestoryMsg(Message::Msg *Msg)
{
    while (Msg != nullptr)
    {
        switch (Msg->MsgType)
        {
        case Message::MsgType::text:
            if (((Message::text *)Msg->Message)->text != nullptr)
                delete[]((Message::text *)Msg->Message)->text;
            delete (Message::text *)Msg->Message;
            break;
        case Message::MsgType::classcal_face:
            delete (Message::classcal_face *)Msg->Message;
            break;
        case Message::MsgType::expression:
            delete[]((Message::expression *)Msg->Message)->MD5;
            delete (Message::expression *)Msg->Message;
            break;
        case Message::MsgType::picture:
            delete[]((Message::picture *)Msg->Message)->MD5;
            delete[]((Message::picture *)Msg->Message)->Data.URL;
            delete (Message::picture *)Msg->Message;
            break;
        case Message::MsgType::xml:
            delete[]((Message::xml *)Msg->Message)->text;
            delete (Message::xml *)Msg->Message;
            break;
        case Message::MsgType::reply:
        {
            Message::Msg *ReplyMsg = ((Message::reply *)Msg->Message)->Msg;
            while (ReplyMsg != nullptr)
            {
                switch (ReplyMsg->MsgType)
                {
                case Message::MsgType::text:
                    delete[]((Message::text *)ReplyMsg->Message)->text;
                    delete (Message::text *)ReplyMsg->Message;
                    break;
                case Message::MsgType::classcal_face:
                    delete (Message::classcal_face *)ReplyMsg->Message;
                    break;
                }
                Message::Msg *tmp = ReplyMsg->NextPoint;
                delete ReplyMsg;
                ReplyMsg = tmp;
            }
        }
            delete (Message::reply *)Msg->Message;
            break;
        case Message::MsgType::json:
            delete[]((Message::json *)Msg->Message)->text;
            delete (Message::json *)Msg->Message;
            break;
        default:
            break;
        }
        Message::Msg *tmp = Msg->NextPoint;
        delete Msg;
        Msg = tmp;
    };
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
            switch (Log_.LogType)
            {
            case LogType::__DEBUG:
                std::cout << "Debug";
                break;
            case LogType::INFORMATION:
                std::cout << "Information";
                break;
            case LogType::NOTICE:
                std::cout << "Notice";
                break;
            case LogType::WARNING:
                std::cout << "Warning";
                break;
            case LogType::_ERROR:
                std::cout << "Error";
                break;
            }
            std::cout << " ";
            switch (Log_.MsgType)
            {
            case MsgType::OTHER:
                std::cout << "Other";
                break;
            case MsgType::PLUGIN:
                std::cout << "Plugin";
                break;
            case MsgType::_GROUP:
                std::cout << "Group";
                break;
            case MsgType::PRIVATE:
                std::cout << "Private";
                break;
            case MsgType::PROGRAM:
                std::cout << "Program";
                break;
            case MsgType::SERVER:
                std::cout << "Server";
                break;
            default:
                throw "Known MsgType";
                break;
            }
            std::cout << " " << (char *)Log_.Type.c_str() << " " << (char *)Log_.Msg.c_str() << std::endl;

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

void Log::AddLog(const LogType LogType, const MsgType MsgType, const char *Type, const char *Msg)
{
    LogQueue.push(Log({LogType, MsgType, Iconv::AnsiToUtf8(Type), Iconv::AnsiToUtf8(Msg)}));
    ++Semaphore;
    cv.notify_one();
}

void Log::AddLog(const LogType LogType, const MsgType MsgType, const char *Type, const char8_t *Msg)
{
    LogQueue.push(Log({LogType, MsgType, Iconv::AnsiToUtf8(Type), Msg}));
    ++Semaphore;
    cv.notify_one();
}

void Log::AddLog(const LogType LogType, const MsgType MsgType, const char8_t *Type, const char *Msg)
{
    LogQueue.push(Log({LogType, MsgType, Type, Iconv::AnsiToUtf8(Msg)}));
    ++Semaphore;
    cv.notify_one();
}

void Log::AddLog(const LogType LogType, const MsgType MsgType, const wchar_t *Type, const wchar_t *Msg)
{
    LogQueue.push(Log({LogType, MsgType, Iconv::UnicodeToUtf8(Type), Iconv::UnicodeToUtf8(Msg)}));
    ++Semaphore;
    cv.notify_one();
}

#endif

void Log::AddLog(const LogType LogType, const MsgType MsgType, const char8_t *Type, const char8_t *MsgFormat, const bool Format, ...)
{
    if (Format)
    {
        char8_t Msg[999];
        va_list args;
        va_start(args, Format);
        vsprintf((char *)Msg, (char *)MsgFormat, args);
        va_end(args);
        LogQueue.push(Log({LogType, MsgType, Type, Msg}));
    }
    else
        LogQueue.push(Log({LogType, MsgType, Type, MsgFormat}));

    ++Semaphore;
    cv.notify_one();
}

void Log::AddLog(const LogType LogType, const MsgType MsgType, const Event::NoticeEvent::NoticeEvent *NoticeEvent)
{
    std::u8string MsgSteam;
    switch (NoticeEvent->NoticeEventType)
    {
    case Event::NoticeEvent::NoticeEventType::group_fileupload:
        LogQueue.push(Log({
            LogType,
            MsgType,
            u8"group_fileupload",
        }));
        break;
    case Event::NoticeEvent::NoticeEventType::group_adminchange:
        MsgSteam += (char8_t *)std::to_string(((Event::NoticeEvent::group_adminchange *)NoticeEvent->Information)->FromGroup).c_str();
        MsgSteam += u8" ";
        MsgSteam += (char8_t *)std::to_string(((Event::NoticeEvent::group_adminchange *)NoticeEvent->Information)->FromQQ).c_str();
        MsgSteam += u8" ";
        MsgSteam += (((Event::NoticeEvent::group_adminchange *)NoticeEvent->Information)->Type ? u8"Set" : u8"UnSet");
        LogQueue.push(Log({LogType, MsgType, u8"group_adminchange", MsgSteam}));
        break;
    case Event::NoticeEvent::NoticeEventType::group_memberchange:
        MsgSteam += (char8_t *)std::to_string(((Event::NoticeEvent::group_memberchange *)NoticeEvent->Information)->FromGroup).c_str();
        MsgSteam += u8" ";
        MsgSteam += (char8_t *)std::to_string(((Event::NoticeEvent::group_memberchange *)NoticeEvent->Information)->FromQQ).c_str();
        switch (((Event::NoticeEvent::group_memberchange *)NoticeEvent->Information)->Type)
        {
        case 0:
            MsgSteam += u8" Increase";
            break;
        case 1:
            MsgSteam += u8" ";
            MsgSteam += (char8_t *)std::to_string(((Event::NoticeEvent::group_memberchange *)NoticeEvent->Information)->OperateQQ).c_str();
            MsgSteam += u8" Increase";
            break;
        case 2:
            MsgSteam += u8" Decrease";
            break;
        case 3:
            MsgSteam += u8" ";
            MsgSteam += (char8_t *)std::to_string(((Event::NoticeEvent::group_memberchange *)NoticeEvent->Information)->OperateQQ).c_str();
            MsgSteam += u8" Decrease";
            break;
        case 4:
            MsgSteam += u8" Disband";
            break;
        default:
            break;
        }
        LogQueue.push(Log({LogType, MsgType, u8"group_memberchange", MsgSteam}));
        break;
    case Event::NoticeEvent::NoticeEventType::group_mute:
        LogQueue.push(Log({
            LogType,
            MsgType,
            u8"group_mute",
        }));
        break;
    case Event::NoticeEvent::NoticeEventType::friend_added:
        LogQueue.push(Log({
            LogType,
            MsgType,
            u8"friend_added",
        }));
        break;
    }
    ++Semaphore;
    cv.notify_one();
}

void Log::AddLog(const LogType LogType, const MsgType MsgType, const Event::RequestEvent::RequestEvent *RequestEvent)
{
    std::u8string MsgSteam;
    switch (RequestEvent->RequestEventType)
    {
    case Event::RequestEvent::RequestEventType::add_friend:
        MsgSteam += (char8_t *)std::to_string(((Event::RequestEvent::add_friend *)RequestEvent->Information)->FromQQ).c_str();
        MsgSteam += u8" ";
        MsgSteam += ((Event::RequestEvent::add_friend *)RequestEvent->Information)->msg;
        LogQueue.push(Log({LogType, MsgType, u8"add_friend", MsgSteam}));
        break;
    case Event::RequestEvent::RequestEventType::other_join_group:
        MsgSteam += (char8_t *)std::to_string(((Event::RequestEvent::other_join_group *)RequestEvent->Information)->FromGroup).c_str();
        MsgSteam += u8" ";
        MsgSteam += (char8_t *)std::to_string(((Event::RequestEvent::other_join_group *)RequestEvent->Information)->FromQQ).c_str();
        MsgSteam += u8" ";
        MsgSteam += ((Event::RequestEvent::other_join_group *)RequestEvent->Information)->FromGroupName;
        MsgSteam += u8" ";
        MsgSteam += ((Event::RequestEvent::other_join_group *)RequestEvent->Information)->FromQQName;
        if (((Event::RequestEvent::other_join_group *)RequestEvent->Information)->InvitorQQ != 0)
        {
            MsgSteam += u8" ";
            MsgSteam += (char8_t *)std::to_string(((Event::RequestEvent::other_join_group *)RequestEvent->Information)->InvitorQQ).c_str();
            MsgSteam += u8" ";
            MsgSteam += ((Event::RequestEvent::other_join_group *)RequestEvent->Information)->InvitorQQName;
        }
        MsgSteam += u8" ";
        MsgSteam += ((Event::RequestEvent::other_join_group *)RequestEvent->Information)->msg;
        LogQueue.push(Log({LogType, MsgType, u8"add_group", MsgSteam}));
        break;
    case Event::RequestEvent::RequestEventType::self_invited:

        MsgSteam += (char8_t *)std::to_string(((Event::RequestEvent::self_invited *)RequestEvent->Information)->FromGroup).c_str();
        MsgSteam += u8" ";
        MsgSteam += ((Event::RequestEvent::self_invited *)RequestEvent->Information)->FromGroupName;
        MsgSteam += u8" ";
        MsgSteam += (char8_t *)std::to_string(((Event::RequestEvent::self_invited *)RequestEvent->Information)->InvitorQQ).c_str();
        MsgSteam += u8" ";
        MsgSteam += ((Event::RequestEvent::self_invited *)RequestEvent->Information)->InvitorQQName;
        break;
    }
    ++Semaphore;
    cv.notify_one();
}
