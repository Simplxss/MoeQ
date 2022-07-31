语言: [`English`](https://github.com/YuFanXing/MoeQ/blob/master/README.md) **`简体中文`**

# 简介

***MoeQ***是一个基于*安卓QQ*或*Tim*的跨平台(*Windows*&*Linux*)*QQ机器人*.

目前MoeQ功能还未完善, 如果你想要的是一个成品的机器人框架, 请使用[*mirai*](https://www.google.com).

**希望你们的努力能让它变得更好!**

# 构建

此项目在Windows 11 & WSL下使用VSCode进行开发.

本项目使用了[*vcpkg*](https://github.com/Microsoft/vcpkg)作为包管理器.

本项目在Windows上使用的编译器为[*MinGW64*](http://winlibs.com/), Linux上使用的编译器为*gcc-12*.

本程序使用了许多的c++11和c++23特性, 请注意编译器的支持性.

# 功能

## 协议

1. 登录和下线.(包括二次登录).

2. 获取好友和群列表.

3. 接收好友和群消息.

4. 发送部分好友和群消息(文本,表情,图片,json卡片).

5. 撤回好友和群消息.

6. 进行一些好友(发送赞)和群操作(禁言,移除群员,修改群管理员,修改群成员头衔,修改群成员名片).

7. ...

## 插件系统

1. 开启和停止插件.

2. 权限控制.

3. [*C++ sdk*](https://github.com/MoeQ-Team/mqcppsdk).

4. ...

# 画饼

1. 重写UI.

2. 插件商城.

3. ...

# 文件用途

`./MoeQ.cpp` 程序入口点.

`./include` 依赖项的头文件.

`./Protocol` 协议的实现代码.

`./PluginSystem` 插件控制系统.

`./Utils` 各种组件.

`./Protocol/Android.cpp` `./Protocol/Tim.cpp` 协议主文件.

`./Protocol/Log.cpp` 数据库和日志系统.

`./PluginSystem/PluginSystem.cpp` 插件控制主系统.

`./PluginSystem/ExportFunction.cpp` 给插件的公开函数.

`./Utils/Utils.cpp` 包含加解密, 压缩, 摘要算法和其他工具.

`./Utils/Protobuf.cpp` `./Utils/JceStruct.cpp` `./Utils/Pack.cpp` 组包方式实现.

# 协议

**如果你想要帮助改进或增加功能,你可能需要了解以下内容**

**重要:你不能添加与交易有关的功能**

### *安卓 QQ* 协议

文件: `./Protocol/Android.cpp` 

版本: *8.8.0*

|                  函数名                   |       用途       |
| :---------------------------------------: | :--------------: |
|          Android::Fun_Send_Sync           |    同步发送包    |
|            Android::Fun_Handle            | 处理服务器广播包 |
|          Android::Fun_Life_Event          |   生命周期事件   |
|     Android::Make_Body_Request_Packet     |  构造jce结构包   |
| Android::Unpack_OnlinePush_PbPushGroupMsg |    解析群消息    |
| Android::Unpack_OnlinePush_PbPushTransMsg |  解析群操作消息  |
|   Android::Unpack_MessageSvc_PushNotify   |   解析私聊消息   |

### *Tim* 协议

文件: `./Protocol/Tim.cpp`

版本: *3.3.1*

# 样例

如果你仅仅想使用本框架,  下面是使用的最简方式.

```c++
#include "\Protocol\Android.h"

// IMEI 861891778567   IMSI 460013521635791   GUID 86A445BF44A2C287597618F6F36EB68C   MAC 4F923C3D4568   4F:92:3C:3D:45:68
// 请随机修改这些值
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
        // 登录成功!
        Sdk.QQ_Login_Finish();
        Sdk.QQ_Online();
        break;
    case LOGIN_VERIY:
        // 滑块验证码
        // Sdk.QQ_Get_Viery_Ticket(); //获取滑块验证码网址
        // state = Sdk.QQ_Viery_Ticket("Ticket"); //提交验证码
        goto check;
    case LOGIN_VERIY_SMS:
        // 设备锁
        // Sdk.QQ_Get_Viery_PhoneNumber() //获取手机号
        // Sdk.QQ_Send_Sms(); //发送短信
        // state = Sdk.QQ_Viery_Sms("000000"); //提交验证码
        goto check;
    default:
        // 登录失败
        // 错误码: state
        // 错误信息: Sdk.QQ_GetErrorMsg();
    }
}
```


# 依赖项

感谢以下这些项目铸就了今天的这个项目!

1. ***[imageinfo](https://github.com/xiaozhuai/imageinfo)***

2. ***[rapidjson](https://github.com/Tencent/rapidjson)***

3. ***[openssl](https://github.com/openssl/openssl)***

4. ***[sqlite3](https://github.com/sqlite/sqlite)***

5. ***[zlib](https://github.com/madler/zlib)***

**如果非必要, 请不要添加其他依赖项.**

