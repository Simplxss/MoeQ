cmake_minimum_required(VERSION 3.0.0)

project(MoeQ)
set(TARGET_NAME MoeQ)

set(CMAKE_CXX_STANDARD 20)


if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
    set(VCPKG_TARGET_TRIPLET x64-windows)
    link_libraries(ws2_32 wsock32)
    endif()

    if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
    set(VCPKG_TARGET_TRIPLET x64-linux)
    endif()
endif()

if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
    add_definitions(-D _WIN_PLATFORM_)
    add_definitions(-D UNICODE)
endif()

if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
    add_definitions(-D _LINUX_PLATFORM_)
    set(CMAKE_CXX_FLAGS "-fvisibility=hidden ${CMAKE_CXX_FLAGS}")
endif()

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_definitions(-D DEBUG)
endif()

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    add_definitions(-D RELEASE)
endif()

add_definitions(-D X64)

find_package(ZLIB REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(unofficial-sqlite3 CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES "Protocol/*.cpp" "PluginSystem/*.cpp" "Utils/*.cpp")
add_executable(${TARGET_NAME} ${SOURCES} "MoeQ.cpp")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    target_compile_options(cqcppsdk INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/utf-8>)
endif()

target_link_libraries(${TARGET_NAME} PRIVATE ZLIB::ZLIB)
target_link_libraries(${TARGET_NAME} PRIVATE unofficial::sqlite3::sqlite3)
target_link_libraries(${TARGET_NAME} PRIVATE OpenSSL::SSL OpenSSL::Crypto)

message(STATUS ${TARGET_NAME})