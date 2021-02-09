// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#define _CRT_SECURE_NO_WARNINGS

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#include "framework.h"
#include "resource.h"

#include <vector>
#include <random>
#include <chrono>

#include "Defined.h"

#include <zlib.h>
#include <sqlite3.h>
#include <openssl\sha.h>
#include <openssl\md5.h>
#include <openssl\ecdh.h>
#include <openssl\des.h>
#include "..\include\miniblink\wke.h" //include windows.h
#include "..\include\rapidjson\document.h"

#pragma comment(lib, "crypt32.lib")

#endif //PCH_H
