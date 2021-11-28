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

#include "cocot46.h"
#include <string.h>
#include "debug.h"

#include QMK_KEYBOARD_H
#include "matrix.h"
#include "bmp.h"
#include "bmp_matrix.h"
#include "spi.h"
#include "paw3204.h"

#include "report.h"

void keyboard_post_init_kb() { debug_enable = false; }

void create_user_file() {
    // static const char qmk_configurator[] =
    //     "<meta http-equiv=\"refresh\" "
    //     "content=\"0;URL=\'https://sekigon-gonnoc.github.io/qmk_configurator/#/"
    //     "kugel/LAYOUT\'\"/>";
    // BMPAPI->usb.create_file("MAP_EDITHTM", (uint8_t *)qmk_configurator,
    //                         strlen(qmk_configurator));

    // static const char build_guide[] =
    //     "<meta http-equiv=\"refresh\" "
    //     "content=\"0;URL=\'https://github.com/sekigon-gonnoc/Kugel-doc\'\"/>";
    // BMPAPI->usb.create_file("BLDGUIDEHTM", (uint8_t *)build_guide,
    //                         strlen(build_guide));
}

// static void create_status_file() {
//     static char status_str[128];
//     // clang-format off
//     tfp_sprintf(status_str,
//                 "Trackball:%s\r\n",
//                 trackball_init_flag == TRACKBALL_BTO ? " BTO" : "NO");
//     // clang-format on
//     BMPAPI->usb.create_file("STATUS  TXT", (uint8_t *)status_str,
//                             strlen(status_str));
// }

void matrix_scan_kb() {

    static float voltage = -1;
    if (!is_usb_connected()) {
        static uint32_t battery_check_cnt = 0;
        static uint32_t low_battery_cnt = 0;

        if (voltage < 0) {
            // first measurement
            voltage = BMPAPI->app.get_vcc_mv();
            battery_check_cnt = timer_read32();
        } else if (timer_elapsed32(battery_check_cnt) > 1000) {
            battery_check_cnt = timer_read32();
            uint32_t v_mes =  BMPAPI->app.get_vcc_mv();

            if (v_mes > voltage) {
                voltage = (0.7f) * voltage + (0.3f) * v_mes;
            } else {
                if (voltage - v_mes > 100) {
                } else {
                    voltage = (0.95f) * voltage + (0.05f) * v_mes;
                }
            }

            if (voltage < 1000.0f - 100.0f) { // 100mV offset by series resistance
                low_battery_cnt++;
            }

            if (low_battery_cnt > 30) {
                sleep_enter_counter = 1;
            }
        }
    } else {
        voltage = -1;
    }

    matrix_scan_user();
}

// void bmp_before_sleep() {
// ////    setPinInputHigh(16);
// ////    setPinInputHigh(14);
//     // setPinInputHigh(CS_PIN_TB);
// ////    writePinHigh(TB_POW);
// }

// bool bmp_config_overwrite(bmp_api_config_t const *const config_on_storage,
//                           bmp_api_config_t *const       keyboard_config) {
//     // get vcc from a3
//     BMPAPI->adc.config_vcc_channel(3, 1200, 700);
//     // wait until voltage become stable
//     for (int i = 0; i < 40000; i++) {
//         BMPAPI->app.get_vcc_percent();
//     }

//     // User can overwrite partial settings
//     keyboard_config->startup          = config_on_storage->startup;
//     keyboard_config->matrix.debounce  = config_on_storage->matrix.debounce;
//     keyboard_config->param_central    = config_on_storage->param_central;
//     keyboard_config->param_peripheral = config_on_storage->param_peripheral;
//     keyboard_config->keymap           = config_on_storage->keymap;
//     keyboard_config->reserved[2]      = config_on_storage->reserved[2];
//     return true;
// }
