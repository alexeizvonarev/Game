@echo off
color 2

echo Building...
cd ..\
echo %CD%

xcopy "Game\Data" "Build\out\Data" /E /Y /I

copy "Release\Game.exe" "Build\out"
copy "Release\*.dll" "Build\out\*.dll"

cd Build\
del "Release.zip"
del "Release.rar"

start WinRAR A -r "Release.zip" "out\"
start WinRAR A -r "Release.rar" "out\"
pause