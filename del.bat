@echo off
set "folder=src"

REM 进入源代码目录
cd "%folder%"

REM 遍历目录中的文件
for /r %%i in (*.o) do (
    REM 删除匹配的文件
    echo Deleting "%%i"
    del "%%i"
)

echo Deletion complete.

REM 返回原始目录
cd ..
