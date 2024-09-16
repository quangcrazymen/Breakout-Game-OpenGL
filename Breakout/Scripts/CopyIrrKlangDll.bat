echo "hello this is from post build"

cd Scripts

rem depend on the build configuration
set platform=%1
set buildConfig=%2

echo %platform%
echo %buildConfig%

if not exist ..\Build\%platform%\%buildConfig%\ikpMP3.dll (
	xcopy /z ..\..\dlls\ikpMP3.dll ..\Build\%platform%\%buildConfig%
)

if not exist ..\Build\%platform%\%buildConfig%\irrKlang.dll (
	xcopy /z ..\..\dlls\irrKlang.dll ..\Build\%platform%\%buildConfig%
)
