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


package com.example.vistroller.dualshock;

import android.app.Activity;
import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.view.WindowManager;
import android.util.Log;

import org.ronhuang.vistroller.Vistroller;
import org.ronhuang.vistroller.VistrollerListener;


/** The main activity for the MainActivity. */
public class MainActivity extends Activity implements VistrollerListener {
    // Handler to view.
    MainView mView;

    // Vistroller instance.
    private Vistroller mVistroller;

    // Force orientation.
    private int mScreenOrientation = ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE;

    // Log tag
    private static final String TAG = "MainActivity";


    /** Called when the activity first starts or the user navigates back
     * to an activity. */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        Log.d(TAG, "MainActivity::onCreate");
        super.onCreate(savedInstanceState);

        // Specify layout
        setContentView(R.layout.main);

        // Apply screen orientation
        setRequestedOrientation(mScreenOrientation);

        // As long as this window is visible to the user, keep the device's
        // screen turned on and bright.
        getWindow().setFlags(
            WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON,
            WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

        // Create and initialize Vistroller instance.
        mVistroller = new Vistroller(this);
        mVistroller.addListener(this);
        mVistroller.onCreate();

        // Handler to view.
        mView = (MainView)findViewById(R.id.canvas);
    }


   /** Called when the activity will start interacting with the user.*/
    @Override
    protected void onResume() {
        Log.d(TAG, "MainActivity::onResume");
        super.onResume();

        mVistroller.onResume();
    }


    /** Called when the system is about to start resuming a previous activity.*/
    @Override
    protected void onPause() {
        Log.d(TAG, "MainActivity::onPause");
        super.onPause();

        mVistroller.onPause();
    }


    /** The final call you receive before your activity is destroyed.*/
    @Override
    protected void onDestroy() {
        Log.d(TAG, "MainActivity::onDestroy");
        super.onDestroy();

        mVistroller.onDestroy();
    }


    /** Listen to Vistroller events. */
    public void onVistrollerStateChanged(Vistroller.State state) {
        Log.d(TAG, "MainActivity::onVistrollerStateChanged: " + state);

        switch (state) {
        case ENGINE_INITIALIZED:
            break;

        case TRACKER_INITIALIZED:
            break;

        case SYSTEM_INITIALIZED:
            // Start the camera.
            mVistroller.start();
            break;

        default:
            break;
        }
    }


    /** Update progress. */
    public void onVistrollerProgressUpdate(int progress) {
        mView.setProgress(progress);
    }
}
