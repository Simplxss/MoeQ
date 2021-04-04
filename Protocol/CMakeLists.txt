cmake_minimum_required(VERSION 3.0.0)
file(GLOB_RECURSE SOURCES "*.cpp")
add_executable(${TARGET_NAME} ${SOURCES})