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

package org.ronhuang.vistroller;

import java.util.List;
import java.util.ArrayList;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.os.AsyncTask;
import android.util.Log;

import com.qualcomm.QCAR.QCAR;


public class Vistroller
{
    private Activity mActivity;
    private List<VistrollerListener> mListeners;

    // Application status constants:
    private static final int STATUS_UNINITED         = -1;
    private static final int STATUS_INIT_ENGINE      = 1;
    private static final int STATUS_INIT_TRACKER     = 2;
    private static final int STATUS_INITED           = 3;
    private static final int STATUS_CAMERA_STOPPED   = 4;
    private static final int STATUS_CAMERA_RUNNING   = 5;

    // Name of the native dynamic libraries to load:
    private static final String NATIVE_LIB_VISTROLLER = "vistroller";
    private static final String NATIVE_LIB_QCAR = "QCAR";

    // Display size of the device
    private int mScreenWidth = 0;
    private int mScreenHeight = 0;

    // The current application status
    private int mStatus = STATUS_UNINITED;

    // The async tasks to initialize the QCAR SDK
    private InitQCARTask mInitQCARTask;
    private LoadTrackerTask mLoadTrackerTask;

    // QCAR initialization flags
    private int mQCARFlags = 0;

    // Log tag
    private static final String TAG = "Vistroller";

    /** Static initializer block to load native libraries on start-up. */
    static
    {
        loadLibrary(NATIVE_LIB_QCAR);
        loadLibrary(NATIVE_LIB_VISTROLLER);
    }


    /** Exposed states. */
    public enum State {
        ENGINE_INITIALIZED,
        TRACKER_INITIALIZED,
        SYSTEM_INITIALIZED
    }


    /** Constructor */
    public Vistroller(Activity nActivity)
    {
        mActivity = nActivity;

        // Query the QCAR initialization flags:
        mQCARFlags = QCAR.GL_20;

        mListeners = new ArrayList<VistrollerListener>();
    }


    /** Get flags. */
    public int getFlags()
    {
        return mQCARFlags;
    }


    /** requiresAlpha */
    public boolean requiresAlpha()
    {
        return QCAR.requiresAlpha();
    }


    /** Add listener to various events. */
    public void addListener(VistrollerListener listener)
    {
        mListeners.add(listener);
    }


    /** Trigger state changed event to listeners. */
    private void triggerStateChanged(State state)
    {
        for (int i = 0; i < mListeners.size(); i++) {
            mListeners.get(i).onVistrollerStateChanged(state);
        }
    }


    /** Request starting camera. */
    public void requestStartCamera()
    {
        updateApplicationStatus(STATUS_CAMERA_RUNNING);
    }


    /** Set the screen size from activity. */
    public void setScreenSize(int width, int height)
    {
        mScreenWidth = width;
        mScreenHeight = height;
    }


    /** Native function to initialize the application. */
    private native void updateScreenSize(int width, int height);


    /** An async task to initialize QCAR asynchronously. */
    private class InitQCARTask extends AsyncTask<Void, Integer, Boolean>
    {
        // Initialize with invalid value
        private int mProgressValue = -1;

        protected Boolean doInBackground(Void... params)
        {
            QCAR.setInitParameters(mActivity, mQCARFlags);

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
                Log.d(TAG, "InitQCARTask::onPostExecute: QCAR initialization" + " successful");

                // Inform screen to QCAR, is it necessary?
                updateScreenSize(mScreenWidth, mScreenHeight);

                // Inform listeners.
                triggerStateChanged(State.ENGINE_INITIALIZED);

                // Done initialization
                updateApplicationStatus(STATUS_INIT_TRACKER);
            }
            else
            {
            	// Create dialog box for display error:
            	AlertDialog dialogError = new AlertDialog.Builder(mActivity).create();
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
                Log.e(TAG, "InitQCARTask::onPostExecute: " + logMessage + " Exiting.");

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
            Log.d(TAG, "LoadTrackerTask::onPostExecute: execution " + (result ? "successful" : "failed"));

            triggerStateChanged(State.TRACKER_INITIALIZED);

            // Done loading the tracker, update application status:
            updateApplicationStatus(STATUS_INITED);
        }
    }


    /** Called when the activity first starts or the user navigates back
     * to an activity. */
    protected void onCreate()
    {
        Log.d(TAG, "Vistroller::onCreate");

        // Update the application status to start initializing application
        updateApplicationStatus(STATUS_INIT_ENGINE);
    }


    /** Native methods for starting and stoping the camera. */
    private native void startCamera();
    private native void stopCamera();


   /** Called when the activity will start interacting with the user.*/
    protected void onResume()
    {
        Log.d(TAG, "Vistroller::onResume");

        // QCAR-specific resume operation
        QCAR.onResume();

        // We may start the camera only if the QCAR SDK has already been
        // initialized
        if (mStatus == STATUS_CAMERA_STOPPED)
            updateApplicationStatus(STATUS_CAMERA_RUNNING);
    }


    /** Called when the system is about to start resuming a previous activity.*/
    protected void onPause()
    {
        Log.d(TAG, "Vistroller::onPause");

        // QCAR-specific pause operation
        QCAR.onPause();

        if (mStatus == STATUS_CAMERA_RUNNING)
            updateApplicationStatus(STATUS_CAMERA_STOPPED);
    }


    /** Native function to initialize the application. */
    private native void deinitApplicationNative();


    /** The final call you receive before your activity is destroyed.*/
    protected void onDestroy()
    {
        Log.d(TAG, "Vistroller::onDestroy");

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
        if (mStatus == appStatus)
            return;

        // Store new status value
        mStatus = appStatus;

        // Execute application state-specific actions
        switch (mStatus)
        {
            case STATUS_INIT_ENGINE:
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
                    Log.e(TAG, "Initializing QCAR SDK failed");
                }
                break;

            case STATUS_INIT_TRACKER:
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
                    Log.e(TAG, "Loading tracking data set failed");
                }
                break;

            case STATUS_INITED:
                // Hint to the virtual machine that it would be a good time to
                // run the garbage collector.
                //
                // NOTE: This is only a hint. There is no guarantee that the
                // garbage collector will actually be run.
                System.gc();
                break;

            case STATUS_CAMERA_STOPPED:
                // Call the native function to stop the camera
                stopCamera();
                break;

            case STATUS_CAMERA_RUNNING:
                // Call the native function to start the camera
                startCamera();
                break;

            default:
                throw new RuntimeException("Invalid application state");
        }
    }


    /** Tells native code whether we are in portait or landscape mode */
    public native void setActivityPortraitMode(boolean isPortrait);


    /** A helper for loading native libraries stored in "libs/armeabi*". */
    private static boolean loadLibrary(String nLibName)
    {
        try
        {
            System.loadLibrary(nLibName);
            Log.i(TAG, "Native library lib" + nLibName + ".so loaded");
            return true;
        }
        catch (UnsatisfiedLinkError ulee)
        {
            Log.e(TAG, "The library lib" + nLibName + ".so could not be loaded");
        }
        catch (SecurityException se)
        {
            Log.e(TAG, "The library lib" + nLibName + ".so was not allowed to be loaded");
        }

        return false;
    }
}
