del /q build\*
for /d %%x in (build\*) do @rd /s /q "%%x"
echo off
setlocal ENABLEDELAYEDEXPANSION
set params=
for /f %%i in ('dir src /b /a-d') do (
    set params=!params! "src/%%i"
)
echo on
gcc -m32 -ffreestanding -nostdlib -nostdinc %params% -o build/kernel