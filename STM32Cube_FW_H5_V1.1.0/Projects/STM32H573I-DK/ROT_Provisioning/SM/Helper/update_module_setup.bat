@ECHO OFF

call %~dp0is_config_new.bat
if %errorlevel%==0 (
    exit /b 0
)

call %~dp0../../env.bat

:: Environment variable for setting postbuild command with AppliCfg
set "projectdir=%~dp0..\"

:: Enable delayed expansion
setlocal EnableDelayedExpansion

:start
goto exe:
goto py:
:exe
::line for Windows executable
set "applicfg=%cube_fw_path%\Utilities\PC_Software\ROT_AppliConfig\dist\AppliCfg.exe"
set "python="
if exist %applicfg% (
echo run config Appli with Windows executable
goto update
)
:py
::called if we just want to use AppliCfg python (think to comment "goto exe:")
set "applicfg=%cube_fw_path%\Utilities\PC_Software\ROT_AppliConfig\AppliCfg.py"
set "python=python "

:update
set "AppliCfg=%python%%applicfg%"

:: TPC file with flash layout config information
set general_cfg_file="%projectdir%Config/SM_Config_General.xml"

:: TPC xml sections to configure
set fw_size="Firmware area Size"
set rom_fixed="Rom fixed"
set fw_dwl_offset="Firmware download area offset"
set fw_in_bin="Binary input file"
set fw_out_bin="Image output file"

set code_offset="NS appli primary offset"
set code_dwl_offset="NS appli secondary offset"
set code_size="NS appli size"
set reserved_offset="NS reserved area offset"
set reserved_size="NS reserved area size"

set code_offset_module_0="S Module 0 primary offset"
set code_dwl_offset_module_0="S Module 0 secondary offset"
set code_size_module_0="S Module 0 size"

:: Sizes
set SECTOR_SIZE=0x2000
set MODULE_HEADER_SIZE=0x20
set TRAILER_MAX_SIZE=0x800

:: ======================================================== Updating SMDK Module ===============================================

:: Flash layout files
set module_template_xml=%projectdir%..\SM\Images\SM_Module_Image_template.xml
set module_xml=%sm_module_0_boot_path_project%Images\SM_Module_0_Image.xml

set path_input_binary="!sm_module_0_boot_path_project!\Binary\module_0.bin"
set path_input_binary=!path_input_binary:\=/!
set path_output_binary="!sm_module_0_boot_path_project!\Binary\module_0_enc_sign.hex"
set path_output_binary=!path_output_binary:\=/!
set icf_file_module_0="!sm_module_0_boot_path_project!EWARM\ukapp.icf"
set config_sections_file="!sm_module_0_boot_path_project!Inc\ukapp_config_sections.h"

copy %module_template_xml% %module_xml%

for %%I in ("%module_xml%") do set image_dir_path=%%~dpI

for /f "delims=" %%a in ('%~dp0compute_rel_path.bat %~dp0..\Config %image_dir_path%') do set "resolvedPath=./%%a"

call %~dp0update_xml.bat %module_xml% %resolvedPath%/SM_Config_Keys.xml

%AppliCfg% xmlparam -c "--confirm" -n "Confirm" -h "1" -t "Data" -d "" %module_xml% --vb
if !errorlevel! neq 0 goto :error
%AppliCfg% xmlval -xml %general_cfg_file% -nxml %code_size_module_0% -n %fw_size% -e "val1*%SECTOR_SIZE%" %module_xml% --vb
if !errorlevel! neq 0 goto :error
%AppliCfg% xmlval -xml %general_cfg_file% -nxml %code_offset_module_0% -n %rom_fixed% -e "(val1*%SECTOR_SIZE%)+0xC000000" %module_xml% --vb
if !errorlevel! neq 0 goto :error
%AppliCfg% xmlval -xml %general_cfg_file% -nxml %code_dwl_offset_module_0% -n %fw_dwl_offset% -e "(val1*%SECTOR_SIZE%)+0x8000000" %module_xml% --vb
if !errorlevel! neq 0 goto :error
%AppliCfg% xmlval -v !path_output_binary! --string -n %fw_out_bin% %module_xml% --vb
if !errorlevel! neq 0 goto :error
%AppliCfg% xmlval -v !path_input_binary! --string -n %fw_in_bin% %module_xml% --vb
if !errorlevel! neq 0 goto :error

:: Updating Linker files
%AppliCfg% linker -xml %general_cfg_file% -nxml %code_offset_module_0% -n CODE_OFFSET !icf_file_module_0! --vb
if !errorlevel! neq 0 goto :error
%AppliCfg% linker -xml %general_cfg_file% -nxml %code_size_module_0% -n CODE_SIZE !icf_file_module_0! --vb
if !errorlevel! neq 0 goto :error

:: Updating ukapp_config_sections.h
%AppliCfg% definevalue -xml %general_cfg_file% -nxml %code_offset_module_0% -n UKAPP_MEMORY_REGION_CODE_ORIGIN -e "0x0C000000 + val1*%SECTOR_SIZE% + %MODULE_HEADER_SIZE%" !config_sections_file! --vb
if !errorlevel! neq 0 goto :error
%AppliCfg% definevalue -xml %general_cfg_file% -nxml %code_offset_module_0% -nxml %code_size_module_0% -n UKAPP_MEMORY_REGION_CODE_ORIGIN_END -e "0x0C000000 + val1*%SECTOR_SIZE% + val2*%SECTOR_SIZE% - %TRAILER_MAX_SIZE% + %MODULE_HEADER_SIZE%" !config_sections_file! --vb
if !errorlevel! neq 0 goto :error


:: ============================================================= End functions ===================================================
:: All the steps were executed correctly
echo        Successful application update according to flash layout
exit /b 0

:: Error when script is executed
:error
echo        Error, update_module_setup.bat script aborted >CON
exit /b 1
