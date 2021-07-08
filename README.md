Language: **`English`** [`简体中文`](https://github.com/YuFanXing/MoeQ/blob/master/README_ZH.md)

# Brief Introduction

***MoeQ*** is *a QQ robot* crossing platforms(*Windows*&*Linux*) based on *Android QQ* or *Tim*.

It is still a *semi-finished product* now. If you want a *ready-made robot* frame, please go to the next door [*mirai*](https://github.com/mamoe/mirai).

Some codes and names of variate are referred to *mirai*.

Because of busy school, I can't spare time to continue updating this project on my own, so I opened sources.

**Wish you can make it better!**

# Build

It is developed by VSCode with environment of Windows 10 Pro & WSL.

The package management is [*vcpkg*](https://github.com/Microsoft/vcpkg), please run following command to install dependencies.

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

#MacOS
git clone https://github.com/microsoft/vcpkg
cd vcpkg
./bootstrap-vcpkg.sh
./vcpkg install openssl:x64-macos
./vcpkg install sqlite3:x64-macos
./vcpkg install zlib:x64-macos
./vcpkg integrate install
```

Then, add "-DCMAKE_TOOLCHAIN_FILE=path" into your cmake command.

The compilers that we use are [*MinGW64*](http://winlibs.com/) or *MSVC* on Windows and *gcc-10* on Linux.

There are a lot of features of c++11 and c++20 using by this project, please notice the support of your compiler.

**Significant: If you use *MinGW64* to build your program, please replace all "\\:" in "path-to-build\CMakeFiles\MoeQ.dir\compiler_depend.make" to ":"**

# Achieved

## Protocol

1. Log in and sign out.

2. Get friends and groups list.

3. Receive some group messages and private messages.

4. Send part of group messages and private messages.

5. Draw group and private message.

6. Do some friend and group actions.

7. ...

## Plugin System

1. Enable and disable.

2. Right control.

3. [*C++ sdk*](https://github.com/YuFanXing/mqcppsdk).

4. ...

# Features Under Way

1. Support upload image and voice.

2. Support voice message.

3. Update protocol version.

4. Optimize user Interface.

5. Plugin store.

6. ...

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
2. ***[openssl](https://github.com/openssl/openssl)***
3. ***[sqlite3](https://sqlite.org/)***
4. ***[zlib](https://github.com/madler/zlib)***

**If it is not necessary,  please don't add more dependencies.**

