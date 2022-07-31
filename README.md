Language: **`English`** [`简体中文`](https://github.com/YuFanXing/MoeQ/blob/master/README_ZH.md)

# Brief Introduction

***MoeQ*** is *a QQ robot* crossing platforms(*Windows*&*Linux*) based on *Android QQ* or *Tim*.

It is still a *semi-finished product* now. If you want a *ready-made robot* frame, please go to the next door [*mirai*](https://github.com/mamoe/mirai).

**Wish you can make it better!**

# Build

It is developed by VSCode with environment of Windows 11 & WSL.

The package management is [*vcpkg*](https://github.com/Microsoft/vcpkg).

The compilers that we use are [*MinGW64*](http://winlibs.com/) on Windows and *gcc-12* on Linux.

There are a lot of features of c++11 and c++23 using by this project, please notice the support of your compilers.

# Achieved

## Protocol

1. Log in and sign out.(include second login)

2. Get friends and groups list.

3. Receive group messages and private messages(text,classcal_face,picture,json).

4. Send part of group messages and private messages.

5. Draw group and private message.

6. Do some friend and group actions.

7. ...

## Plugin System

1. Enable and disable.

2. Right control.

3. [*C++ sdk*](https://github.com/MoeQ-Team/mqcppsdk).

4. ...

# Features Under Way

1. Support voice message.

2. Update protocol version.

3. Optimize user Interface.

4. Plugin store.

5. ...

# Files Usage

`./MoeQ.cpp` The entrance of the program.

`./include` Include the head files of dependencies.

`./Protocol` Include QQ protocol files.

`./PluginSystem` Include plugin control files.

`./Utils` Include utils.

`./Protocol/Android.cpp` `./Protocol/Tim.cpp` The protocols of *QQ*.

`./Protocol/Log.cpp` Database and log system.

`./PluginSystem/PluginSystem.cpp` The plugins control system.

`./PluginSystem/ExportFunction.cpp` The export functions to plugins.

`./Utils/Utils.cpp` Include encode, compress, algorithm and other tools.

`./Utils/Protobuf.cpp` `./Utils/JceStruct.cpp` `./Utils/Pack.cpp` Include some packing measures.

# Protocol

**If you want to help us improve or expand features, you should learn the following.**

But, you **CAN'T** add features like *send or receive red envelopes*.

### *Android QQ* Protocol

File: `./Protocol/Android.cpp` 

Version: *8.8.0*

|               Function Name               |              Usage              |
| :---------------------------------------: | :-----------------------------: |
|          Android::Fun_Send_Sync           |   send a packet synchronously   |
|            Android::Fun_Handle            | handle server broadcast message |
|          Android::Fun_Life_Event          |        life cycle event         |
|     Android::Make_Body_Request_Packet     |         pack jce-struct         |
| Android::Unpack_OnlinePush_PbPushGroupMsg |        get group message        |
| Android::Unpack_OnlinePush_PbPushTransMsg |    get group action message     |
|   Android::Unpack_MessageSvc_PushNotify   |       get private message       |

### *Tim* Protocol

File: `./Protocol/Tim.cpp`

Version: *3.3.1*

# Example

If you just want to use the protocol,  following is the simplest way of using the *Android* class.

```c++
#include "\Protocol\Android.h"

// IMEI 861891778567   IMSI 460013521635791   GUID 86A445BF44A2C287597618F6F36EB68C   MAC 4F923C3D4568   4F:92:3C:3D:45:68
// Remember to change it randomly
Android Sdk("861891778567",
            "460013521635791",
            (const byte *)"\x86\xA4\x45\xBF\x44\xA2\xC2\x87\x59\x76\x18\xF6\xF3\x6E\xB6\x8C",
            (const byte *)"\x4F\x92\x3C\x3D\x45\x68",
            "XiaoMi",
            "MIX Alpha");
int main()
{
    Sdk.QQ_Init("10001");
    int state = Sdk.QQ_Login("Password");
check:
    switch (state)
    {
    case LOGIN_SUCCESS:
        // Login Successfully!
        Sdk.QQ_Login_Finish();
        Sdk.QQ_Online();
        break;
    case LOGIN_VERIY:
        // Slider verification code
        // Sdk.QQ_Get_Viery_Ticket();
        // state = Sdk.QQ_Viery_Ticket("Ticket");
        goto check;
    case LOGIN_VERIY_SMS:
        // Driver Lock
        // Sdk.QQ_Get_Viery_PhoneNumber()
        // Sdk.QQ_Send_Sms();
        // state = Sdk.QQ_Viery_Sms("000000");
        goto check;
    default:
        // Login failed
        // error code: state
        // error message: Sdk.QQ_GetErrorMsg();
    }
}
```

# Dependencies

Thanks to the following projects for making this project greater!

1. ***[imageinfo](https://github.com/xiaozhuai/imageinfo)***

2. ***[rapidjson](https://github.com/Tencent/rapidjson)***

3. ***[openssl](https://github.com/openssl/openssl)***

4. ***[sqlite3](https://github.com/sqlite/sqlite)***

5. ***[zlib](https://github.com/madler/zlib)***

**If it is not necessary,  please don't add more dependencies.**

