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
#include <QCAR/Trackable.h>


// Utility for logging:
#define LOG(...)  __android_log_print(ANDROID_LOG_DEBUG, "Vistroller", __VA_ARGS__)


#ifdef __cplusplus
extern "C"
{
#endif


JNIEXPORT void JNICALL
Java_org_ronhuang_vistroller_Vistroller_startTracking(JNIEnv *, jobject)
{
    LOG("Java_org_ronhuang_vistroller_Vistroller_startTracking");

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
Java_org_ronhuang_vistroller_Vistroller_stopTracking(JNIEnv *, jobject)
{
    LOG("Java_org_ronhuang_vistroller_Vistroller_stopTracking");

    QCAR::Tracker::getInstance().stop();

    QCAR::CameraDevice::getInstance().stop();
    QCAR::CameraDevice::getInstance().deinit();
}


jobject
newTrackable(JNIEnv *env, const short id, const float *data)
{
    static jclass cls = NULL;
    static jmethodID cid = NULL;
    jobject result = NULL;
    jfloatArray pose = NULL;

    // Cache cls
    if (NULL == cls) {
        jclass lcls = env->FindClass("org/ronhuang/vistroller/Trackable");
        if (NULL == lcls)
            return NULL;
        cls = static_cast<jclass>(env->NewGlobalRef(static_cast<jobject>(lcls)));
        env->DeleteLocalRef(lcls);
        if (NULL == cls)
            return NULL;
    }

    // Cache cid
    if (NULL == cid) {
        cid = env->GetMethodID(cls, "<init>", "(S[F)V");
        if (NULL == cid)
            return NULL;
    }

    // Create pose
    pose = env->NewFloatArray(3 * 4);
    if (NULL == pose)
        return NULL;
    env->SetFloatArrayRegion(pose, 0, 3 * 4, data);

    // Invoke constructor.
    result = env->NewObject(cls, cid, id, pose);

    // Free local reference.
    env->DeleteLocalRef(pose);

    return result;
}


JNIEXPORT jobject JNICALL
Java_org_ronhuang_vistroller_Vistroller_getTrackable(JNIEnv *env, jobject)
{
    LOG("Java_org_ronhuang_vistroller_Vistroller_getTrackable");

    const QCAR::Tracker &tracker = QCAR::Tracker::getInstance();
    const int count = tracker.getNumActiveTrackables();
    const QCAR::Trackable *trackable = NULL;
    jobject result = NULL;

    for (int i = 0; i < count; i++) {
        trackable = tracker.getActiveTrackable(i);
        if (QCAR::Trackable::TRACKED != trackable->getStatus())
            continue;

        result = newTrackable(env, trackable->getId(), trackable->getPose().data);
        break; // FIXME: return only the first one for now.
    }

    if (NULL == result) {
        // Make sure always return an instance of Trackable.
        // Return invalid one.
        float data[3 * 4] = {
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0
        };
        result = newTrackable(env, -1, data);
    }

    return result;
}


#ifdef __cplusplus
}
#endif
