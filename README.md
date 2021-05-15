Language: **`English`** [`简体中文`](https://github.com/YuFanXing/MoeQ/blob/master/README_ZH.md)

# Brief Introduction

***MoeQ*** is *a QQ robot* crossing platforms(*Windows*&*Linux*) based on *Android QQ* or *Tim*.

It is still a *semi-finished product* now. If you want a *ready-made robot* frame, please go to the next door [mirai](https://www.google.com).

Because of busy school, I can't spare time to continue updating this project on my own, so I opened sources.

**Wish you can make it better!**

# Build

It is developed by VSCode with environment of Windows 10 Pro & WSL.

Package management is [*vcpkg*](https://github.com/Microsoft/vcpkg).

Please run following command to install dependencies.

```bash
#Windows
git clone https://github.com/microsoft/vcpkg
cd vcpkg
bootstrap-vcpkg.bat
vcpkg install openssl:x64-mingw-static
vcpkg install sqlite3:x64-mingw-static
vcpkg install zlib:x64-mingw-static
vcpkg integrate install

#Linux
git clone https://github.com/microsoft/vcpkg
cd vcpkg
./bootstrap-vcpkg.sh
./vcpkg install openssl:x64-linux
./vcpkg install sqlite3:x64-linux
./vcpkg install zlib:x64-linux
./vcpkg integrate install
```

Then, add "-DCMAKE_TOOLCHAIN_FILE=path" into your cmake command.

# Achieved

## Protocol

1. Log in and sign out.

2. Get friends and groups list.

2. Receive some group messages and private messages.

3. Send part of group messages and private messages.

4. Draw group and private message.

5. Do some friend and group actions.

6. ...

## Plugin System

1. Enable and disable.

2. Right control.

3. [C++ sdk](https://github.com/YuFanXing/mqcppsdk).

4. ...

# Features Under Way

2. Support voice message.
3. Fix bugs.
4. Update protocol version.
5. Optimize user Interface.
6. Plugin store.
7. ...

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

Version: *8.5.5*

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

Android Sdk("861891778567", 
            "460013521635791", 
            (const byte*)"\x86\xA4\x45\xBF\x44\xA2\xC2\x87\x59\x76\x18\xF6\xF3\x6E\xB6\x8C", 
            (const byte*)"\0\0\0\0\0\2", 
            "XiaoMi", 
            "MIX Alpha");
Sdk.QQ_Init("10001");
int state = Sdk.QQ_Login("Password");
if (state == LOGIN_SUCCESS)
    Sdk.QQ_Online();  //you log in successfully
```

# Dependencies

Thanks to the following projects for making this project greater!

1. ***[rapidjson](https://github.com/Tencent/rapidjson)***
3. ***[openssl](https://github.com/openssl/openssl)***
4. ***[sqlite3](https://sqlite.org/)***
5. ***[zlib](https://github.com/madler/zlib)***

**If it is not necessary,  please don't add more dependencies.**

