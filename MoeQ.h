#if defined(_WIN_PLATFORM_)
#include <direct.h>
#endif

#if defined(_LINUX_PLATFORM_)
#include <unistd.h>
#endif

#include <filesystem>

#include "include/rapidjson/filewritestream.h"
#include "include/rapidjson/prettywriter.h"
#include "include/imageinfo/imageinfo.hpp"

#include "PluginSystem/ExportFunction.h"
