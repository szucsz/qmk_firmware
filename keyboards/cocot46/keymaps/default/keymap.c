/* Copyright 2021 aki27
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include <math.h>
#include "bmp.h"
#include "bmp_custom_keycode.h"
#include "keycode_str_converter.h"
#include "pointing_device.h"
#include "paw3204.h"

bool isScrollMode;
double trackBallAngle = 0.0;
uint8_t trackBallResolution = 0;

// Defines the keycodes used by our macros in process_record_user
enum layer_number {
    _QWERTY = 0,
    _LOWER = 1,
    _RAISE = 2,
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    CUSTOM_KC = BMP_SAFE_RANGE
};

const key_string_map_t custom_keys_user = {
    .start_kc    = CUSTOM_KC,
    .end_kc      = CUSTOM_KC,
    .key_strings = "\0"
};

// dummy definition
const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {KC_NO};

keyevent_t encoder1_ccw = {
    .key = (keypos_t){.row = 3, .col = 6},
    .pressed = false
};

keyevent_t encoder1_cw = {
    .key = (keypos_t){.row = 2, .col = 6},
    .pressed = false
};

void encoder_update_user(uint8_t index, bool clockwise) {
    // for Remap
    // ref : https://twitter.com/_gonnoc/status/1387726213322469379
    // ref : https://github.com/sekigon-gonnoc/qmk_firmware/blob/dev/sekigon/keyboards/sekigon/ecmx20/keymaps/default/keymap.c#L61

    if (index == 0) {
        keypos_t key = clockwise ? encoder1_cw.key : encoder1_ccw.key;
        uint8_t  layer   = layer_switch_get_layer(key);
        uint16_t keycode = keymap_key_to_keycode(layer, key);
        tap_code16(keycode);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool continue_process = process_record_user_bmp(keycode, record);
    if (continue_process == false) {
        return false;
    }

    return true;
}

void matrix_init_user(void) {
    init_paw3204();
    int16_t angle = BMPAPI->app.get_config()->reserved[3];
    trackBallAngle = angle * 3 * M_PI / 180.0;
    trackBallResolution = BMPAPI->app.get_config()->reserved[4];
    if (trackBallResolution > 5) {
        trackBallResolution = 5;
    }
}

void matrix_scan_user(void) {
    static int  cnt;
    static bool paw_ready;

    report_mouse_t mouse_rep = pointing_device_get_report();

    // Trackball check and configration
    if (cnt++ % 50 == 0) {
        static uint8_t last_pid = 0x00;
        uint8_t pid = read_pid_paw3204();
        if (pid != last_pid) {
            paw_ready = (pid == 0x30);
            last_pid = pid;
            if (paw_ready) {
                config_paw3204(trackBallResolution);
                dprint("paw3204 OK\n");
            } else {
                dprintf("paw3204 NG:%d\n", pid);
            }
        }
    }

    if (paw_ready) {
        // Read trackball motion
        uint8_t stat;
        int8_t paw_x, paw_y;
        read_paw3204(&stat, &paw_x, &paw_y);
        // Motion occurred
        if (stat & 0x80) {
            // Rotate coordinates
            int8_t x = paw_y;
            int8_t y = -paw_x;
            int16_t r_x = x * cos(trackBallAngle) - y * sin(trackBallAngle);
            int16_t r_y = x * sin(trackBallAngle) + y * cos(trackBallAngle);
            r_x =  (r_x > 127)? 127 : (-128 > r_x)? -128 : r_x;
            r_y =  (r_y > 127)? 127 : (-128 > r_y)? -128 : r_y;
            // When the movement is slow, it makes delicate movements.
            if (r_x * r_x + r_y * r_y < 20 * 20) {
                r_x = (r_x + (r_x >= 0 ? 1 : -1)) / 2;
                r_y = (r_y + (r_y >= 0 ? 1 : -1)) / 2;
            }
            // Update report
            if (isScrollMode) {
                if (cnt % 5 == 0) {
                    mouse_rep.v = -r_y;
                    mouse_rep.h = r_x;
                }
            } else {
                mouse_rep.x = r_x;
                mouse_rep.y = r_y;
            }
            pointing_device_set_report(mouse_rep);

            // Debug print
            dprintf("stat:%2x paw:[%4d,%4d] report:[%4d,%4d]\n", stat, paw_x, paw_y, mouse_rep.x, mouse_rep.y);
        }
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _LOWER:
    case _RAISE:
        isScrollMode = true;
        break;
    default:
        isScrollMode = false;
        break;
    }
  return state;
}