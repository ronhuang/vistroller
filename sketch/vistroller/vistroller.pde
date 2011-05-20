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

#include <PS2X_lib.h>
#include "markers.h"

#define DEBUG_LED_PIN 13
#define OLED_WIDTH 160
#define OLED_HEIGHT 128
#define MARKER_PIXEL 26
// marker size = 2 + 1 + 1 + 2 * 9 + 1 + 1 + 2

// forward declaration
void osdPrintln(const char *str);
void drawMarker(const byte *marker);

// create PS2 Controller Class
PS2X ps2x;
int error = 0;

int buttons[] = {
    PSB_PAD_LEFT, PSB_PAD_RIGHT, PSB_SQUARE, PSB_CROSS,
    PSB_PAD_UP, PSB_PAD_DOWN, PSB_TRIANGLE, PSB_CIRCLE,
    PSB_SELECT, PSB_START,
    PSB_L1, PSB_L2, PSB_L3,
    PSB_R1, PSB_R2, PSB_R3
};

void setup() {
    // Initialize LED onboard.
    pinMode(DEBUG_LED_PIN, OUTPUT);

    // OLED serial port.
    Serial.begin(115200);


    // OLED
    OLED_Init();
    OLED_Clear();

    // FIXME: not needed.
    OLED_SetTextTrans(0x01);


    // PS2 controller
    //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
    error = ps2x.config_gamepad(7, 9, 8, 6, false, false);

    if (error == 0) {
        byte type = ps2x.readType();

        switch(type) {
        case 0:
            osdPrintln("Unknown controller type.");
            break;
        case 1:
            osdPrintln("DualShock controller found.");
            break;
        case 2:
            osdPrintln("GuitarHero controller found.");
            break;
        }
    }
    else if (error == 1)
        osdPrintln("No controller found, check wiring.");
    else if (error == 2)
        osdPrintln("Controller found but not accepting commands.");
    else if (error == 3)
        osdPrintln("Controller refusing to enter pressures mode, may not support it.");
}

void loop() {
    if (error > 0) { //skip loop if no controller found
        static bool high = true;
        digitalWrite(DEBUG_LED_PIN, high ? HIGH : LOW);
        high = !high;
        delay(1000);
        return;
    }

    ps2x.read_gamepad();

    for (int k = 0; k < sizeof(buttons) / sizeof(buttons[0]); k++) {
        if (!ps2x.Button(buttons[k]))
            continue;
        const byte *marker = &markers[k * 36];
        drawMarker(marker);
    }

    delay(50);
}

void osdPrintln(const char *str) {
    OLED_DrawText(0, 0, 0, str, 0xFFFF);
}

void drawMarker(const byte *marker) {
    static int size = min(OLED_WIDTH, OLED_HEIGHT) / MARKER_PIXEL;

    // draw black frame
    // draw ID
    // draw other?
}
