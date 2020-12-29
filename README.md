Language: **`English`** [`简体中文`](https://github.com/YuFanXing/MoeQ/README_ZH.md)

# Brief Introduction

***MoeQ*** is a QQ robot based on Android QQ 8.4.1.

Because of busy school, I can't continue update this project on my own, so I public it.

**Wish you can make it better!**


# Achieved


## Protocol

1. Log in and sign out.

2. Get friends and groups list.

2. Receive some group messages and private messages.

3. Send part of group messages and private messages.

4. Draw group message.

5. Do some friend and group actions.

6. ...


## Plugin System

1. Enable and Disable.

2. Right control.

3. [C++ sdk](https://github.com/YuFanXing/mqcppsdk).

4. ...


# Todo List

1. Some memory leak.
2. Support image message and voice message.
3. Fix bugs.
4. Update protocol version.
5. Plugin Management.
6. Plugin store.
8. ...

# Files Usage

`./MoeQ` Include source code of this project.

`./include` Include the head files of dependencies.

`./lib` Include the static link library of dependencies.



`./MoeQ/MoeQ.cpp` The entrance of the program.

`./MoeQ/MainFrm.cpp` The main window.

`./MoeQ/Android.cpp` The protocol of Android QQ.

`./MoeQ/PluginSystem.cpp` The plugins control system.

`./MoeQ/Utils.cpp` Include encode, compress, algorithm and some tools.



# Protocol Example

*Android QQ 8.4.1*



# Dependency

Thanks to the following projects for making this project greater!

1. *rapidjson*

2. *miniblink*
3. *openssl*
4. *zlib*
5. *curl*

**If it is not necessary,  please don't add more dependencies.**