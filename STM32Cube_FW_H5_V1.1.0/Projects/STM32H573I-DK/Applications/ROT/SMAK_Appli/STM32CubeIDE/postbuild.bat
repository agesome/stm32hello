@ECHO OFF
:: Getting the Trusted Package Creator CLI path
set "projectdir=%~dp0"
pushd %projectdir%\..\..\..\..\ROT_Provisioning
set provisioningdir=%cd%
popd
call "%provisioningdir%\env.bat"

:: Enable delayed expansion
setlocal EnableDelayedExpansion

:: Environment variable for log file
set current_log_file="%projectdir%\postbuild.log"
echo. > %current_log_file%

:: arg1 is the config type (Debug, Release)
set "config=%1"

:: Copy SMAK Appli binary to Binary location
copy %projectdir%\%config%\STM32H573I-DK_SMAK_Appli.bin %projectdir%..\Binary\appli.bin
IF !errorlevel! NEQ 0 goto :error

%stm32tpccli% -pb "%provisioningdir%\SM\Images\SM_Code_Image.xml" >> %current_log_file% 2>&1
IF !errorlevel! NEQ 0 goto :error

%stm32tpccli% -pb "%provisioningdir%\SM\Images\SM_Code_Image_bin.xml" >> %current_log_file% 2>&1
IF !errorlevel! NEQ 0 goto :error
exit 0

:error
echo.
echo =====
echo ===== Error occurred.
echo ===== See %current_log_file% for details. Then try again.
echo =====
exit 1
