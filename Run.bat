@echo off
cd /d "%~dp0my_runner_2017"
echo Building my_runner (mingw32-make)...
mingw32-make
if not exist my_runner.exe (
    echo.
    echo Build failed - see errors above.
    pause
    exit /b 1
)
echo.
echo Launching My Runner - hold SPACE to jump the sombrero, Escape to quit.
start "" my_runner.exe
