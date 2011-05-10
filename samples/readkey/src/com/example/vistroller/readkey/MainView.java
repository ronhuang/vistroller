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


package com.example.vistroller.readkey;

import android.view.View;
import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.view.KeyEvent;
import android.util.Log;


public class MainView extends View {
    private Paint mPaint;
    private String mShowOnScreen;
    private long mPreviousKeyDownTime = 0;
    private String mFrequency;

    // Log tag
    private static final String TAG = "MainView";


    public MainView(Context context) {
        super(context);

        init();
    }


    public MainView(Context context, AttributeSet attrs) {
        super(context, attrs);

        init();
    }


    public MainView(Context context, AttributeSet attrs, int defStyle) {
        super(context, attrs, defStyle);

        init();
    }


    private void init() {
        // Initialize paint
        mPaint = new Paint();
        mPaint.setDither(true);
        mPaint.setColor(0xFFFFFF00);
        mPaint.setStyle(Paint.Style.STROKE);
        mPaint.setStrokeJoin(Paint.Join.ROUND);
        mPaint.setStrokeCap(Paint.Cap.ROUND);
        mPaint.setStrokeWidth(1);

        mPaint.setTextSize(30.0f);
    }


    @Override
    protected void onDraw(Canvas canvas) {
        if (null != mFrequency)
            canvas.drawText(mFrequency, 100.0f, 100.0f, mPaint);

        if (null != mShowOnScreen)
            canvas.drawText(mShowOnScreen, 200.0f, 200.0f, mPaint);
    }


    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        long interval = event.getEventTime() - mPreviousKeyDownTime;
        mPreviousKeyDownTime = event.getEventTime();

        Log.d(TAG, "MainView::onKeyDown: " + keyCode);

        if (interval > 0) {
            mFrequency = String.format("Key down frequency: %01.2f keys/second", 1000f / interval);
            invalidate();
        }

        return false;
    }


    @Override
    public boolean onKeyUp(int keyCode, KeyEvent event) {
        Log.d(TAG, "MainView::onKeyUp: " + keyCode);

        mShowOnScreen = String.format("%d", keyCode);
        invalidate();

        return false;
    }
}
