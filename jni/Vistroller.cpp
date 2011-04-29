/*==============================================================================
            Copyright (c) 2010 QUALCOMM Incorporated.
            All Rights Reserved.
            Qualcomm Confidential and Proprietary

@file
    Vistroller.cpp

@brief
    Native interfaces for Vistroller

==============================================================================*/


#include <jni.h>
#include <android/log.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <GLES/gl.h>
#include <GLES/glext.h>

#include <QCAR/QCAR.h>
#include <QCAR/CameraDevice.h>
#include <QCAR/Renderer.h>
#include <QCAR/VideoBackgroundConfig.h>
#include <QCAR/Trackable.h>
#include <QCAR/Tool.h>
#include <QCAR/Tracker.h>
#include <QCAR/CameraCalibration.h>
#include <QCAR/Marker.h>

#include "SampleUtils.h"
#include "Cube.h"

#ifdef __cplusplus
extern "C"
{
#endif

// Screen dimensions:
unsigned int screenWidth        = 0;
unsigned int screenHeight       = 0;

// Indicates whether screen is in portrait (true) or landscape (false) mode
bool isActivityInPortraitMode   = false;

// The projection matrix used for rendering virtual objects:
QCAR::Matrix44F projectionMatrix;

// Constants:
static const float kLetterScale        = 25.0f;
static const float kLetterTranslate    = 25.0f;


JNIEXPORT void JNICALL
Java_org_ronhuang_vistroller_Vistroller_setActivityPortraitMode(JNIEnv *, jobject, jboolean isPortrait)
{
    isActivityInPortraitMode = isPortrait;
}


JNIEXPORT void JNICALL
Java_org_ronhuang_vistroller_FrameMarkersRenderer_renderFrame(JNIEnv *, jobject)
{
    //LOG("Java_org_ronhuang_vistroller_FrameMarkersRenderer_renderFrame");

    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render video background:
    QCAR::State state = QCAR::Renderer::getInstance().begin();

    // Did we find any trackables this frame?
    for(int tIdx = 0; tIdx < state.getNumActiveTrackables(); tIdx++)
    {
        // Get the trackable:
        const QCAR::Trackable* trackable = state.getActiveTrackable(tIdx);
        QCAR::Matrix44F modelViewMatrix =
            QCAR::Tool::convertPose2GLMatrix(trackable->getPose());

        // Check the type of the trackable:
        assert(trackable->getType() == QCAR::Trackable::MARKER);
        const QCAR::Marker* marker = static_cast<const QCAR::Marker*>(trackable);

        //textureIndex = marker->getMarkerId();

        // Select which model to draw:
        const GLvoid* vertices = &CubeVertices[0];
        const GLvoid* indices = &CubeIndices[0];
        const GLvoid* colors = &CubeColors[0];
        int numIndices = NUM_CUBE_INDEX;

#if 0
        QCAR::Matrix44F modelViewProjection;

        SampleUtils::translatePoseMatrix(-kLetterTranslate,
                                         -kLetterTranslate,
                                         0.f,
                                         &modelViewMatrix.data[0]);
        SampleUtils::scalePoseMatrix(kLetterScale, kLetterScale, kLetterScale,
                                     &modelViewMatrix.data[0]);
        SampleUtils::multiplyMatrix(&projectionMatrix.data[0],
                                    &modelViewMatrix.data[0],
                                    &modelViewProjection.data[0]);

        glLoadMatrixf(&modelViewProjection.data[0]);
#endif
        glVertexPointer(3, GL_FLOAT, 0, vertices);
        glColorPointer(4, GL_FLOAT, 0, colors);
        glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, indices);

        SampleUtils::checkGlError("Vistroller render frame");
    }

    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

    QCAR::Renderer::getInstance().end();
}


void
configureVideoBackground()
{
    // Get the default video mode:
    QCAR::CameraDevice& cameraDevice = QCAR::CameraDevice::getInstance();
    QCAR::VideoMode videoMode = cameraDevice.
                                getVideoMode(QCAR::CameraDevice::MODE_DEFAULT);

    // Configure the video background
    QCAR::VideoBackgroundConfig config;
    config.mEnabled = true;
    config.mSynchronous = true;
    config.mPosition.data[0] = 0.0f;
    config.mPosition.data[1] = 0.0f;

    if (isActivityInPortraitMode)
    {
        //LOG("configureVideoBackground PORTRAIT");
        config.mSize.data[0] = videoMode.mHeight
                                * (screenHeight / (float)videoMode.mWidth);
        config.mSize.data[1] = screenHeight;
    }
    else
    {
        //LOG("configureVideoBackground LANDSCAPE");
        config.mSize.data[0] = screenWidth;
        config.mSize.data[1] = videoMode.mHeight
                            * (screenWidth / (float)videoMode.mWidth);
    }

    // Set the config:
    QCAR::Renderer::getInstance().setVideoBackgroundConfig(config);
}


JNIEXPORT void JNICALL
Java_org_ronhuang_vistroller_Vistroller_initApplicationNative(JNIEnv* env, jobject obj, jint width, jint height)
{
    LOG("Java_org_ronhuang_vistroller_Vistroller_initApplicationNative");

    // Store screen dimensions
    screenWidth = width;
    screenHeight = height;
}


JNIEXPORT void JNICALL
Java_org_ronhuang_vistroller_Vistroller_deinitApplicationNative(JNIEnv* env, jobject obj)
{
    LOG("Java_org_ronhuang_vistroller_Vistroller_deinitApplicationNative");
}


JNIEXPORT void JNICALL
Java_org_ronhuang_vistroller_Vistroller_startCamera(JNIEnv *, jobject)
{
    LOG("Java_org_ronhuang_vistroller_Vistroller_startCamera");

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
    QCAR::Tracker::getInstance().start();

    // Cache the projection matrix:
    const QCAR::Tracker& tracker = QCAR::Tracker::getInstance();
    const QCAR::CameraCalibration& cameraCalibration =
                                    tracker.getCameraCalibration();
    projectionMatrix = QCAR::Tool::getProjectionGL(cameraCalibration, 2.0f,
                                            2000.0f);
}


JNIEXPORT void JNICALL
Java_org_ronhuang_vistroller_Vistroller_stopCamera(JNIEnv *, jobject)
{
    LOG("Java_org_ronhuang_vistroller_Vistroller_stopCamera");

    QCAR::Tracker::getInstance().stop();

    QCAR::CameraDevice::getInstance().stop();
    QCAR::CameraDevice::getInstance().deinit();
}


JNIEXPORT void JNICALL
Java_org_ronhuang_vistroller_FrameMarkersRenderer_initRendering(
                                                    JNIEnv* env, jobject obj)
{
    LOG("Java_org_ronhuang_vistroller_FrameMarkersRenderer_initRendering");

    // Define clear color
    glClearColor(0.0f, 0.0f, 0.0f, QCAR::requiresAlpha() ? 0.0f : 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
}


JNIEXPORT void JNICALL
Java_org_ronhuang_vistroller_FrameMarkersRenderer_updateRendering(
                        JNIEnv* env, jobject obj, jint width, jint height)
{
    LOG("Java_org_ronhuang_vistroller_FrameMarkersRenderer_updateRendering");

    // Update screen dimensions
    screenWidth = width;
    screenHeight = height;

    // Reconfigure the video background
    configureVideoBackground();
}


#ifdef __cplusplus
}
#endif
