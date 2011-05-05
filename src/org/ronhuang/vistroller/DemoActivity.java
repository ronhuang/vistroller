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


/** The main activity for the DemoActivity. */
public class DemoActivity extends Activity implements VistrollerListener {
    // Vistroller instance
    private Vistroller mVistroller;

    // Our views:
    private DemoView mFgView;

    // Force orientation.
    private int mScreenOrientation = ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE;

    // Log tag
    private static final String TAG = "DemoActivity";


    /** Called when the activity first starts or the user navigates back
     * to an activity. */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        Log.d(TAG, "DemoActivity::onCreate");
        super.onCreate(savedInstanceState);

        // Specify layout
        setContentView(R.layout.demo);

        // Apply screen orientation
        setRequestedOrientation(mScreenOrientation);

        // As long as this window is visible to the user, keep the device's
        // screen turned on and bright.
        getWindow().setFlags(
            WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON,
            WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

        // Initialize foreground view.
        mFgView = (DemoView)findViewById(R.id.canvas);

        // Create and initialize Vistroller instance.
        mVistroller = new Vistroller(this);
        mVistroller.addListener(this);
        mVistroller.onCreate();
    }


   /** Called when the activity will start interacting with the user.*/
    @Override
    protected void onResume() {
        Log.d(TAG, "DemoActivity::onResume");
        super.onResume();

        mVistroller.onResume();
    }


    /** Called when the system is about to start resuming a previous activity.*/
    @Override
    protected void onPause() {
        Log.d(TAG, "DemoActivity::onPause");
        super.onPause();

        mVistroller.onPause();
    }


    /** The final call you receive before your activity is destroyed.*/
    @Override
    protected void onDestroy() {
        Log.d(TAG, "DemoActivity::onDestroy");
        super.onDestroy();

        mVistroller.onDestroy();
    }


    /** Listen to Vistroller events. */
    public void onVistrollerStateChanged(Vistroller.State state) {
        Log.d(TAG, "DemoActivity::onVistrollerStateChanged: " + state);

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
}
