@echo off
setlocal ENABLEDELAYEDEXPANSION

::Author:BetaBin

set apkSrcPath=G:\xunlei_downloads

for %%i in ("G:\xunlei_downloads\*") do (
set tempname=%%i.apk
call "apktool.bat" d -f "%%i" "!tempname:~0,-4!"
)
