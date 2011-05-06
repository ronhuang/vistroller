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
#include <QCAR/VideoBackgroundConfig.h>
#include <QCAR/Renderer.h>
#include <QCAR/Marker.h>


// Utility for logging:
#define LOG(...)  __android_log_print(ANDROID_LOG_DEBUG, "Vistroller", __VA_ARGS__)


#ifdef __cplusplus
extern "C"
{
#endif


jobject
newMarker(JNIEnv *env, const short id, const float *pose_data, const float *size_data)
{
    static jclass cls = NULL;
    static jmethodID cid = NULL;
    jobject result = NULL;
    jfloatArray pose = NULL;
    jfloatArray size = NULL;

    // Cache cls
    if (NULL == cls) {
        jclass lcls = env->FindClass("org/ronhuang/vistroller/Marker");
        if (NULL == lcls) {
            LOG("org/ronhuang/vistroller/Marker not found");
            return NULL;
        }
        cls = static_cast<jclass>(env->NewGlobalRef(static_cast<jobject>(lcls)));
        env->DeleteLocalRef(lcls);
        if (NULL == cls) {
            LOG("cls not global referenced");
            return NULL;
        }
    }

    // Cache cid
    if (NULL == cid) {
        cid = env->GetMethodID(cls, "<init>", "(S[F[F)V");
        if (NULL == cid) {
            LOG("Constructor not found");
            return NULL;
        }
    }

    // Create pose
    pose = env->NewFloatArray(3 * 4);
    if (NULL == pose) {
        LOG("pose not created");
        return NULL;
    }
    env->SetFloatArrayRegion(pose, 0, 3 * 4, pose_data);

    // Create size
    size = env->NewFloatArray(2);
    if (NULL == size) {
        LOG("size not created");
        return NULL;
    }
    env->SetFloatArrayRegion(size, 0, 2, size_data);

    // Invoke constructor.
    result = env->NewObject(cls, cid, id, pose, size);

    // Free local reference.
    env->DeleteLocalRef(pose);
    env->DeleteLocalRef(size);

    return result;
}


void
configureVideoBackground()
{
    // Get the default video mode:
    QCAR::CameraDevice& cameraDevice = QCAR::CameraDevice::getInstance();
    QCAR::VideoMode videoMode = cameraDevice.getVideoMode(QCAR::CameraDevice::MODE_DEFAULT);

    // Configure the video background
    QCAR::VideoBackgroundConfig config;
    config.mEnabled = false;
    config.mSynchronous = false;
    config.mPosition.data[0] = 0.0f;
    config.mPosition.data[1] = 0.0f;
    config.mSize.data[0] = videoMode.mWidth;
    config.mSize.data[1] = videoMode.mHeight;

    // Set the config:
    QCAR::Renderer::getInstance().setVideoBackgroundConfig(config);
}


JNIEXPORT void JNICALL
Java_org_ronhuang_vistroller_Vistroller_startTracking(JNIEnv *, jobject)
{
    LOG("Java_org_ronhuang_vistroller_Vistroller_startTracking");

    // Initialize the camera:
    if (!QCAR::CameraDevice::getInstance().init())
        return;

    // Configure the video background
    configureVideoBackground();

    // Select the default mode:
    if (!QCAR::CameraDevice::getInstance().selectVideoMode(
                                QCAR::CameraDevice::MODE_DEFAULT))
        return;

    // Start the camera:
    if (!QCAR::CameraDevice::getInstance().start())
        return;

    // Start the tracker:
    if (!QCAR::Tracker::getInstance().start())
        return;
}


JNIEXPORT void JNICALL
Java_org_ronhuang_vistroller_Vistroller_stopTracking(JNIEnv *, jobject)
{
    LOG("Java_org_ronhuang_vistroller_Vistroller_stopTracking");

    QCAR::Tracker::getInstance().stop();
    QCAR::CameraDevice::getInstance().stop();
    QCAR::CameraDevice::getInstance().deinit();
}


JNIEXPORT jobject JNICALL
Java_org_ronhuang_vistroller_Vistroller_getMarker(JNIEnv *env, jobject)
{
    //LOG("Java_org_ronhuang_vistroller_Vistroller_getMarker");

    jobject result = NULL;

    QCAR::State state = QCAR::Renderer::getInstance().begin();

    for (int i = 0; i < state.getNumActiveTrackables(); i++) {
        const QCAR::Trackable *trackable = state.getActiveTrackable(i);
        assert(trackable->getType() == QCAR::Trackable::MARKER);
        const QCAR::Marker *marker = static_cast<const QCAR::Marker*>(trackable);

        result = newMarker(env, marker->getMarkerId(), marker->getPose().data, marker->getSize().data);
        break; // FIXME: return only the first one for now.
    }

    if (NULL == result) {
        // Make sure always return an instance of Trackable.
        // Return invalid one.
        float pose[3 * 4] = {
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0
        };
        float size[2] = {0, 0};
        result = newMarker(env, -1, pose, size);
    }

    QCAR::Renderer::getInstance().end();

    return result;
}


#ifdef __cplusplus
}
#endif
