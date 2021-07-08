语言: [`English`](https://github.com/YuFanXing/MoeQ/blob/master/README.md) **`简体中文`**

# 简介

***MoeQ***是一个基于*安卓QQ*或*Tim*的跨平台(*Windows*&*Linux*)*QQ机器人*.

它现在还是一个半成品, 如果你想要的是一个成品的机器人框架, 请去[*mirai*](https://www.google.com).

部分协议代码和变量名参考*mirai*.

由于学业繁忙, 我无力继续支撑这个项目, 于是将其开源.

**希望你们的努力能让它变得更好!**

# 构建

此项目在Windows 10 Pro & WSL环境下使用VSCode进行开发.

本项目使用了[*vcpkg*](https://github.com/Microsoft/vcpkg)作为包管理器, 请先执行如下命令来安装必要的依赖.

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

接着, 请添加"-DCMAKE_TOOLCHAIN_FILE=path"到CMake的命令行中.

本项目在Windows上使用的编译器为[*MinGW64*](http://winlibs.com/)或*MSVC*, Linux上使用的编译器为*gcc-10*.

本程序使用了许多的c++11和c++20特性, 请注意编译器的支持性.

**注意:如果你使用MinGW64来构建程序, 请替换"path-to-build\CMakeFiles\MoeQ.dir\compiler_depend.make"文件中所有的"\:"为":"**


# 依赖项

感谢以下这些项目铸就了今天的这个项目!

1. ***[rapidjson](https://github.com/Tencent/rapidjson)***
2. ***[openssl](https://github.com/openssl/openssl)***
3. ***[sqlite3](https://sqlite.org/)***
4. ***[zlib](https://github.com/madler/zlib)***

**如果非必要, 请不要添加其他依赖项.**

