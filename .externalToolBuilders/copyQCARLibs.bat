@ECHO OFF
IF NOT EXIST ./libs mkdir libs
cd libs
IF NOT EXIST ./armeabi mkdir armeabi
IF NOT EXIST ./armeabi-v7a mkdir armeabi-v7a
cd ..
copy ..\..\build\lib\armeabi\libQCAR.so libs\armeabi\ > NUL
copy ..\..\build\lib\armeabi-v7a\libQCAR.so libs\armeabi-v7a\ > NUL

IF NOT EXIST libs\armeabi\libQCAR.so GOTO PRINTERROR
IF NOT EXIST libs\armeabi\libQCAR.so GOTO PRINTERROR

GOTO SUCCESS

:PRINTERROR
ECHO ========================================================================
ECHO ERROR: libQCAR.so could not be copied. Check your QCAR-SDK installation.
ECHO ========================================================================
GOTO END

:SUCCESS
ECHO =====================================================================
ECHO SUCCESS: libQCAR.so copied into lib directory.
ECHO =====================================================================

:END
