#include "PluginSystem.h"

extern bool DevMode;

#if defined(_WIN_PLATFORM_)
extern wchar_t DataPath[MAX_PATH + 1];
#endif

#if defined(_LINUX_PLATFORM_)
extern char DataPath[PATH_MAX + 1];
#endif

extern PluginSystem Plugin;

void Event::OnGroupMsg(const GroupMsg *GroupMsg)
{
    Target::group Group{GroupMsg->FromGroup, GroupMsg->FromQQ};
    Target::Target Target{Target::TargetType::group, (void *)&Group};
    Plugin.BroadcastMessageEvent(&Target, GroupMsg->Msg, Database::AddGroupMsg(GroupMsg));
}

void Event::OnPrivateMsg(const PrivateMsg *PrivateMsg)
{
    Target::_private Private{PrivateMsg->FromQQ};
    Target::Target Target{Target::TargetType::_private, (void *)&Private};
    Plugin.BroadcastMessageEvent(&Target, PrivateMsg->Msg, Database::AddPrivateMsg(PrivateMsg));
}

void Event::OnNoticeMsg(const NoticeEvent::NoticeEvent *NoticeEvent)
{
    Plugin.BroadcastNoticeEvent(NoticeEvent);
}

void Event::OnRequestMsg(const RequestEvent::RequestEvent *RequestEvent)
{
    //Todo
    Plugin.BroadcastRequestEvent(RequestEvent, 0);
}

void PluginSystem::Load(
#if defined(_WIN_PLATFORM_)
    const wchar_t *
#endif
#if defined(_LINUX_PLATFORM_)
    const char *
#endif
        szFilePath)
{
    PluginList.clear();
#if defined(_WIN_PLATFORM_)
    wchar_t PluginPath[MAX_PATH + 1];
    wcscpy(PluginPath, szFilePath);
    wcscat(PluginPath, L"\\app\\*.mpk");
    long long handle;
    _wfinddata64_t fileinfo;
    handle = _wfindfirsti64(PluginPath, &fileinfo);
    if (handle != -1)
    {
        do
        {

        } while (!_wfindnexti64(handle, &fileinfo));
        _findclose(handle);
    }

    if (DevMode)
    {
        wchar_t _PluginPath[MAX_PATH + 1];
        wcscpy(PluginPath, szFilePath);
        wcscat(PluginPath, L"\\dev\\");
        wcscpy(_PluginPath, PluginPath);
        wcscat(_PluginPath, L"*");
        handle = _wfindfirsti64(_PluginPath, &fileinfo);
        if (handle != -1)
        {
            do
            {
                if (fileinfo.attrib == _A_SUBDIR)
                {
                    if (!wcscmp(fileinfo.name, L"."))
                        continue;
                    if (!wcscmp(fileinfo.name, L".."))
                        continue;
                    wchar_t PluginPath_[MAX_PATH + 1], PluginPath__[MAX_PATH + 1];
                    wcscpy(PluginPath_, PluginPath);
                    wcscat(PluginPath_, fileinfo.name);
                    wcscat(PluginPath_, L"\\");
                    wcscpy(PluginPath__, PluginPath_);
                    wcscat(PluginPath_, L"app.dll");
                    wcscat(PluginPath__, L"app.json");

                    HMODULE Handle = LoadLibrary(PluginPath_);
                    if (Handle == NULL)
                    {
                        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadPlugin", u8"LoadLibrary fail, GetLastError:%d", true, GetLastError());
                        continue;
                    }
                    typedef int(__stdcall * Initialize)(const uint64_t);
                    Initialize _Initialize = (Initialize)GetProcAddress(Handle, "Initialize");
                    if (_Initialize == NULL)
                    {
                        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadPlugin", u8"Can't get address of function Initialize");
                        continue;
                    }

                    std::ifstream input(PluginPath__);
                    if (!input.is_open())
                    {
                        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadPlugin", u8"Read Json error");
                        continue;
                    }
                    char Json[5000] = {0};
                    input.read(Json, 5000);
                    Json[input.gcount()] = 0;
                    input.close();

                    rapidjson::Document d;
                    d.Parse<rapidjson::kParseCommentsFlag>(Json);

                    if (d.HasParseError())
                    {
                        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadPlugin", u8"Parse Json fail, ParseErrorCode:%d, ErrorOffset:%llu", true, d.GetParseError(), d.GetErrorOffset());
                        continue;
                    }

                    if (!d.HasMember("name"))
                    {
                        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadPlugin", u8"Json is incomplete");
                        d.Clear();
                        continue;
                    }

                    Plugin ThisPlugin;

                    ThisPlugin.Name = new char8_t[d["name"].GetStringLength() + 1];
                    memcpy(ThisPlugin.Name, d["name"].GetString(), d["name"].GetStringLength());
                    ThisPlugin.Name[d["name"].GetStringLength()] = 0;
                    if (!d.HasMember("appid"))
                    {
                        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadPlugin", u8"Json is incomplete");
                        d.Clear();
                        continue;
                    }
                    ThisPlugin.Appid = new char8_t[d["appid"].GetStringLength() + 1];
                    memcpy(ThisPlugin.Appid, d["appid"].GetString(), d["appid"].GetStringLength());
                    ThisPlugin.Appid[d["appid"].GetStringLength()] = 0;
                    if (wcscmp(Iconv::Utf8ToUnicode(ThisPlugin.Appid).c_str(), fileinfo.name))
                    {
                        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadPlugin", u8"Appid is not same");
                        d.Clear();
                        continue;
                    }
                    if (!d.HasMember("version"))
                    {
                        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadPlugin", u8"Json is incomplete");
                        d.Clear();
                        continue;
                    }
                    ThisPlugin.Version = new char8_t[d["version"].GetStringLength() + 1];
                    memcpy(ThisPlugin.Version, d["version"].GetString(), d["version"].GetStringLength());
                    ThisPlugin.Version[d["version"].GetStringLength()] = 0;
                    if (!d.HasMember("author"))
                    {
                        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadPlugin", u8"Json is incomplete");
                        d.Clear();
                        continue;
                    }
                    ThisPlugin.Author = new char8_t[d["author"].GetStringLength() + 1];
                    memcpy(ThisPlugin.Author, d["author"].GetString(), d["author"].GetStringLength());
                    ThisPlugin.Author[d["author"].GetStringLength()] = 0;
                    if (!d.HasMember("description"))
                    {
                        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadPlugin", u8"Json is incomplete");
                        d.Clear();
                        continue;
                    }
                    ThisPlugin.Description = new char8_t[d["description"].GetStringLength() + 1];
                    memcpy(ThisPlugin.Description, d["description"].GetString(), d["description"].GetStringLength());
                    ThisPlugin.Description[d["description"].GetStringLength()] = 0;
                    if (d.HasMember("event"))
                    {
                        const rapidjson::Value &a = d["event"];
                        ThisPlugin.EventList.resize(a.Size());
                        uint j = 0;
                        bool error = false;
                        for (auto &v : a.GetArray())
                        {
                            if (!v.HasMember("type"))
                            {
                                Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadPlugin", u8"Json is incomplete");
                                d.Clear();
                                error = true;
                                break;
                            }
                            ThisPlugin.EventList[j].type = v["type"].GetInt();
                            if (!v.HasMember("function"))
                            {
                                Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadPlugin", u8"Json is incomplete");
                                d.Clear();
                                error = true;
                                break;
                            }
                            ThisPlugin.EventList[j].function = (void *)GetProcAddress(Handle, v["function"].GetString());
                            if (ThisPlugin.EventList[j].function == NULL)
                            {
                                Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadPlugin", u8"GetProcAddress error, function name:%s", true, v["function"].GetString());
                                d.Clear();
                                error = true;
                                break;
                            }
                            if (!v.HasMember("subevent"))
                            {
                                Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadPlugin", u8"Json is incomplete");
                                d.Clear();
                                error = true;
                                break;
                            }
                            const rapidjson::Value &a_ = v["subevent"];
                            for (auto &v_ : a_.GetArray())
                            {
                                if (!v_.HasMember("id"))
                                {
                                    Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadPlugin", u8"Json is incomplete");
                                    d.Clear();
                                    error = true;
                                    break;
                                }
                                ThisPlugin.EventList[j].subevent |= 1 << v_["id"].GetInt();
                                if (!v_.HasMember("priority"))
                                {
                                    Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadPlugin", u8"Json is incomplete");
                                    d.Clear();
                                    error = true;
                                    break;
                                }
                                switch (v_["id"].GetInt())
                                {
                                case 1:
                                    ThisPlugin.EventList[j].priority |= v_["priority"].GetInt();
                                    break;
                                case 2:
                                    ThisPlugin.EventList[j].priority |= v_["priority"].GetInt() << 2;
                                    break;
                                case 4:
                                    ThisPlugin.EventList[j].priority |= v_["priority"].GetInt() << 4;
                                    break;
                                case 8:
                                    ThisPlugin.EventList[j].priority |= v_["priority"].GetInt() << 6;
                                    break;
                                }
                            }
                            if (error)
                                break;
                            j++;
                        }
                        if (error)
                            continue;
                    }
                    if (d.HasMember("menu"))
                    {
                        if (!d["menu"].HasMember("function"))
                        {
                            Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadPlugin", u8"Json is incomplete");
                            d.Clear();
                            continue;
                        }
                        ThisPlugin.Menu.function = (PluginSystem::Menu::Munu)GetProcAddress(Handle, d["menu"]["function"].GetString());
                        if (ThisPlugin.Menu.function == NULL)
                        {
                            Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadPlugin", u8"GetProcAddress error, function name:%s", true, d["menu"]["function"].GetString());
                            d.Clear();
                            continue;
                        }
                        if (!d["menu"].HasMember("caption"))
                        {
                            Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadPlugin", u8"Json is incomplete");
                            d.Clear();
                            continue;
                        }
                        const rapidjson::Value &a = d["menu"]["caption"];
                        ThisPlugin.Menu.CaptionList.resize(a.Size());
                        uint k = 0;
                        for (auto &v : a.GetArray())
                        {
                            ThisPlugin.Menu.CaptionList[k] = new char8_t[v.GetStringLength() + 1];
                            memcpy(ThisPlugin.Menu.CaptionList[k], v.GetString(), v.GetStringLength());
                            ThisPlugin.Menu.CaptionList[k][v.GetStringLength()] = 0;
                            k++;
                        }
                    }
                    if (d.HasMember("auth"))
                    {
                        for (size_t j = 0; j < d["auth"].Size(); j++)
                            ThisPlugin.Auth |= (1 << d["auth"][j].GetInt());
                    }

                    ThisPlugin.AuthCode = Utils::GetRandom();
                    _Initialize(ThisPlugin.AuthCode);
                    PluginList.emplace(PluginList.end(), &ThisPlugin);
                }
            } while (!_wfindnexti64(handle, &fileinfo));
            _findclose(handle);
        }
    }
#endif

#if defined(_LINUX_PLATFORM_)
    char PluginPath[PATH_MAX + 1];
    DIR *dir;
    dirent *dirent;
    strcpy(PluginPath, szFilePath);
    strcat(PluginPath, "/app/");
    dir = opendir(PluginPath);
    if (dir != 0)
    {
        std::regex reg_obj(".*.mpk", std::regex::icase);
        while ((dirent = readdir(dir)) != NULL)
        {
            if (std::regex_match(dirent->d_name, reg_obj)) // regex_match()匹配
            {
                dirent->d_name;
            }
        }
        closedir(dir);
    }

    if (DevMode)
    {
        strcpy(PluginPath, szFilePath);
        strcat(PluginPath, "/dev/");
        dir = opendir(PluginPath);
        if (dir != 0)
        {
            while ((dirent = readdir(dir)) != NULL)
            {
                if (dirent->d_type == DT_DIR)
                {
                    if (!strcmp(dirent->d_name, "."))
                        continue;
                    if (!strcmp(dirent->d_name, ".."))
                        continue;

                    char PluginPath_[PATH_MAX + 1], PluginPath__[PATH_MAX + 1];
                    strcpy(PluginPath_, PluginPath);
                    strcat(PluginPath_, dirent->d_name);
                    strcat(PluginPath_, "/");
                    strcpy(PluginPath__, PluginPath_);
                    strcat(PluginPath_, "libapp.so");
                    strcat(PluginPath__, "app.json");

                    void *Handle = dlopen(PluginPath_, RTLD_NOW);
                    if (Handle == NULL)
                    {
                        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadPlugin", u8"dlopen fail, GetLastError:%d", true, dlerror());
                        continue;
                    }
                    typedef int (*Initialize)(const uint64_t);
                    Initialize _Initialize = (Initialize)dlsym(Handle, "Initialize");
                    if (_Initialize == NULL)
                    {
                        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadPlugin", u8"Can't get address of function Initialize");
                        continue;
                    }

                    std::ifstream input(PluginPath__);
                    if (!input.is_open())
                    {
                        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadPlugin", u8"Read Json error");
                        continue;
                    }
                    char Json[5000] = {0};
                    input.read(Json, 5000);
                    Json[input.gcount()] = 0;
                    input.close();

                    rapidjson::Document d;
                    d.Parse<rapidjson::kParseCommentsFlag>(Json);

                    if (d.HasParseError())
                    {
                        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadPlugin", u8"Parse Json fail, ParseErrorCode:%d, ErrorOffset:%llu", true, d.GetParseError(), d.GetErrorOffset());
                        return;
                    }

                    if (!d.HasMember("name"))
                    {
                        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadPlugin", u8"Json is incomplete");
                        d.Clear();
                        return;
                    }

                    Plugin ThisPlugin;

                    ThisPlugin.Name = new char8_t[d["name"].GetStringLength() + 1];
                    memcpy(ThisPlugin.Name, d["name"].GetString(), d["name"].GetStringLength());
                    ThisPlugin.Name[d["name"].GetStringLength()] = 0;
                    if (!d.HasMember("appid"))
                    {
                        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadPlugin", u8"Json is incomplete");
                        d.Clear();
                        return;
                    }
                    ThisPlugin.Appid = new char8_t[d["appid"].GetStringLength() + 1];
                    memcpy(ThisPlugin.Appid, d["appid"].GetString(), d["appid"].GetStringLength());
                    ThisPlugin.Appid[d["appid"].GetStringLength()] = 0;
                    if (strcmp((const char *)ThisPlugin.Appid, dirent->d_name))
                    {
                        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadPlugin", u8"Appid is not same");
                        d.Clear();
                        return;
                    }
                    if (!d.HasMember("version"))
                    {
                        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadPlugin", u8"Json is incomplete");
                        d.Clear();
                        return;
                    }
                    ThisPlugin.Version = new char8_t[d["version"].GetStringLength() + 1];
                    memcpy(ThisPlugin.Version, d["version"].GetString(), d["version"].GetStringLength());
                    ThisPlugin.Version[d["version"].GetStringLength()] = 0;
                    if (!d.HasMember("author"))
                    {
                        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadPlugin", u8"Json is incomplete");
                        d.Clear();
                        return;
                    }
                    ThisPlugin.Author = new char8_t[d["author"].GetStringLength() + 1];
                    memcpy(ThisPlugin.Author, d["author"].GetString(), d["author"].GetStringLength());
                    ThisPlugin.Author[d["author"].GetStringLength()] = 0;
                    if (!d.HasMember("description"))
                    {
                        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadPlugin", u8"Json is incomplete");
                        d.Clear();
                        return;
                    }
                    ThisPlugin.Description = new char8_t[d["description"].GetStringLength() + 1];
                    memcpy(ThisPlugin.Description, d["description"].GetString(), d["description"].GetStringLength());
                    ThisPlugin.Description[d["description"].GetS5tringLength()] = 0;
                    if (d.HasMember("event"))
                    {
                        const rapidjson::Value &a = d["event"];
                        ThisPlugin.EventList.resize(a.Size());
                        uint j = 0;
                        bool error = false;
                        for (auto &v : a.GetArray())
                        {
                            if (!v.HasMember("type"))
                            {
                                Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadPlugin", u8"Json is incomplete");
                                d.Clear();
                                error = true;
                                break;
                            }
                            ThisPlugin.EventList[j].type = v["type"].GetInt();
                            if (!v.HasMember("function"))
                            {
                                Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadPlugin", u8"Json is incomplete");
                                d.Clear();
                                error = true;
                                break;
                            }
                            ThisPlugin.EventList[j].function = dlsym(Handle, v["function"].GetString());
                            if (ThisPlugin.EventList[j].function == NULL)
                            {
                                Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadPlugin", u8"GetProcAddress error, function name:%s", true, v["function"].GetString());
                                d.Clear();
                                error = true;
                                break;
                            }
                            if (!v.HasMember("subevent"))
                            {
                                Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadPlugin", u8"Json is incomplete");
                                d.Clear();
                                error = true;
                                break;
                            }
                            const rapidjson::Value &a_ = v["subevent"];
                            for (auto &v_ : a_.GetArray())
                            {
                                if (!v_.HasMember("id"))
                                {
                                    Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadPlugin", u8"Json is incomplete");
                                    d.Clear();
                                    error = true;
                                    break;
                                }
                                ThisPlugin.EventList[j].subevent |= 1 << v_["id"].GetInt();
                                if (!v_.HasMember("priority"))
                                {
                                    Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadPlugin", u8"Json is incomplete");
                                    d.Clear();
                                    error = true;
                                    break;
                                }
                                switch (v_["id"].GetInt())
                                {
                                case 1:
                                    ThisPlugin.EventList[j].priority |= v_["priority"].GetInt();
                                    break;
                                case 2:
                                    ThisPlugin.EventList[j].priority |= v_["priority"].GetInt() << 2;
                                    break;
                                case 4:
                                    ThisPlugin.EventList[j].priority |= v_["priority"].GetInt() << 4;
                                    break;
                                case 8:
                                    ThisPlugin.EventList[j].priority |= v_["priority"].GetInt() << 6;
                                    break;
                                }
                            }
                            if (error)
                                break;
                            j++;
                        }
                        if (error)
                            return;
                    }
                    if (d.HasMember("menu"))
                    {
                        if (!d["menu"].HasMember("function"))
                        {
                            Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadPlugin", u8"Json is incomplete");
                            d.Clear();
                            return;
                        }
                        ThisPlugin.Menu.function = (PluginSystem::Menu::Munu)dlsym(Handle, d["menu"]["function"].GetString());
                        if (ThisPlugin.Menu.function == NULL)
                        {
                            Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadPlugin", u8"GetProcAddress error, function name:%s", true, d["menu"]["function"].GetString());
                            d.Clear();
                            return;
                        }
                        if (!d["menu"].HasMember("caption"))
                        {
                            Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadPlugin", u8"Json is incomplete");
                            d.Clear();
                            return;
                        }
                        const rapidjson::Value &a = d["menu"]["caption"];
                        ThisPlugin.Menu.CaptionList.resize(a.Size());
                        uint k = 0;
                        for (auto &v : a.GetArray())
                        {
                            ThisPlugin.Menu.CaptionList[k] = new char8_t[v.GetStringLength() + 1];
                            memcpy(ThisPlugin.Menu.CaptionList[k], v.GetString(), v.GetStringLength());
                            ThisPlugin.Menu.CaptionList[k][v.GetStringLength()] = 0;
                            k++;
                        }
                    }
                    if (d.HasMember("auth"))
                    {
                        for (size_t j = 0; j < d["auth"].Size(); j++)
                            ThisPlugin.Auth |= (1 << d["auth"][j].GetInt());
                    }

                    ThisPlugin.AuthCode = Utils::GetRandom();
                    _Initialize(ThisPlugin.AuthCode);
                    PluginList.emplace(PluginList.end(), &ThisPlugin);
                }
            }
            closedir(dir);
        }
    }
#endif

#if defined(_WIN_PLATFORM_)
    wchar_t SettingFilePath[PATH_MAX + 1];
    wcscpy(SettingFilePath, DataPath);
    wcscat(SettingFilePath, L"setting.json");
#endif

#if defined(_LINUX_PLATFORM_)
    char SettingFilePath[PATH_MAX + 1];
    strcpy(SettingFilePath, DataPath);
    strcat(SettingFilePath, "setting.json");
#endif

    std::ifstream input(SettingFilePath);
    if (!input.is_open())
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadPlugin", u8"Read Setting Json error");
        return;
    }
    char Json[1000] = {0};
    input.read(Json, 1000);
    Json[input.gcount()] = 0;
    input.close();

    rapidjson::Document d;
    d.Parse<rapidjson::kParseCommentsFlag>(Json);

    if (d.HasParseError())
    {
        Log::AddLog(Log::LogType::_ERROR, Log::MsgType::PROGRAM, u8"LoadPlugin", u8"Parse Setting Json fail, ParseErrorCode:%d, ErrorOffset:%llu", true, d.GetParseError(), d.GetErrorOffset());
        return;
    }
    for (size_t i = 0; i < PluginList.size(); i++)
    {
        if (d.HasMember((const char *)PluginList[i].Appid))
            if (d[(const char *)PluginList[i].Appid].HasMember("enable"))
                PluginList[i].Enable = d[(const char *)PluginList[i].Appid]["enable"].GetBool();
    }

    LoadEvent();

    BroadcastLifeCycleEvent(::Event::LifeCycleEvent::LifeCycleEventType::StartUp);
}

void PluginSystem::LoadEvent()
{
    LifeCycleEventList->clear();
    MessageEventList->clear();
    NoticeEventList->clear();
    RequestEventList->clear();

    std::vector<PluginSystem::Event> EventList_;
    for (size_t i = 0; i < PluginList.size(); i++)
    {
        if (!PluginList[i].Enable)
            continue;
        for (size_t j = 0; j < PluginList[i].EventList.size(); j++)
        {
            if (PluginList[i].EventList[j].type == 0)
                EventList_.insert(EventList_.end(), PluginList[i].EventList[j]);
        }
    }
    for (size_t i = 0; i < 4; i++) //max 0 mini 3
    {
        for (size_t j = 0; j < EventList_.size(); j++)
        {
            for (size_t k = 0; k < 4; k++)
            {
                if ((EventList_[j].subevent & (1 << k)) == 0)
                    continue;
                if (((EventList_[j].priority >> (k * 2)) & 3) == i)
                    LifeCycleEventList[k].insert(LifeCycleEventList[k].end(), (LifeCycleEvent)EventList_[j].function);
            }
        }
    }

    EventList_.clear();
    for (size_t i = 0; i < PluginList.size(); i++)
    {
        if (!PluginList[i].Enable)
            continue;
        for (size_t j = 0; j < PluginList[i].EventList.size(); j++)
        {
            if (PluginList[i].EventList[j].type == 1)
                EventList_.insert(EventList_.end(), PluginList[i].EventList[j]);
        }
    }
    for (size_t i = 0; i < 4; i++) //max 0 mini 3
    {
        for (size_t j = 0; j < EventList_.size(); j++)
        {
            for (size_t k = 0; k < 3; k++)
            {
                if ((EventList_[j].subevent & (1 << k)) == 0)
                    continue;
                if (((EventList_[j].priority >> (k * 2)) & 3) == i)
                    MessageEventList[k].insert(MessageEventList[k].end(), (MessageEvent)EventList_[j].function);
            }
        }
    }

    EventList_.clear();
    for (size_t i = 0; i < PluginList.size(); i++)
    {
        if (!PluginList[i].Enable)
            continue;
        for (size_t j = 0; j < PluginList[i].EventList.size(); j++)
        {
            if (PluginList[i].EventList[j].type == 2)
                EventList_.insert(EventList_.end(), PluginList[i].EventList[j]);
        }
    }
    for (size_t i = 0; i < 4; i++) //max 0 mini 3
    {
        for (size_t j = 0; j < EventList_.size(); j++)
        {
            for (size_t k = 0; k < 4; k++)
            {
                if ((EventList_[j].subevent & (1 << k)) == 0)
                    continue;
                if (((EventList_[j].priority >> (k * 2)) & 3) == i)
                    NoticeEventList[k].insert(NoticeEventList[k].end(), (NoticeEvent)EventList_[j].function);
            }
        }
    }

    EventList_.clear();
    for (size_t i = 0; i < PluginList.size(); i++)
    {
        if (!PluginList[i].Enable)
            continue;
        for (size_t j = 0; j < PluginList[i].EventList.size(); j++)
        {
            if (PluginList[i].EventList[j].type == 3)
                EventList_.insert(EventList_.end(), PluginList[i].EventList[j]);
        }
    }
    for (size_t i = 0; i < 4; i++) //max 0 mini 3
    {
        for (size_t j = 0; j < EventList_.size(); j++)
        {
            for (size_t k = 0; k < 2; k++)
            {
                if ((EventList_[j].subevent & (1 << k)) == 0)
                    continue;
                if (((EventList_[j].priority >> (k * 2)) & 3) == i)
                    RequestEventList[k].insert(RequestEventList[k].end(), (RequestEvent)EventList_[j].function);
            }
        }
    }
}

bool PluginSystem::VieryAuth(const uint64_t auth_code, const int auth)
{
    for (size_t i = 0; i < PluginList.size(); i++)
    {
        if (PluginList[i].AuthCode == auth_code)
        {
            if (PluginList[i].Enable)
            {
                return (PluginList[i].Auth & (1 << auth)) || !auth;
            }
        }
    }
    return false;
}

const char8_t *PluginSystem::AuthCode2Name(const uint64_t auth_code)
{
    for (size_t i = 0; i < PluginList.size(); i++)
    {
        if (PluginList[i].AuthCode == auth_code)
        {
            return PluginList[i].Name;
        }
    }
    return u8"";
}

void PluginSystem::BroadcastLifeCycleEvent(const ::Event::LifeCycleEvent::LifeCycleEventType LifeCycleEventType)
{
    for (size_t i = 0; i < LifeCycleEventList[static_cast<int>(LifeCycleEventType)].size(); i++)
    {
        LifeCycleEventList[static_cast<int>(LifeCycleEventType)][i](LifeCycleEventType);
    }
}

void PluginSystem::BroadcastMessageEvent(const ::Target::Target *Target, const ::Message::Msg *Msg, const uint64_t MsgID)
{
    for (size_t i = 0; i < MessageEventList[static_cast<int>(Target->TargetType)].size(); i++)
    {
        if (MessageEventList[static_cast<int>(Target->TargetType)][i](Target, Msg, MsgID) == ::Event::ReturnType::block)
            break;
    }
}

void PluginSystem::BroadcastNoticeEvent(const ::Event::NoticeEvent::NoticeEvent *NoticeEvent)
{
    for (size_t i = 0; i < MessageEventList[static_cast<int>(NoticeEvent->NoticeEventType)].size(); i++)
    {
        if (NoticeEventList[static_cast<int>(NoticeEvent->NoticeEventType)][i](NoticeEvent) == ::Event::ReturnType::block)
            break;
    }
}

void PluginSystem::BroadcastRequestEvent(const ::Event::RequestEvent::RequestEvent *RequestEvent, const uint64_t responseFlag)
{
    for (size_t i = 0; i < RequestEventList[static_cast<int>(RequestEvent->RequestEventType)].size(); i++)
    {
        switch (RequestEventList[static_cast<int>(RequestEvent->RequestEventType)][i](RequestEvent, responseFlag))
        {
        case ::Event::RequestEvent::ReturnType::agree:

            return;
        case ::Event::RequestEvent::ReturnType::disagree:

            return;
        case ::Event::RequestEvent::ReturnType::ignore:
            break;
        }
    }
}
