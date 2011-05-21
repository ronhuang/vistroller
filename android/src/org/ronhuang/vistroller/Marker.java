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

import java.util.Arrays;


public class Marker
{
    private short mId = -1;
    private float[] mPose;
    private float[] mSize;


    public Marker(short id, float[] pose, float[] size) {
        mId = id;
        mPose = pose;
        mSize = size;
    }


    public short getId() {
        return mId;
    }


    public float[] getPose() {
        return mPose;
    }


    public float[] getSize() {
        return mSize;
    }


    public boolean isValid() {
        return mId >= 0;
    }


    @Override
    public boolean equals(Object o) {
        Marker m = (Marker)o;

        return mId == m.getId() &&
            Arrays.equals(mPose, m.getPose()) &&
            Arrays.equals(mSize, m.getSize());
    }
}
