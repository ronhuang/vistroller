/*==============================================================================
            Copyright (c) 2010 QUALCOMM Incorporated.
            All Rights Reserved.
            Qualcomm Confidential and Proprietary

@file
    Vistroller.java

@brief
    Visual Controller using frame markers

==============================================================================*/


package org.ronhuang.vistroller;

import java.util.Vector;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.pm.ActivityInfo;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.util.DisplayMetrics;
import android.view.View;
import android.view.WindowManager;
import android.view.ViewGroup.LayoutParams;
import android.widget.ImageView;

import com.qualcomm.QCAR.QCAR;


/** The main activity for the Vistroller. */
public class Vistroller extends Activity
{
    // Application status constants:
    private static final int APPSTATUS_UNINITED         = -1;
    private static final int APPSTATUS_INIT_APP         = 0;
    private static final int APPSTATUS_INIT_QCAR        = 1;
    private static final int APPSTATUS_INIT_APP_AR      = 2;
    private static final int APPSTATUS_INIT_TRACKER     = 3;
    private static final int APPSTATUS_INITED           = 4;
    private static final int APPSTATUS_CAMERA_STOPPED   = 5;
    private static final int APPSTATUS_CAMERA_RUNNING   = 6;

    // Name of the native dynamic libraries to load:
    private static final String NATIVE_LIB_VISTROLLER = "vistroller";
    private static final String NATIVE_LIB_QCAR = "QCAR";

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

    // Display size of the device
    private int mScreenWidth = 0;
    private int mScreenHeight = 0;

    // The current application status
    private int mAppStatus = APPSTATUS_UNINITED;

    // The async tasks to initialize the QCAR SDK
    private InitQCARTask mInitQCARTask;
    private LoadTrackerTask mLoadTrackerTask;

    // QCAR initialization flags
    private int mQCARFlags = 0;

    private int mSplashScreenImageResource = 0;

    /** Static initializer block to load native libraries on start-up. */
    static
    {
        loadLibrary(NATIVE_LIB_QCAR);
        loadLibrary(NATIVE_LIB_VISTROLLER);
    }


    /** An async task to initialize QCAR asynchronously. */
    private class InitQCARTask extends AsyncTask<Void, Integer, Boolean>
    {
        // Initialize with invalid value
        private int mProgressValue = -1;

        protected Boolean doInBackground(Void... params)
        {
            QCAR.setInitParameters(Vistroller.this, mQCARFlags);

            do
            {
                // QCAR.init() blocks until an initialization step is complete,
                // then it proceeds to the next step and reports progress in
                // percents (0 ... 100%)
                // If QCAR.init() returns -1, it indicates an error.
                // Initialization is done when progress has reached 100%.
                mProgressValue = QCAR.init();

                // Publish the progress value:
                publishProgress(mProgressValue);

                // We check whether the task has been canceled in the meantime
                // (by calling AsyncTask.cancel(true))
                // and bail out if it has, thus stopping this thread.
                // This is necessary as the AsyncTask will run to completion
                // regardless of the status of the component that started is.
            } while (!isCancelled() && mProgressValue >= 0 && mProgressValue < 100);

            return (mProgressValue > 0);
        }


        protected void onProgressUpdate(Integer... values)
        {
            // Do something with the progress value "values[0]", e.g. update
            // splash screen, progress bar, etc.
        }


        protected void onPostExecute(Boolean result)
        {
            // Done initializing QCAR, proceed to next application
            // initialization status:
            if (result)
            {
                DebugLog.LOGD("InitQCARTask::onPostExecute: QCAR initialization" +
                                                            " successful");

                updateApplicationStatus(APPSTATUS_INIT_APP_AR);
            }
            else
            {
            	// Create dialog box for display error:
            	AlertDialog dialogError = new AlertDialog.Builder(Vistroller.this).create();
            	dialogError.setButton(
            		"Close",
            		new DialogInterface.OnClickListener()
            		{
            			public void onClick(DialogInterface dialog, int which)
            			{
            				// Exiting application
                            System.exit(1);
            			}
            		}
            	);

            	String logMessage;

                // NOTE: Check if initialization failed because the device is
                // not supported. At this point the user should be informed
                // with a message.
                if (mProgressValue == QCAR.INIT_DEVICE_NOT_SUPPORTED)
                {
                	logMessage = "Failed to initialize QCAR because this " +
                	    "device is not supported.";
                }
                else if (mProgressValue ==
                            QCAR.INIT_CANNOT_DOWNLOAD_DEVICE_SETTINGS)
                {
                	logMessage =
                        "Network connection required to initialize camera " +
                        "settings. Please check your connection and restart " +
                        "the application. If you are still experiencing " +
                        "problems, then your device may not be currently " +
                        "supported.";
                }
                else
                {
                	logMessage = "Failed to initialize QCAR.";
                }

                // Log error:
                DebugLog.LOGE("InitQCARTask::onPostExecute: " + logMessage +
                                " Exiting.");

                // Show dialog box with error message:
                dialogError.setMessage(logMessage);
                dialogError.show();
            }
        }
    }


    /** An async task to load the tracker data asynchronously. */
    private class LoadTrackerTask extends AsyncTask<Void, Integer, Boolean>
    {
        protected Boolean doInBackground(Void... params)
        {
            // Initialize with invalid value
            int progressValue = -1;

            do
            {
                progressValue = QCAR.load();
                publishProgress(progressValue);

            } while (!isCancelled() && progressValue >= 0 &&
                        progressValue < 100);

            return (progressValue > 0);
        }


        protected void onProgressUpdate(Integer... values)
        {
            // Do something with the progress value "values[0]", e.g. update
            // splash screen, progress bar, etc.
        }


        protected void onPostExecute(Boolean result)
        {
            DebugLog.LOGD("LoadTrackerTask::onPostExecute: execution " +
                        (result ? "successful" : "failed"));

            // Done loading the tracker, update application status:
            updateApplicationStatus(APPSTATUS_INITED);
        }
    }


    /** Called when the activity first starts or the user navigates back
     * to an activity. */
    protected void onCreate(Bundle savedInstanceState)
    {
        DebugLog.LOGD("Vistroller::onCreate");
        super.onCreate(savedInstanceState);

        // Set the splash screen image to display during initialization:
        mSplashScreenImageResource = R.drawable.splash_screen_frame_markers;

        // Query the QCAR initialization flags:
        mQCARFlags = getInitializationFlags();

        // Update the application status to start initializing application
        updateApplicationStatus(APPSTATUS_INIT_APP);
    }


    /** Configure QCAR with the desired version of OpenGL ES. */
    private int getInitializationFlags()
    {
        return QCAR.GL_20;
    }


    /** Native methods for starting and stoping the camera. */
    private native void startCamera();
    private native void stopCamera();


   /** Called when the activity will start interacting with the user.*/
    protected void onResume()
    {
        DebugLog.LOGD("Vistroller::onResume");
        super.onResume();

        // QCAR-specific resume operation
        QCAR.onResume();

        // We may start the camera only if the QCAR SDK has already been
        // initialized
        if (mAppStatus == APPSTATUS_CAMERA_STOPPED)
            updateApplicationStatus(APPSTATUS_CAMERA_RUNNING);

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
        DebugLog.LOGD("Vistroller::onPause");
        super.onPause();

        if (mGlView != null)
        {
            mGlView.setVisibility(View.INVISIBLE);
            mGlView.onPause();
        }

        // QCAR-specific pause operation
        QCAR.onPause();

        if (mAppStatus == APPSTATUS_CAMERA_RUNNING)
        {
            updateApplicationStatus(APPSTATUS_CAMERA_STOPPED);
        }
    }


    /** Native function to deinitialize the application.*/
    private native void deinitApplicationNative();


    /** The final call you receive before your activity is destroyed.*/
    protected void onDestroy()
    {
        DebugLog.LOGD("Vistroller::onDestroy");
        super.onDestroy();

        // Cancel potentially running tasks
        if (mInitQCARTask != null &&
            mInitQCARTask.getStatus() != InitQCARTask.Status.FINISHED)
        {
            mInitQCARTask.cancel(true);
            mInitQCARTask = null;
        }

        if (mLoadTrackerTask != null &&
            mLoadTrackerTask.getStatus() != LoadTrackerTask.Status.FINISHED)
        {
            mLoadTrackerTask.cancel(true);
            mLoadTrackerTask = null;
        }

        // Do application deinitialization in native code
        deinitApplicationNative();

        // Deinitialize QCAR SDK
        QCAR.deinit();

        System.gc();
    }


    /** NOTE: this method is synchronized because of a potential concurrent
     * access by Vistroller::onResume() and InitQCARTask::onPostExecute(). */
    private synchronized void updateApplicationStatus(int appStatus)
    {
        // Exit if there is no change in status
        if (mAppStatus == appStatus)
            return;

        // Store new status value
        mAppStatus = appStatus;

        // Execute application state-specific actions
        switch (mAppStatus)
        {
            case APPSTATUS_INIT_APP:
                // Initialize application elements that do not rely on QCAR
                // initialization
                initApplication();

                // Proceed to next application initialization status
                updateApplicationStatus(APPSTATUS_INIT_QCAR);
                break;

            case APPSTATUS_INIT_QCAR:
                // Initialize QCAR SDK asynchronously to avoid blocking the
                // main (UI) thread.
                // This task instance must be created and invoked on the UI
                // thread and it can be executed only once!
                try
                {
                    mInitQCARTask = new InitQCARTask();
                    mInitQCARTask.execute();
                }
                catch (Exception e)
                {
                    DebugLog.LOGE("Initializing QCAR SDK failed");
                }
                break;

            case APPSTATUS_INIT_APP_AR:
                // Initialize Augmented Reality-specific application elements
                // that may rely on the fact that the QCAR SDK has been
                // already initialized
                initApplicationAR();

                // Proceed to next application initialization status
                updateApplicationStatus(APPSTATUS_INIT_TRACKER);
                break;

            case APPSTATUS_INIT_TRACKER:
                // Load the tracking data set
                //
                // This task instance must be created and invoked on the UI
                // thread and it can be executed only once!
                try
                {
                    mLoadTrackerTask = new LoadTrackerTask();
                    mLoadTrackerTask.execute();
                }
                catch (Exception e)
                {
                    DebugLog.LOGE("Loading tracking data set failed");
                }
                break;

            case APPSTATUS_INITED:
                // Hint to the virtual machine that it would be a good time to
                // run the garbage collector.
                //
                // NOTE: This is only a hint. There is no guarantee that the
                // garbage collector will actually be run.
                System.gc();

                // The elapsed time since the splash screen was visible:
                long splashScreenTime = System.currentTimeMillis() -
                                            mSplashScreenStartTime;
                long newSplashScreenTime = 0;
                if (splashScreenTime < MIN_SPLASH_SCREEN_TIME)
                {
                    newSplashScreenTime = MIN_SPLASH_SCREEN_TIME -
                                            splashScreenTime;
                }

                // Request a callback function after a given timeout to dismiss
                // the splash screen:
                Handler handler = new Handler();
                handler.postDelayed(
                    new Runnable() {
                        public void run()
                        {
                            // Hide the splash screen
                            mSplashScreenView.setVisibility(View.INVISIBLE);

                            // Activate the renderer
                            mRenderer.mIsActive = true;

                            // Now add the GL surface view. It is important
                            // that the OpenGL ES surface view gets added
                            // BEFORE the camera is started and video
                            // background is configured.
                            addContentView(mGlView, new LayoutParams(
                                            LayoutParams.FILL_PARENT,
                                            LayoutParams.FILL_PARENT));

                            // Start the camera:
                            updateApplicationStatus(APPSTATUS_CAMERA_RUNNING);
                        }
                    }
                    , newSplashScreenTime);

                break;

            case APPSTATUS_CAMERA_STOPPED:
                // Call the native function to stop the camera
                stopCamera();
                break;

            case APPSTATUS_CAMERA_RUNNING:
                // Call the native function to start the camera
                startCamera();
                break;

            default:
                throw new RuntimeException("Invalid application state");
        }
    }


    /** Tells native code whether we are in portait or landscape mode */
    private native void setActivityPortraitMode(boolean isPortrait);


    /** Initialize application GUI elements that are not related to AR. */
    private void initApplication()
    {
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

    	// Pass on screen orientation info to native code
        setActivityPortraitMode(screenOrientation == ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);

        // Query display dimensions
        DisplayMetrics metrics = new DisplayMetrics();
        getWindowManager().getDefaultDisplay().getMetrics(metrics);
        mScreenWidth = metrics.widthPixels;
        mScreenHeight = metrics.heightPixels;

        // As long as this window is visible to the user, keep the device's
        // screen turned on and bright.
        getWindow().setFlags(
            WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON,
            WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

        // Create and add the splash screen view
        mSplashScreenView = new ImageView(this);
        mSplashScreenView.setImageResource(mSplashScreenImageResource);
        addContentView(mSplashScreenView, new LayoutParams(
                        LayoutParams.FILL_PARENT, LayoutParams.FILL_PARENT));

        mSplashScreenStartTime = System.currentTimeMillis();

    }


    /** Native function to initialize the application. */
    private native void initApplicationNative(int width, int height);


    /** Initializes AR application components. */
    private void initApplicationAR()
    {
        // Do application initialization in native code (e.g. registering
        // callbacks, etc.)
        initApplicationNative(mScreenWidth, mScreenHeight);

        // Create OpenGL ES view:
        int depthSize = 16;
        int stencilSize = 0;
        boolean translucent = QCAR.requiresAlpha();

        mGlView = new QCARSampleGLView(this);
        mGlView.init(mQCARFlags, translucent, depthSize, stencilSize);

        mRenderer = new FrameMarkersRenderer();
        mGlView.setRenderer(mRenderer);

    }


    /** A helper for loading native libraries stored in "libs/armeabi*". */
    public static boolean loadLibrary(String nLibName)
    {
        try
        {
            System.loadLibrary(nLibName);
            DebugLog.LOGI("Native library lib" + nLibName + ".so loaded");
            return true;
        }
        catch (UnsatisfiedLinkError ulee)
        {
            DebugLog.LOGE("The library lib" + nLibName +
                            ".so could not be loaded");
        }
        catch (SecurityException se)
        {
            DebugLog.LOGE("The library lib" + nLibName +
                            ".so was not allowed to be loaded");
        }

        return false;
    }
}
