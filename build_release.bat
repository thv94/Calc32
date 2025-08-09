@echo off

setlocal

IF NOT EXIST build\release mkdir build\release

pushd build\release

call cl -nologo /EHa- /GR- /Oi /TC /WX /W4 /FC /O2 /I"C:\Users\user\MyStuff\Code\Calc32\include" ..\..\src\calc.c ..\..\src\computations.c /link user32.lib gdi32.lib

popd
