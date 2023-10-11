::@ECHO OFF
set prebuild_log_file="%~dp0prebuild.log"

call %~dp0env.bat
call %provisioning_dir%SM/Helper/update_nsapp_setup.bat > %prebuild_log_file% 2>&1

if %errorlevel% neq 0 goto :error

:: Updating fwu.h file with Module number
set fwu_file="%~dp0\Inc\fwu.h"
set AppliCfg="%cube_fw_path%\Utilities\PC_Software\ROT_AppliConfig\dist\AppliCfg.exe"
set general_cfg_file="%provisioning_dir%SM/Config/SM_Config_General.xml"
%AppliCfg% definevalue -xml %general_cfg_file% -nxml "Nb Secure Modules" -n NB_MODULE %fwu_file% --vb >> %prebuild_log_file% 2>&1
if %errorlevel% neq 0 goto :error

:: All the steps were executed correctly
echo        Successful application update according to flash layout
exit 0

:: Error when script is executed
:error
echo        Error, prebuild.bat script aborted, check prebuild.log >CON
exit 1
