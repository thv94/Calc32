@echo off

setlocal

IF NOT EXIST build\debug mkdir build\debug

pushd build\debug

call cl -nologo /EHa- /GR- /Oi /TC /WX /W4 /Z7 /FC /Od /I"C:\Users\user\MyStuff\Code\Calc32\include" ..\..\src\calc.c ..\..\src\computations.c /link user32.lib gdi32.lib

popd
