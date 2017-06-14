@echo Off

SET toolKit_include="StaticLibrary\ToolKit\*.h"
SET toolKit_lib="StaticLibrary\Debug\*.lib"
SET toolKit_include_dest="Library\ToolKit\Include"
SET toolKit_lib_dest="Library\ToolKit\Libs"

:main
xcopy %toolKit_lib% %toolKit_lib_dest%
xcopy %toolKit_include% %toolKit_include_dest%
pause >nul