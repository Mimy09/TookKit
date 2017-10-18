@echo off
title FMM.bat
mode con cols=80 lines=45
color 1f
setlocal enableextensions enableDelayedExpansion

set GLOBAL_FILE1=
set GLOBAL_FILE2=

:MAIN
	cls
	echo.
	echo. "##############################"
	echo. "##  _________  ______  ___  ##"
	echo. "##  |  ___|  \/  ||  \/  |  ##"
	echo. "##  | |_  | .  . || .  . |  ##"
	echo. "##  |  _| | |\/| || |\/| |  ##"
	echo. "##  | |   | |  | || |  | |  ##"
	echo. "##  \_|   \_|  |_/\_|  |_/  ##"
	echo. "##                          ##"
	echo. "##############################"
	echo. 
	echo. Made by: Francisco R  Mitchell J
	echo.
	echo.
	set /p GLOBAL_FILE1=":: Open File = "
	echo.
	set /p GLOBAL_FILE2=":: Save File = "
	echo.
	echo.--------------------------------------------------------------------------------
	echo.
	call :WRITEFILE %GLOBAL_FILE1% %GLOBAL_FILE2%
	echo.
	echo.--------------------------------------------------------------------------------
	echo.
	echo.- Data will be saved in "%GLOBAL_FILE2%"
	echo.
	echo.--------------------------------------------------------------------------------
	echo.
	pause
	goto:eof

:WRITEFILE
	setlocal enableDelayedExpansion
	echo - Reading file :: %~1
	for /f "tokens=*" %%A in (%~1) do (
		for /f "tokens=1*" %%B in ("%%A") do (
			if "%%B" == "#include" (
				for /f "tokens=2*" %%C in ("%%A") do (
					SET START=%%C
					SET START=!START:~0,1!
 					if "!START!" NEQ "<" (						
						set "CURPATH=%~1"
						for %%a in ("%~1") do set "CURFILE=%%~nxa"
						
						call :strrchr RESULT CURPATH CURFILE
						
						set NEWPATH=%%C
						set NEWPATH=!NEWPATH:~1,-1!
						
						set "RESULT=!RESULT!!NEWPATH!"
						
						CALL :WRITEFILE !RESULT! %~2

					) else ( echo %%A>>%~2 )
				)
			) else ( echo %%A>>%~2 )
		)
	)
	endlocal
	exit /b 0

:strrchr <result> <string> <sub>
(
	set "str=!%~2! /"
	set "substr=!%~3!"
	
	call set str=%%str:!substr! =%%
	
)
(
	endlocal & set "%~1=!str:~0,-1!"
	exit /b
)