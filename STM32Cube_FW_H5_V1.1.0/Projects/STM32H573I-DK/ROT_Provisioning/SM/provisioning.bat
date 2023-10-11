:: Getting the Trusted Package Creator and STM32CubeProgammer CLI path
echo off
call %~dp0../env.bat

:: Enable delayed expansion
setlocal EnableDelayedExpansion

:: Environment variable for log file
set "projectdir=%~dp0"
set provisioning_log="%projectdir%provisioning.log"
set current_log_file=%provisioning_log%
echo. > %current_log_file%

:: Environment variable for CubeMx
set isGeneratedByCubeMX=%PROJECT_GENERATED_BY_CUBEMX%

:start
goto exe:
goto py:
:exe
:: called if we want to use AppliCfg executable
set "applicfg=%cube_fw_path%\Utilities\PC_Software\ROT_AppliConfig\dist\AppliCfg.exe"
set "python="
if exist %applicfg% (
echo run config Appli with Windows executable
goto update
)
:py
:: called if we just want to use AppliCfg python (think to comment "goto exe:")
set "applicfg=%cube_fw_path%\Utilities\PC_Software\ROT_AppliConfig\AppliCfg.py"
set "python=python "

:update
set "AppliCfg=%python%%applicfg%"

:: Environment variables for CubeProg
set vb=1
set connect_ur=-c port=SWD ap=1 mode=UR -vb %vb%
set connect=-c port=SWD ap=1 mode=HotPlug -vb %vb%
set connect_reset="-c port=SWD speed=fast ap=1 mode=Hotplug -hardRst -vb %vb%"

:: Environment variables for secure manager package versions
set binver=%projectdir%Binary\version.bat
if exist %binver% goto :getversions
echo %binver% missing. >> %current_log_file%
echo Please get STM3H5 Secure Manager package from st.com. >> %current_log_file%
goto :error_config

:getversions
call %binver%

:: Environment variables for binaries
set rsse_binary_path=%stm32programmercli%\..\RSSe\H5\%rsse_binary%
set ssfi_binary_path=%projectdir%Binary\%ssfi_binary%
set sfi_binary_path=%projectdir%Binary\SecureManagerPackage.sfi
set license=%projectdir%Keys\SFI_Global_License.bin

:: Initial configuration
echo =====
echo ===== Provisioning of Secure Manager Package
echo =====

echo =====     SSFI version: %ssfi_binary%
if exist %ssfi_binary_path% goto :rsse_sfi
echo %ssfi_binary_path% missing. >> %current_log_file%
echo Please get STM3H5 Secure Manager package from st.com. >> %current_log_file%
goto :error_config

:rsse_sfi

echo =====     RSSe SFI version: %rsse_binary%
if exist %rsse_binary_path% goto :vcp
set rsse_binary_path=%projectdir%ST\%rsse_binary%
if exist !rsse_binary_path! goto :vcp
echo !rsse_binary_path! missing. >> %current_log_file%
echo Please get latest version of STM32CubeProgrammer from st.com. >> %current_log_file%
goto :error_config

:vcp
echo =====
echo ===== Product state must be Open. Execute  \ROT_Provisioning\DA\regression.bat if not the case.
echo =====
echo.

:: ====================================================== STM32H5 product preparation =============================================
:: =============================================== Steps to create the SM_Config_General.obk file ===============================
echo Step 1 : Configuration
echo;
echo    * General configuration:
echo        From TrustedPackageCreator (tab H5-OBkey)
echo        Select SM_Config_General.xml (in \ROT_Provisioning\SM\Config)
echo        Update the configuration (if/as needed) then generate SM_Config_General.obk file
echo        Press any key to continue...
if [%1] neq [AUTO] pause >nul
echo        Processing OBKey file...

%stm32tpccli% -obk %projectdir%Config\SM_Config_General.xml >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
echo        Successful SM_Config_General.obk file generation

:: =============================================== Steps to create the SM_Config_Keys.obk file ==================================
echo;
echo    * OEM Keys configuration:
echo        From TrustedPackageCreator (tab H5-OBkey)
echo        Select SM_Config_Keys.xml (in \ROT_Provisioning\SM\Config)
echo        Warning: Default keys must NOT be used in a product. Make sure to regenerate your own keys!
echo        Update the configuration (if/as needed) then generate OBkey file
echo        Press any key to continue...
if [%1] neq [AUTO] pause >nul
echo        Processing OBKey file...

%stm32tpccli% -obk %projectdir%Config\SM_Config_Keys.xml >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
%stm32tpccli% -pb %projectdir%ST\SM_ST_Settings_1.xml >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
%stm32tpccli% -obk %projectdir%ST\SM_ST_Settings_2.xml >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
echo        Successful SM_Config_Keys.obk file generation

:: =============================================== Steps to create the DA_Config.obk file =========================================
echo;
echo    * DA configuration:
echo        Warning: Default keys must NOT be used in a product. Make sure to regenerate your own keys!
echo        From TrustedPackageCreator (tab H5-DA CertifGen),
echo        update the keys(s) (in \ROT_Provisioning\DA\Keys) and permissions (if/as needed)
echo        then regenerate the certificate(s)
echo        From TrustedPackageCreator (tab H5-OBKey),
echo        Select DA_Config.xml (in \ROT_Provisioning\DA\Config)
echo        Update the configuration (if/as needed) then generate DA_Config.obk file
echo        Press any key to continue...
if [%1] neq [AUTO] pause >nul

:: =============================================== Steps to create the Option_Bytes.csv file ======================================
echo;
echo    * Option Bytes configuration:
echo        From TrustedPackageCreator (tab H5-SFI Option Bytes)
echo        Select STM32H5xx, then Open Option_Bytes.csv file (in \ROT_Provisioning\SM\Config)
echo        Update the configuration (if/as needed) then generate Option_Bytes.csv file
echo        Press any key to continue...
if [%1] neq [AUTO] pause >nul

:: ================================================= Steps to create the SFI license file =========================================
echo;
echo    * SFI global license configuration:
echo        From TrustedPackageCreator (tab H5-License Gen)
echo        Open encryption key file (\ROT_Provisioning\SM\Keys\SFI_Encryption_Key.bin)
echo        and nonce file (\ROT_Provisioning\SM\Keys\SFI_Encryption_Nonce.bin),
echo        then regenerate them (if/as needed) with same name.
echo        Select Output license file (\ROT_Provisioning\SM\Keys\SFI_Global_License.bin)
echo        then Generate License (if/as needed) with same name.
echo        Press any key to continue...
if [%1] neq [AUTO] pause >nul

:: ======================================================== Step to generate SFI ==================================================
echo;
echo    * SFI file generation:
echo        Processing...

:: Flash layout files
set flash_layout_bin="%projectdir%Binary\FlashLayoutConfigs.bin"
set general_cfg_file="%projectdir%Config\SM_Config_General.xml"
set module_template_xml="%projectdir%Images\SM_Module_Image_template.xml"

:: Get effective flash layout
%AppliCfg% xmlval -b %flash_layout_bin% -b_el_idx 0  -nxml_el_idx "Flash Layout configuration index" -n "Nb Secure Modules" %general_cfg_file% --vb >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
%AppliCfg% xmlval -b %flash_layout_bin% -b_el_idx 4  -nxml_el_idx "Flash Layout configuration index" -n "S Module 0 primary offset" %general_cfg_file% --vb >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
%AppliCfg% xmlval -b %flash_layout_bin% -b_el_idx 5  -nxml_el_idx "Flash Layout configuration index" -n "S Module 0 secondary offset" %general_cfg_file% --vb >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
%AppliCfg% xmlval -b %flash_layout_bin% -b_el_idx 6  -nxml_el_idx "Flash Layout configuration index" -n "S Module 0 size" %general_cfg_file% --vb >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
%AppliCfg% xmlval -b %flash_layout_bin% -b_el_idx 7  -nxml_el_idx "Flash Layout configuration index" -n "S Module 1 primary offset" %general_cfg_file% --vb >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
%AppliCfg% xmlval -b %flash_layout_bin% -b_el_idx 8  -nxml_el_idx "Flash Layout configuration index" -n "S Module 1 secondary offset" %general_cfg_file% --vb >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
%AppliCfg% xmlval -b %flash_layout_bin% -b_el_idx 9  -nxml_el_idx "Flash Layout configuration index" -n "S Module 1 size" %general_cfg_file% --vb >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
%AppliCfg% xmlval -b %flash_layout_bin% -b_el_idx 10 -nxml_el_idx "Flash Layout configuration index" -n "S Module 2 primary offset" %general_cfg_file% --vb >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
%AppliCfg% xmlval -b %flash_layout_bin% -b_el_idx 11 -nxml_el_idx "Flash Layout configuration index" -n "S Module 2 secondary offset" %general_cfg_file% --vb >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
%AppliCfg% xmlval -b %flash_layout_bin% -b_el_idx 12 -nxml_el_idx "Flash Layout configuration index" -n "S Module 2 size" %general_cfg_file% --vb >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
%AppliCfg% xmlval -b %flash_layout_bin% -b_el_idx 13 -nxml_el_idx "Flash Layout configuration index" -n "S Module 3 primary offset" %general_cfg_file% --vb >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
%AppliCfg% xmlval -b %flash_layout_bin% -b_el_idx 14 -nxml_el_idx "Flash Layout configuration index" -n "S Module 3 secondary offset" %general_cfg_file% --vb >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
%AppliCfg% xmlval -b %flash_layout_bin% -b_el_idx 15 -nxml_el_idx "Flash Layout configuration index" -n "S Module 3 size" %general_cfg_file% --vb >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
%AppliCfg% xmlval -b %flash_layout_bin% -b_el_idx 16 -nxml_el_idx "Flash Layout configuration index" -n "S Module 4 primary offset" %general_cfg_file% --vb >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
%AppliCfg% xmlval -b %flash_layout_bin% -b_el_idx 17 -nxml_el_idx "Flash Layout configuration index" -n "S Module 4 secondary offset" %general_cfg_file% --vb >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
%AppliCfg% xmlval -b %flash_layout_bin% -b_el_idx 18 -nxml_el_idx "Flash Layout configuration index" -n "S Module 4 size" %general_cfg_file% --vb >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
%AppliCfg% xmlval -b %flash_layout_bin% -b_el_idx 19 -nxml_el_idx "Flash Layout configuration index" -n "S Module 5 primary offset" %general_cfg_file% --vb >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
%AppliCfg% xmlval -b %flash_layout_bin% -b_el_idx 20 -nxml_el_idx "Flash Layout configuration index" -n "S Module 5 secondary offset" %general_cfg_file% --vb >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
%AppliCfg% xmlval -b %flash_layout_bin% -b_el_idx 21 -nxml_el_idx "Flash Layout configuration index" -n "S Module 5 size" %general_cfg_file% --vb >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
%AppliCfg% xmlval -b %flash_layout_bin% -b_el_idx 22 -nxml_el_idx "Flash Layout configuration index" -n "S Module 6 primary offset" %general_cfg_file% --vb >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
%AppliCfg% xmlval -b %flash_layout_bin% -b_el_idx 23 -nxml_el_idx "Flash Layout configuration index" -n "S Module 6 secondary offset" %general_cfg_file% --vb >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
%AppliCfg% xmlval -b %flash_layout_bin% -b_el_idx 24 -nxml_el_idx "Flash Layout configuration index" -n "S Module 6 size" %general_cfg_file% --vb >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
%AppliCfg% xmlval -b %flash_layout_bin% -b_el_idx 25 -nxml_el_idx "Flash Layout configuration index" -n "S Module 7 primary offset" %general_cfg_file% --vb >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
%AppliCfg% xmlval -b %flash_layout_bin% -b_el_idx 26 -nxml_el_idx "Flash Layout configuration index" -n "S Module 7 secondary offset" %general_cfg_file% --vb >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
%AppliCfg% xmlval -b %flash_layout_bin% -b_el_idx 27 -nxml_el_idx "Flash Layout configuration index" -n "S Module 7 size" %general_cfg_file% --vb >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
%AppliCfg% xmlval -b %flash_layout_bin% -b_el_idx 28 -nxml_el_idx "Flash Layout configuration index" -n "NS appli primary offset" %general_cfg_file% --vb >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
%AppliCfg% xmlval -b %flash_layout_bin% -b_el_idx 29 -nxml_el_idx "Flash Layout configuration index" -n "NS appli secondary offset" %general_cfg_file% --vb >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
%AppliCfg% xmlval -b %flash_layout_bin% -b_el_idx 30 -nxml_el_idx "Flash Layout configuration index" -n "NS appli size" -nxml "NS reserved area size" -e "val1-(val2/2)" -cond "val2>0 and (val2 %% 2) == 0" %general_cfg_file% --vb >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
%AppliCfg% xmlval -b %flash_layout_bin% -b_el_idx 31 -nxml_el_idx "Flash Layout configuration index" -n "NS reserved area offset" -nxml "NS appli primary offset" -nxml "NS appli size" -e "val2 + val3" %general_cfg_file% --vb >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
%AppliCfg% xmlval -b %flash_layout_bin% -b_el_idx 33 -nxml_el_idx "Flash Layout configuration index" -n "ITS Factory offset" %general_cfg_file% --vb >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
%AppliCfg% xmlval -b %flash_layout_bin% -b_el_idx 34 -nxml_el_idx "Flash Layout configuration index" -n "ITS Factory size" %general_cfg_file% --vb >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
%AppliCfg% xmlval -b %flash_layout_bin% -b_el_idx 35 -nxml_el_idx "Flash Layout configuration index" -n "ITS offset" %general_cfg_file% --vb >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
%AppliCfg% xmlval -b %flash_layout_bin% -b_el_idx 36 -nxml_el_idx "Flash Layout configuration index" -n "ITS size" %general_cfg_file% --vb >> %current_log_file%
if !errorlevel! neq 0 goto :error_config

:: TPC xml sections to configure
set fw_size="Firmware area Size"
set rom_fixed="Rom fixed"
set fw_dwl_offset="Firmware download area offset"
set fw_out_bin="Image output file"

:: Get nb of modules
set tmp_file=%projectdir%ST\modules.bat
echo set nb_modules= > %tmp_file%
%AppliCfg% flash -xml %general_cfg_file% -n "Nb Secure Modules" -b nb_modules --decimal %tmp_file% --vb >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
call %tmp_file%

:: Variable containing list of modules to put in SFI file
set modules=

:: Generate dummy modules
set dummy_bin=%projectdir%Binary\dummy.bin
if not exist %dummy_bin% (
fsutil file createnew %dummy_bin% 1 >> %current_log_file%
)

for /L %%A in (1,1,%nb_modules%) do (
set /a id=%%A-1
set module_xml="%projectdir%Images\SM_Module_!id!_Image.xml"
set code_offset="S Module !id! primary offset"
set code_dwl_offset="S Module !id! secondary offset"
set code_size="S Module !id! size"
set image_hex1="Binary/Module_!id!.hex"
set image_hex2=Binary\Module_!id!.hex
copy %module_template_xml% !module_xml! >> %current_log_file%
%AppliCfg% xmlval -xml %general_cfg_file% -nxml !code_size! -n %fw_size% -e "val1*0x2000" !module_xml! --vb >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
%AppliCfg% xmlval -xml %general_cfg_file% -nxml !code_offset! -n %rom_fixed% -e "(val1*0x2000)+0xC000000" !module_xml! --vb >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
%AppliCfg% xmlval -xml %general_cfg_file% -nxml !code_dwl_offset! -n %fw_dwl_offset% -e "(val1*0x2000)+0x8000000" !module_xml! --vb >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
%AppliCfg% xmlval -v ../!image_hex1! --string -n %fw_out_bin% !module_xml! --vb >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
%stm32tpccli% -pb !module_xml! >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
set modules=!modules! --firmware "%projectdir%!image_hex2!"
)

:: Generate ITS factory (empty)
set its_xml="%projectdir%Images\SM_ITS.xml"
set its_factory_offset="ITS offset"
set its_factory_dwl_offset="ITS Factory offset"
set its_factory_size="ITS Factory size"
set its_factory=--firmware "%projectdir%Binary\ITS_Factory.hex"
%AppliCfg% xmlval -xml %general_cfg_file% -nxml %its_factory_size% -n %fw_size% -e "val1*0x2000" %its_xml% --vb >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
%AppliCfg% xmlval -xml %general_cfg_file% -nxml %its_factory_offset% -n %rom_fixed% -e "(val1*0x2000)+0xC000000" %its_xml% --vb >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
%AppliCfg% xmlval -xml %general_cfg_file% -nxml %its_factory_dwl_offset% -n %fw_dwl_offset% -e "(val1*0x2000)+0x8000000" %its_xml% --vb >> %current_log_file%
if !errorlevel! neq 0 goto :error_config
%stm32tpccli% -pb %its_xml% >> %current_log_file%
if !errorlevel! neq 0 goto :error_config

:: Generate SFI file
set device=--deviceid 0x484
set key=--key "%projectdir%Keys\SFI_Encryption_Key.bin"
set nonce=--nonce "%projectdir%Keys\SFI_Encryption_Nonce.bin"
set ob=--obfile "%projectdir%Config\Option_Bytes.csv"
set obk=--ob-keys "%projectdir%..\DA\Binary\DA_Config.obk" "%projectdir%Binary\SM_Config_Keys.obk" "%projectdir%Binary\SM_Config_General.obk"
set ssfi=-ssfi "%ssfi_binary_path%"
set ver=--ver 0
set ramsize=--ramsize 0x19000
set hash=--hash 1
set out=--outfile "%projectdir%Binary\SecureManagerPackage.sfi"
::%stm32tpccli% -sfi %device% %modules% %its_factory% %key% %nonce% %ob% %obk% %ssfi% %ver% %ramsize% %hash% %out% >> %current_log_file%
%stm32tpccli% -sfi %device% %modules% %key% %nonce% %ob% %obk% %ssfi% %ver% %ramsize% %hash% %out% >> %current_log_file%
if !errorlevel! neq 0 goto :error_config

echo        Successful SFI file generation

:installation
:: ================================================ Secure installation RSSe SFI =================================================
echo;
echo Step 2 : Installation
echo;
echo    * BOOT0 pin should be disconnected from VDD
echo        (STM32H573I-DK: set SW1 to position 0)
echo        Press any key to continue...
echo.
if [%1] neq [AUTO] pause >nul

echo    * Secure installation
%stm32programmercli% %connect_ur% -hardRst >> %current_log_file%
%stm32programmercli% %connect_ur% -hardRst >> %current_log_file%
echo        Installation starting (might take up to 10 seconds)...
%stm32programmercli% %connect% -sfi %sfi_binary_path% %license% -rsse %rsse_binary_path% >> %current_log_file%
IF !errorlevel! NEQ 0 goto :error_install

:: Wait end of installation ...
echo        Installation completion...
timeout 3 /NOBREAK >nul
echo        Successful installation
echo.

:: ============================================================= End functions ===================================================
:: All the steps were executed correctly
echo =====
echo ===== The board is correctly configured with ST Secure Manager Package
echo =====
if [%2] neq [AUTO] cmd /k
exit 0

:: Error when script is executed
:error_install
%stm32programmercli% %connect% -hardRst >> %current_log_file%
:error_config
echo.
echo =====
echo ===== Error occurred.
echo ===== See %current_log_file% for details. Then try again.
echo =====
if [%2] neq [AUTO] cmd /k
exit 1
