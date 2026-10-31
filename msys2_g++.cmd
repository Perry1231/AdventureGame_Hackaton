@echo off
setlocal
set MSYS2_PATH_TYPE=map
set MSYS2_DEFAULT_PATH=C:\msys64\usr\bin;C:\msys64\ucrt64\bin;C:\msys64\mingw64\bin
set PATH=C:\msys64\usr\bin;C:\msys64\ucrt64\bin;%PATH%
"C:\msys64\ucrt64\bin\g++.exe" %*
