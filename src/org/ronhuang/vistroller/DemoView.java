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

import android.view.View;
import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.view.KeyEvent;


public class DemoView extends View {
    private Paint mPaint;
    private String mShowOnScreen;

    public DemoView(Context context) {
        super(context);

        init();
    }

    public DemoView(Context context, AttributeSet attrs) {
        super(context, attrs);

        init();
    }

    public DemoView(Context context, AttributeSet attrs, int defStyle) {
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
        mPaint.setStrokeWidth(3);

        mPaint.setTextSize(30.0f);
    }

    @Override
    protected void onDraw(Canvas canvas) {
        canvas.drawCircle(100.0f, 100.0f, 30.0f, mPaint);

        if (null != mShowOnScreen)
            canvas.drawText(mShowOnScreen, 200.0f, 200.0f, mPaint);
    }

    @Override
    public boolean onKeyUp(int keyCode, KeyEvent event) {
        mShowOnScreen = String.format("%d", keyCode);
        return true;
    }
}
