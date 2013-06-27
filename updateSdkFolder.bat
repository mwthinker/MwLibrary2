@echo off
:: Copies the latest MwLibrary2 to SDK folder.

set destFolder="..\SDK\MwLibrary2"

del %destFolder%\include\mw\ /Q
del %destFolder%\source\ /Q

del %destFolder%\lib-r\ /Q
del %destFolder%\lib-d\ /Q

xcopy mw\*.h %destFolder%\include\mw\
xcopy mw\*.cpp %destFolder%\source\

xcopy Release\*.pdb %destFolder%\lib-r\
xcopy Release\MwLibrary2.lib %destFolder%\lib-r\

xcopy Debug\*.pdb %destFolder%\lib-d\
xcopy Debug\*.idb %destFolder%\lib-d\
xcopy Debug\MwLibrary2.lib %destFolder%\lib-d\
