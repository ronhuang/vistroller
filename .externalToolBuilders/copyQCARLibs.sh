#!/bin/bash

if [ ! -d libs ]; then
mkdir libs
fi

cd libs

if [ ! -d ./armeabi ]; then
mkdir armeabi
fi

if [ ! -d ./armeabi-v7a ]; then
mkdir armeabi-v7a
fi

cd ..
cp ../../build/lib/armeabi/libQCAR.so libs/armeabi/
cp ../../build/lib/armeabi-v7a/libQCAR.so libs/armeabi-v7a/

if [ ! -e libs/armeabi/libQCAR.so ] || [ ! -e libs/armeabi-v7a/libQCAR.so ]; then
echo ========================================================================
echo ERROR: libQCAR.so could not be copied. Check your QCAR-SDK installation.
echo ========================================================================
else
echo =====================================================================
echo SUCCESS: libQCAR.so copied into lib directory.
echo =====================================================================
fi
