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

import android.view.SurfaceHolder;
import android.graphics.Canvas;


public class DemoViewThread extends Thread {
    private DemoView mView;
    private SurfaceHolder mHolder;
    private boolean mRun = false;

    public DemoViewThread(DemoView view) {
        mView = view;
        mHolder = mView.getHolder();
    }

    public void setRunning(boolean run) {
        mRun = run;
    }

    @Override
    public void run() {
        Canvas canvas = null;

        while (mRun) {
            canvas = mHolder.lockCanvas();
            if (canvas != null) {
                mView.doDraw(canvas);
                mHolder.unlockCanvasAndPost(canvas);
            }
        }
    }
}
