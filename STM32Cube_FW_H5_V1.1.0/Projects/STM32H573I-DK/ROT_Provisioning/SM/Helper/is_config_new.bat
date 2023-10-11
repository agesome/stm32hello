:: is_config_new.bat
@echo off
setlocal enabledelayedexpansion
set filename=%~dp0../Binary/SecureManagerPackage.sfi
set timestamp_file=timestamp.txt
if not exist %filename% (
    echo SFI doesn't exists, using default configuration
    exit /b 1
)
if exist %timestamp_file% (
    set /p last_run_time=<%timestamp_file%
) else (
    set last_run_time=0
)

for %%A in ("%filename%") do set file_mod_time=%%~tA

set file_time_ms=%file_mod_time:~0,4%%file_mod_time:~5,2%%file_mod_time:~8,2%%file_mod_time:~11,2%%file_mod_time:~14,2%%file_mod_time:~17,2%%file_mod_time:~20,3%
set last_run_time_ms=%last_run_time:~0,4%%last_run_time:~5,2%%last_run_time:~8,2%%last_run_time:~11,2%%last_run_time:~14,2%%last_run_time:~17,2%%last_run_time:~20,3%


if %file_time_ms% GTR %last_run_time_ms% (
    echo Config is updated, project will be updated accordingly
    echo %file_mod_time% > %timestamp_file%
    exit /b 1
) else (
    echo Config is not updated, no update needed on project
    exit /b 0
)
