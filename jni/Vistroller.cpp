/*
 * Copyright (C) 2011 Ron Huang
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */


#include <jni.h>
#include <android/log.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <QCAR/QCAR.h>
#include <QCAR/CameraDevice.h>
#include <QCAR/Tracker.h>


// Utility for logging:
#define LOG(...)  __android_log_print(ANDROID_LOG_DEBUG, "Vistroller", __VA_ARGS__)


#ifdef __cplusplus
extern "C"
{
#endif


JNIEXPORT void JNICALL
Java_org_ronhuang_vistroller_Vistroller_startCamera(JNIEnv *, jobject)
{
    LOG("Java_org_ronhuang_vistroller_Vistroller_startCamera");

    // Initialize the camera:
    if (!QCAR::CameraDevice::getInstance().init())
        return;

    // Select the default mode:
    if (!QCAR::CameraDevice::getInstance().selectVideoMode(
                                QCAR::CameraDevice::MODE_DEFAULT))
        return;

    // Start the camera:
    if (!QCAR::CameraDevice::getInstance().start())
        return;

    // Start the tracker:
    QCAR::Tracker::getInstance().start();
}


JNIEXPORT void JNICALL
Java_org_ronhuang_vistroller_Vistroller_stopCamera(JNIEnv *, jobject)
{
    LOG("Java_org_ronhuang_vistroller_Vistroller_stopCamera");

    QCAR::Tracker::getInstance().stop();

    QCAR::CameraDevice::getInstance().stop();
    QCAR::CameraDevice::getInstance().deinit();
}


#ifdef __cplusplus
}
#endif
