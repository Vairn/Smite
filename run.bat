:: --- Blitz Basic 2.1 build batch script ---
:: ---   by MickGyver (Mikael Norrgard)   ---

:: Leave the following two lines as is
@echo off
setlocal EnableDelayedExpansion

:: -----------------------------------------------------------------------------
:: -- CONFIGURE THE FOLLOWING VARIABLES ----------------------------------------
:: -----------------------------------------------------------------------------

:: Set the project path as seen by WorkBench in the emulated Amiga instance.
:: (This is a Windows folder set up as a virtual hdd in WinUAE.)
:: The project path must end with a forward slash (/).
set project_path_on_amiga=BLITZPROJECTS:/smite/

:: Add all project files, first file must be the main file of the project.
:: All project filenames must end with "_asc" and have the extension ".bb2".
set project_files[0]=smite.bb2
set project_files[1]=types.bb2
set project_files[2]=FileAccess.bb2
set project_files[3]=Map.bb2
set project_files[4]=Monster.bb2
set project_files[5]=Graphics.bb2
set project_files[6]=Menu.bb2
set project_files[7]=Title.bb2
set project_files[8]=debug.bb2

:: Set the WinUAE folder.
:: WinUAE folder must end with a backslash (\)
set winuae_folder=C:\Program Files\WinUAE\

:: Set the WinUAE executable name (winuae64.exe for 64bit, winuae.exe for 32bit)
set winuae_exe=winuae64.exe
 
:: Set the config file to use in WinUAE
set winuae_config="C:\Users\Public\Documents\Amiga Files\WinUAE\Configurations\default.uae"
::C:\Users\[user]\Documents\WinUAE\Configurations\ClassicWB.uae

:: Set time (seconds) to wait for WorkBench to start before starting BB2
:: (Used when WinUAE isn't already running.)
set /a wb_delay=20

:: -----------------------------------------------------------------------------
:: -- END OF VARIABLES ---------------------------------------------------------
:: -----------------------------------------------------------------------------

:: ------------------------------------------------------------------ -----------
:: YOU SHOULDN'T NEED TO EDIT ANYTHING BELOW THIS LINE
:: -------------------------- ---------------------------------------------------

:main

:: WinUAE 64-bit: winuae64.exe, WinUAE 32-bit: winuae.exe
tasklist /FI "IMAGENAME eq %winuae_exe%" 2>NUL | find /I /N "%winuae_exe%">NUL

:: If WinUAE is not running, then run it!
::if %ERRORLEVEL%==1 goto winuaenotrunning

:: Get the number of source files in project
echo -----------------------------------
set /a x=0
:arrayLength
if defined project_files[%x%] (
   call echo %%project_files[%x%]%%
   set /a x+=1
   GOTO :arrayLength
)

:: Reduce project file count by one for loops
set /a count=%x%-1

:: Run ConvertEOL for every *.bb2 file in the project
for /l %%n in (0,1,%count%) do (
  ConvertEOL unix !project_files[%%n]! Build/!project_files[%%n]!
)

:: Build the arguments for the WinUAEArexx command
set filelist=!project_path_on_amiga!Build/!project_files[0]!
for /l %%n in (1,1,%count%) do (
  set filelist=!filelist! !project_path_on_amiga!Build/!project_files[%%n]!
)

:: Arexx was too unstable for me so I just did it the old fashion way
echo rx blitzbasic2 !filelist!>>cmd.txt
COPY .vscode\User-Startup+cmd.txt dh0\s\User-Startup
del cmd.txt

:: Run the ARexx script
::WinUAEArexx blitzbasic2 1000 !filelist!
start "" "%winuae_folder%%winuae_exe%" -f %winuae_config% -s use_gui=no
:: Bring WinUAE to front
BringToFront "WinUAE"

exit
