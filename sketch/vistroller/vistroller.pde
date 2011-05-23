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
#define MARKER_PIXEL_COUNT 26 // marker size = 2 + 1 + 1 + 2 * 9 + 1 + 1 + 2
#define MARKER_SYMBOL_COUNT 10

#define COLOR_BACKGROUND 0x4A4A // rgb(79, 73, 87)
#define COLOR_BLACK 0x0000
#define COLOR_WHITE 0xFFFF
#define COLOR_GREEN 0x8679 // green rgb(135, 205, 205)
#define COLOR_RED 0xE576 // red rgb(229, 174, 180)
#define COLOR_BLUE 0xC6DF // blue rgb(194, 217, 248)
#define COLOR_PINK 0xFF1E // pink rgb(250, 225, 244)

// Forward declaration
void osdPrintln(const char *str);
void drawMarker(const byte *marker);
void drawMarkerSymbol(const int button);
void clearMarker();

// Global constants used for controller
const int buttons[] = {
    PSB_PAD_LEFT, PSB_PAD_RIGHT, PSB_SQUARE, PSB_CROSS,
    PSB_PAD_UP, PSB_PAD_DOWN, PSB_TRIANGLE, PSB_CIRCLE,
    PSB_SELECT, PSB_START,
    PSB_L1, PSB_L2, PSB_L3,
    PSB_R1, PSB_R2, PSB_R3
};

const char *button_labels[] = {
    "L1", "L2", "L3", "R1", "R2", "R3"
};

// Global constants used in drawMarker()
const char marker_pixel_size = min(OLED_WIDTH, OLED_HEIGHT) / MARKER_PIXEL_COUNT;
const char marker_size = marker_pixel_size * MARKER_PIXEL_COUNT;
const char marker_x_offset = (OLED_WIDTH - marker_size) >> 1;
const char marker_y_offset = (OLED_HEIGHT - marker_size) >> 1;
const int marker_id_colors[] = {COLOR_BLACK, COLOR_WHITE};

// Global constants used in drawMarkerSymbol()
const char symbol_size = marker_pixel_size * MARKER_SYMBOL_COUNT;
const char symbol_x_offset = marker_x_offset + ((marker_size - symbol_size) >> 1);
const char symbol_y_offset = marker_y_offset + ((marker_size - symbol_size) >> 1);

// Global variables for drawing
static PS2X ps2x;
static int error = 0;
static int button_label_base = 0;
static bool dirty = true;

//
void setup() {
    // Initialize LED onboard.
    pinMode(DEBUG_LED_PIN, OUTPUT);

    // OLED serial port.
    Serial.begin(115200);


    // OLED
    OLED_Init();
    OLED_Background(COLOR_BACKGROUND);
    OLED_SetTextTrans(1); // for debug message
    OLED_Clear();



    // Compute button_label_base
    for (int i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++) {
        if (PSB_L1 == buttons[i]) {
            button_label_base = i;
            break;
        }
    }



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

    bool marker_found = false;

    for (int index = 0; index < sizeof(buttons) / sizeof(buttons[0]); index++) {
        if (!ps2x.Button(buttons[index]))
            continue;

        marker_found = true;

        drawMarker(index);
        break; // only one marker at a time.
    }

    if (!marker_found)
        clearMarker();

    delay(50);
}

void osdPrintln(const char *str) {
    OLED_DrawText(0, 0, 0, str, COLOR_WHITE);
}

void drawMarker(const int index) {
    const byte *marker = &markers[index * 36];
    char t, u, v;

    // Draw solid
    OLED_PenSize(0);

    // draw white frame
    t = marker_pixel_size + marker_pixel_size;
    u = marker_size - t;
    OLED_DrawRectangle(marker_x_offset + 0, marker_y_offset + 0, u, t, COLOR_WHITE); // top
    OLED_DrawRectangle(marker_x_offset + u, marker_y_offset + 0, t, u, COLOR_WHITE); // right
    OLED_DrawRectangle(marker_x_offset + t, marker_y_offset + u, u, t, COLOR_WHITE); // bottom
    OLED_DrawRectangle(marker_x_offset + 0, marker_y_offset + t, t, u, COLOR_WHITE); // left

    // draw black frame
    t = marker_pixel_size + marker_pixel_size;
    u = marker_size - marker_pixel_size * 5;
    v = marker_pixel_size;
    OLED_DrawRectangle(marker_x_offset + t + 0, marker_y_offset + t + 0, u, v, COLOR_BLACK);
    OLED_DrawRectangle(marker_x_offset + t + u, marker_y_offset + t + 0, v, u, COLOR_BLACK);
    OLED_DrawRectangle(marker_x_offset + t + v, marker_y_offset + t + u, u, v, COLOR_BLACK);
    OLED_DrawRectangle(marker_x_offset + t + 0, marker_y_offset + t + v, v, u, COLOR_BLACK);

    // draw ID
    t = marker_x_offset + marker_pixel_size * 4;
    u = marker_y_offset + marker_pixel_size * 3;
    v = 0;
    for (; v < 9; v++) {
      OLED_DrawRectangle(t, u, marker_pixel_size, marker_pixel_size, marker_id_colors[marker[v]]);
      t += marker_pixel_size + marker_pixel_size;
    }
    t = marker_x_offset + marker_size - marker_pixel_size * 4;
    u = marker_y_offset + marker_pixel_size * 4;
    for (; v < 18; v++) {
      OLED_DrawRectangle(t, u, marker_pixel_size, marker_pixel_size, marker_id_colors[marker[v]]);
      u += marker_pixel_size + marker_pixel_size;
    }
    t = marker_x_offset + marker_pixel_size * 5;
    u = marker_y_offset + marker_size - marker_pixel_size * 4;
    for (; v < 27; v++) {
      OLED_DrawRectangle(t, u, marker_pixel_size, marker_pixel_size, marker_id_colors[marker[v]]);
      t += marker_pixel_size + marker_pixel_size;
    }
    t = marker_x_offset + marker_pixel_size * 3;
    u = marker_y_offset + marker_pixel_size * 5;
    for (; v < 36; v++) {
      OLED_DrawRectangle(t, u, marker_pixel_size, marker_pixel_size, marker_id_colors[marker[v]]);
      u += marker_pixel_size + marker_pixel_size;
    }

    // draw symbol
    drawMarkerSymbol(index);

    dirty = true;
}

void drawMarkerSymbol(const int index) {
    const int button = buttons[index];
    char t, u, v;

    // Clear previous symbol with background color
    OLED_PenSize(0);
    OLED_DrawRectangle(symbol_x_offset, symbol_y_offset,
                       symbol_size + 1, symbol_size + 1,
                       COLOR_BACKGROUND);

    // Draw wire frame
    OLED_PenSize(1);

    switch (button) {
    case PSB_PAD_UP:
        t = symbol_size >> 1;
        u = symbol_size >> 2;
        OLED_DrawPolygon(symbol_x_offset + t, symbol_y_offset,
                         symbol_x_offset + u, symbol_y_offset + t,
                         symbol_x_offset + u, symbol_y_offset + symbol_size,
                         symbol_x_offset + t + u, symbol_y_offset + symbol_size,
                         symbol_x_offset + t + u, symbol_y_offset + t,
                         COLOR_BLACK);
        break;

    case PSB_PAD_RIGHT:
        t = symbol_size >> 1;
        u = symbol_size >> 2;
        OLED_DrawPolygon(symbol_x_offset, symbol_y_offset + u,
                         symbol_x_offset, symbol_y_offset + t + u,
                         symbol_x_offset + t, symbol_y_offset + t + u,
                         symbol_x_offset + symbol_size, symbol_y_offset + t,
                         symbol_x_offset + t, symbol_y_offset + u,
                         COLOR_BLACK);
        break;

    case PSB_PAD_DOWN:
        t = symbol_size >> 1;
        u = symbol_size >> 2;
        OLED_DrawPolygon(symbol_x_offset + u, symbol_y_offset,
                         symbol_x_offset + u, symbol_y_offset + t,
                         symbol_x_offset + t, symbol_y_offset + symbol_size,
                         symbol_x_offset + t + u, symbol_y_offset + t,
                         symbol_x_offset + t + u, symbol_y_offset,
                         COLOR_BLACK);
        break;

    case PSB_PAD_LEFT:
        t = symbol_size >> 1;
        u = symbol_size >> 2;
        OLED_DrawPolygon(symbol_x_offset, symbol_y_offset + t,
                         symbol_x_offset + t, symbol_y_offset + t + u,
                         symbol_x_offset + symbol_size, symbol_y_offset + t + u,
                         symbol_x_offset + symbol_size, symbol_y_offset + u,
                         symbol_x_offset + t, symbol_y_offset + u,
                         COLOR_BLACK);
        break;

    case PSB_TRIANGLE:
        t = symbol_size >> 1;
        u = symbol_size >> 2;
        v = (char)(((int)symbol_size * 113512) >> 18); // symbol_size * 3^0.5 / 4
        OLED_DrawTriangle(symbol_x_offset + t, symbol_y_offset,
                          symbol_x_offset + t - v, symbol_y_offset + t + u,
                          symbol_x_offset + t + v, symbol_y_offset + t + u,
                          COLOR_GREEN);
        break;

    case PSB_CIRCLE:
        t = symbol_size >> 1;
        OLED_DrawCircle(symbol_x_offset + t, symbol_y_offset + t,
                        t, COLOR_RED);
        break;

    case PSB_CROSS:
        t = symbol_size >> 1;
        u = symbol_size * 46341 >> 17; // symbol_size / 2 / 2^0.5
        OLED_DrawLine(symbol_x_offset + t - u, symbol_y_offset + t - u,
                      symbol_x_offset + t + u, symbol_y_offset + t + u,
                      COLOR_BLUE);
        OLED_DrawLine(symbol_x_offset + t + u, symbol_y_offset + t - u,
                      symbol_x_offset + t - u, symbol_y_offset + t + u,
                      COLOR_BLUE);
        break;

    case PSB_SQUARE:
        t = symbol_size >> 1;
        u = symbol_size * 46341 >> 17; // symbol_size / 2 / 2^0.5
        OLED_DrawRectangle(symbol_x_offset + t - u, symbol_y_offset + t - u,
                           u + u, u + u, COLOR_PINK);
        break;

    case PSB_SELECT:
        t = symbol_size >> 1;
        u = symbol_size >> 2;
        v = symbol_size >> 3;
        OLED_DrawRectangle(symbol_x_offset + u, symbol_y_offset + t - v,
                           t, u, COLOR_BLACK);
        break;

    case PSB_START:
        t = symbol_size >> 1;
        u = symbol_size >> 2;
        v = symbol_size >> 3;
        OLED_DrawTriangle(symbol_x_offset + u, symbol_y_offset + t - v,
                          symbol_x_offset + u, symbol_y_offset + t + v,
                          symbol_x_offset + t + u, symbol_y_offset + t,
                          COLOR_BLACK);
        break;

    case PSB_L1:
    case PSB_L2:
    case PSB_L3:
    case PSB_R1:
    case PSB_R2:
    case PSB_R3:
        t = index - button_label_base;
        OLED_DrawText(9, 5, 2, button_labels[t], COLOR_BLACK);
        break;

    default:
        break;
    }
}

void clearMarker() {
    if (!dirty)
        return;

    // Clear previous marker with background color
    OLED_PenSize(0);
    OLED_DrawRectangle(marker_x_offset, marker_y_offset,
                       marker_size + 1, marker_size + 1,
                       COLOR_BACKGROUND);

    dirty = false;
}
