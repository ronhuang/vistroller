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

import android.app.Activity;
import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.os.Handler;
import android.util.DisplayMetrics;
import android.view.View;
import android.view.WindowManager;
import android.view.ViewGroup.LayoutParams;
import android.widget.ImageView;
import android.util.Log;
import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;


/** The main activity for the VistrollerSample. */
public class VistrollerSample extends Activity implements VistrollerListener
{
    // Vistroller instance
    private Vistroller mVistroller;

    // Our OpenGL view:
    private GLSurfaceView mGlView;

    // The view to display the sample splash screen:
    private ImageView mSplashScreenView;

    // The minimum time the splash screen should be visible:
    private static final long MIN_SPLASH_SCREEN_TIME = 2000;

    // The time when the splash screen has become visible:
    private long mSplashScreenStartTime = 0;

    // Our renderer:
    private FrameMarkersRenderer mRenderer;

    // Force orientation.
    private int mScreenOrientation = ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE;

    // Log tag
    private static final String TAG = "VistrollerSample";


    /** Called when the activity first starts or the user navigates back
     * to an activity. */
    protected void onCreate(Bundle savedInstanceState)
    {
        Log.d(TAG, "VistrollerSample::onCreate");
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

        // Apply screen orientation
        setRequestedOrientation(mScreenOrientation);

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

        // Initialize Vistroller instance.
        mVistroller.onCreate();
    }


   /** Called when the activity will start interacting with the user.*/
    protected void onResume()
    {
        Log.d(TAG, "VistrollerSample::onResume");
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
        Log.d(TAG, "VistrollerSample::onPause");
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
        Log.d(TAG, "VistrollerSample::onDestroy");
        super.onDestroy();

        mVistroller.onDestroy();
    }


    /** Listen to Vistroller events. */
    public void onVistrollerStateChanged(Vistroller.State state)
    {
        Log.d(TAG, "VistrollerSample::onVistrollerStateChanged: " + state);

        switch (state) {
        case ENGINE_INITIALIZED:
            // Create renderer.
            mRenderer = new FrameMarkersRenderer();
            mRenderer.setActivityPortraitMode(mScreenOrientation == ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
            DisplayMetrics metrics = new DisplayMetrics();
            getWindowManager().getDefaultDisplay().getMetrics(metrics);
            mRenderer.setScreenSize(metrics.widthPixels, metrics.heightPixels);

            // Create OpenGL ES view:
            mGlView = new GLSurfaceView(this);
            mGlView.getHolder().setFormat(PixelFormat.TRANSLUCENT);
            mGlView.setEGLContextClientVersion(2);
            mGlView.setEGLConfigChooser(8, 8, 8, 8, 16, 0);
            mGlView.setRenderer(mRenderer);
            break;

        case TRACKER_INITIALIZED:
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

                    // Now add the GL surface view. It is important
                    // that the OpenGL ES surface view gets added
                    // BEFORE the camera is started and video
                    // background is configured.
                    addContentView(mGlView, new LayoutParams(LayoutParams.FILL_PARENT, LayoutParams.FILL_PARENT));

                    // Start the camera:
                    mVistroller.requestStartCamera();

                    // Activate the renderer
                    mRenderer.configureProjectMatrix();
                    mRenderer.configureVideoBackground();
                    mRenderer.mIsActive = true;
                }
            }, newSplashScreenTime);
            break;

        case SYSTEM_INITIALIZED:
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
