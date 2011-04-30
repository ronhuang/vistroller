/*==============================================================================
            Copyright (c) 2010 QUALCOMM Incorporated.
            All Rights Reserved.
            Qualcomm Confidential and Proprietary

@file
    VistrollerSample.java

@brief
    Visual Controller using frame markers

==============================================================================*/


package org.ronhuang.vistroller;

import java.util.Vector;

import android.app.Activity;
import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.os.Handler;
import android.util.DisplayMetrics;
import android.view.View;
import android.view.WindowManager;
import android.view.ViewGroup.LayoutParams;
import android.widget.ImageView;


/** The main activity for the VistrollerSample. */
public class VistrollerSample extends Activity implements VistrollerListener
{
    // Vistroller instance
    private Vistroller mVistroller;

    // Our OpenGL view:
    private QCARSampleGLView mGlView;

    // The view to display the sample splash screen:
    private ImageView mSplashScreenView;

    // The minimum time the splash screen should be visible:
    private static final long MIN_SPLASH_SCREEN_TIME = 2000;

    // The time when the splash screen has become visible:
    long mSplashScreenStartTime = 0;

    // Our renderer:
    private FrameMarkersRenderer mRenderer;


    /** Called when the activity first starts or the user navigates back
     * to an activity. */
    protected void onCreate(Bundle savedInstanceState)
    {
        DebugLog.LOGD("VistrollerSample::onCreate");
        super.onCreate(savedInstanceState);

        // Set the screen orientation
        //
        // NOTE: It is recommended to set this because of the following reasons:
        //
        //    1.) Before Android 2.2 there is no reliable way to query the
        //        absolute screen orientation from an activity, therefore using
        //        an undefined orientation is not recommended. Screen
        //        orientation matching orientation sensor measurements is also
        //        not recommended as every screen orientation change triggers
        //        deinitialization / (re)initialization steps in internal QCAR
        //        SDK components resulting in unnecessary overhead during
        //        application run-time.
        //
        //    2.) Android camera drivers seem to always deliver landscape images
        //        thus QCAR SDK components (e.g. camera capturing) need to know
        //        when we are in portrait mode. Before Android 2.2 there is no
        //        standard, device-independent way to let the camera driver know
        //        that we are in portrait mode as each device seems to require a
        //        different combination of settings to rotate camera preview
        //        frames images to match portrait mode views. Because of this,
        //        we suggest that the activity using the QCAR SDK be locked
        //        to landscape mode if you plan to support Android 2.1 devices
        //        as well. Froyo is fine with both orientations.
    	int screenOrientation = ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE;

    	// Apply screen orientation
    	setRequestedOrientation(screenOrientation);

        // As long as this window is visible to the user, keep the device's
        // screen turned on and bright.
        getWindow().setFlags(
            WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON,
            WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

        // Create and add the splash screen view
        mSplashScreenView = new ImageView(this);
        mSplashScreenView.setImageResource(R.drawable.splash_screen_frame_markers);
        addContentView(mSplashScreenView, new LayoutParams(
                        LayoutParams.FILL_PARENT, LayoutParams.FILL_PARENT));

        mSplashScreenStartTime = System.currentTimeMillis();


        // Create Vistroller instance.
        mVistroller = new Vistroller(this);
        mVistroller.addListener(this);

    	// Pass on screen orientation info to native code.
        mVistroller.setActivityPortraitMode(screenOrientation == ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);

        // Query display dimensions
        DisplayMetrics metrics = new DisplayMetrics();
        getWindowManager().getDefaultDisplay().getMetrics(metrics);
        mVistroller.setScreenSize(metrics.widthPixels, metrics.heightPixels);

        // Initialize Vistroller instance.
        mVistroller.onCreate();
    }


   /** Called when the activity will start interacting with the user.*/
    protected void onResume()
    {
        DebugLog.LOGD("VistrollerSample::onResume");
        super.onResume();

        mVistroller.onResume();

        // Resume the GL view:
        if (mGlView != null)
        {
            mGlView.setVisibility(View.VISIBLE);
            mGlView.onResume();
        }
    }


    /** Called when the system is about to start resuming a previous activity.*/
    protected void onPause()
    {
        DebugLog.LOGD("VistrollerSample::onPause");
        super.onPause();

        if (mGlView != null)
        {
            mGlView.setVisibility(View.INVISIBLE);
            mGlView.onPause();
        }

        mVistroller.onPause();
    }


    /** The final call you receive before your activity is destroyed.*/
    protected void onDestroy()
    {
        DebugLog.LOGD("VistrollerSample::onDestroy");
        super.onDestroy();

        mVistroller.onDestroy();
    }


    /** Listen to Vistroller events. */
    public void onVistrollerStateChanged(VistrollerState state)
    {
        DebugLog.LOGD("VistrollerSample::onVistrollerStateChanged: " + state);

        switch (state) {
        case VistrollerState.ENGINE_INITIALIZED:
            // Create OpenGL ES view:
            int depthSize = 16;
            int stencilSize = 0;
            boolean translucent = QCAR.requiresAlpha();

            mGlView = new QCARSampleGLView(this);
            mGlView.init(mVistroller.getFlags(), translucent, depthSize, stencilSize);

            mRenderer = new FrameMarkersRenderer();
            mGlView.setRenderer(mRenderer);
            break;

        case VistrollerState.TRACKER_INITIALIZED:
            // The elapsed time since the splash screen was visible:
            long splashScreenTime = System.currentTimeMillis() - mSplashScreenStartTime;
            long newSplashScreenTime = 0;
            if (splashScreenTime < MIN_SPLASH_SCREEN_TIME)
                newSplashScreenTime = MIN_SPLASH_SCREEN_TIME - splashScreenTime;

            // Request a callback function after a given timeout to dismiss
            // the splash screen:
            Handler handler = new Handler();
            handler.postDelayed(new Runnable() {
                public void run() {
                    // Hide the splash screen
                    mSplashScreenView.setVisibility(View.INVISIBLE);

                    // Activate the renderer
                    mRenderer.mIsActive = true;

                    // Now add the GL surface view. It is important
                    // that the OpenGL ES surface view gets added
                    // BEFORE the camera is started and video
                    // background is configured.
                    addContentView(mGlView, new LayoutParams(LayoutParams.FILL_PARENT, LayoutParams.FILL_PARENT));

                    // Start the camera:
                    mVistroller.requestStartCamera();
                }
            }, newSplashScreenTime);
            break;

        case VistrollerState.SYSTEM_INITIALIZED:
            // Hint to the virtual machine that it would be a good time to
            // run the garbage collector.
            //
            // NOTE: This is only a hint. There is no guarantee that the
            // garbage collector will actually be run.
            System.gc();
            break;

        default:
            break;
        }
    }
}
