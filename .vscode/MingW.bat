@echo off
setlocal enabledelayedexpansion
set file=D:\QQ\MoeQ-C++\build\CMakeFiles\MoeQ.dir\compiler_depend.make
set file_tmp=D:\QQ\MoeQ-C++\build\CMakeFiles\MoeQ.dir\compiler_depend.make.tmp
set source1=\\:

set replaced1=:

for /f "delims=" %%i in (%file%) do (
    set str=%%i
        set "str=!str:%source1%=%replaced1%!"
        echo !str!>>%file_tmp%
)
move "%file_tmp%" "%file%"