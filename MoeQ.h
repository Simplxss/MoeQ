#if defined(_WIN_PLATFORM_)
#include <direct.h>
#endif

#if defined(_LINUX_PLATFORM_)
#include <unistd.h>
#endif

#include <filesystem>

#include "Protocol/ExportFunction.h"
