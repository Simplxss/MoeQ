cmake_minimum_required(VERSION 3.0.0)

project(MoeQ)
set(TARGET_NAME MoeQ)

set(CMAKE_CXX_STANDARD 20)


if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    link_libraries(ws2_32 wsock32)
    
    if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
    set(VCPKG_TARGET_TRIPLET x64-mingw-static)
    endif()

    if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
    set(VCPKG_TARGET_TRIPLET x64-linux)
    endif()
endif()

if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
    add_definitions(-D _WIN_PLATFORM_)
endif()

if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
    add_definitions(-D _LINUX_PLATFORM_)
endif()

if ("${DCMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_definitions(-D DEBUG)
endif()

if ("${DCMAKE_BUILD_TYPE}" STREQUAL "Release")
    add_definitions(-D RELEASE)
endif()

add_definitions(-D UNICODE -D X64)

find_package(ZLIB REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(unofficial-sqlite3 CONFIG REQUIRED)

aux_source_directory(Protocol DIR_SRCS)
add_executable(${TARGET_NAME} ${DIR_SRCS} "MoeQ.cpp")

target_link_libraries(${TARGET_NAME} PRIVATE ZLIB::ZLIB)
target_link_libraries(${TARGET_NAME} PRIVATE unofficial::sqlite3::sqlite3)
target_link_libraries(${TARGET_NAME} PRIVATE OpenSSL::SSL OpenSSL::Crypto)

message(STATUS ${TARGET_NAME})
