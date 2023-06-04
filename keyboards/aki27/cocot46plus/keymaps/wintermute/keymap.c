/*
Copyright 2022 aki27

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// to compile: qmk compile -kb aki27/cocot46plus -km wintermute

#include QMK_KEYBOARD_H
#include <stdio.h>
#include "quantum.h"
#include <print.h>
#include "version.h"
#include "cocot46plus.h"

// Defines names for use in layer keycodes and the keymap
enum layer_number {
    L_BASE   = 0,
    L_FUN    = 1,
    L_SYM    = 2,
    L_MEDIA  = 3,
    L_NUM    = 4,
    L_NAV    = 5,
    L_META   = 6,
    L_SWITCH = 7
};

enum custom_keycodes {
    PREV_WINDOW = QK_KB_7,
    NEXT_WINDOW,
};

#define SYM(k)    LT(L_SYM,k)
#define NUM(k)    LT(L_NUM,k)
#define FUN(k)    LT(L_FUN,k)
#define META(k)   LT(L_META,k)
#define NAV(k)    LT(L_NAV,k)
#define MEDIA(k)  LT(L_MEDIA,k)

#define HMS(k)    MT(MOD_LSFT,k)
#define HMC(k)    MT(MOD_LCTL,k)
#define HMG(k)    MT(MOD_LGUI,k)
#define HMA(k)    MT(MOD_LALT,k)

#define CA(k)     C(A(k))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  //`------' O O O     O O O `------'
  [L_BASE] = LAYOUT(
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
        KC_ESC,      KC_Q,      KC_W,      KC_E,      KC_R,   KC_T,                    KC_Y,        KC_U,       KC_I,       KC_O,          KC_P, KC_BSPC,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
       KC_LCTL, HMG(KC_A), HMA(KC_S), HMC(KC_D), HMS(KC_F),   KC_G,                    KC_H,   HMS(KC_J),  HMC(KC_K),  HMA(KC_L),  HMG(KC_SCLN), KC_QUOT,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
       KC_LSFT,      KC_Z,      KC_X,      KC_C,      KC_V,   KC_B,                    KC_N,        KC_M,    KC_COMM,     KC_DOT,       KC_SLSH, KC_MINS,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
            KC_LGUI, META(KC_ESC), NAV(KC_BSPC), NUM(KC_TAB), KC_MS_BTN1,        KC_MS_BTN2,  FUN(KC_ENT),  SYM(KC_SPC), MEDIA(KC_DEL), KC_LALT,
                                                      KC_WH_U, MO(L_SWITCH),     KC_WH_D, XXXXXXX, XXXXXXX, XXXXXXX
                               //`------------------------------------' O O O  O O O `------------------------------------'
    ),

// right hand activated layers
  //`------' O O O     X O O `------'
  [L_FUN] = LAYOUT(
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
      KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18,                                          XXXXXXX,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
       KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,                                            KC_NO, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, KC_NO,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
       KC_F7,  KC_F8,  KC_F9, KC_F10, KC_F11, KC_F12,                                        TO(L_SYM),   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
                            KC_LGUI, KC_ESC, KC_BSPC, KC_TAB, KC_MS_BTN1,         KC_MS_BTN2,  KC_TRNS, KC_SPC, KC_DEL,  KC_LALT,
                                                     KC_WH_L, TO(L_BASE),         KC_WH_R, XXXXXXX, XXXXXXX, XXXXXXX
    ),
  //`------' O O O     O X O `------'
  [L_SYM] = LAYOUT(
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
      KC_TILD, KC_AMPR, KC_PIPE,  KC_DLR, KC_LCBR, KC_RCBR,                                  XXXXXXX,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
      KC_GRV,  KC_HASH, KC_EXLM,  KC_EQL,   KC_LT,   KC_GT,                                    KC_NO, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, KC_NO,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
      KC_NO,   KC_PERC,   KC_AT, KC_CIRC, KC_LBRC, KC_RBRC,                              TO(L_MEDIA),   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
                            KC_LGUI, KC_ESC, KC_BSPC, KC_TAB, KC_MS_BTN1,         KC_MS_BTN2,  KC_ENT, KC_TRNS, KC_DEL,  KC_LALT,
                                                     KC_WH_L, TO(L_BASE),         KC_WH_R, XXXXXXX, XXXXXXX, XXXXXXX
    ),
  //`------' O O O     O O X `------'
  [L_MEDIA] = LAYOUT(
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
      KC_NO,      KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,                                  XXXXXXX,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
      KC_NO,    KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT,  KC_NO,                                    KC_NO, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, KC_NO,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
      KC_NO,      KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,                                TO(L_FUN),   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
                          KC_LGUI, KC_MSTP, KC_MPLY, KC_MUTE, KC_MS_BTN1,         KC_MS_BTN2,  KC_ENT, KC_SPC, KC_TRNS,  KC_LALT,
                                                     KC_VOLD, TO(L_BASE),         KC_VOLU, XXXXXXX, XXXXXXX, XXXXXXX
    ),

// left hand activated
  //`------' O O X     O O O `------'
  [L_NUM] = LAYOUT(
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,      XXXXXXX,                             KC_NO,    KC_7,    KC_8,    KC_9, KC_LPRN, KC_RPRN,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
      KC_NO, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT,        KC_NO,                              KC_0,    KC_1,    KC_2,    KC_3, KC_COLN, KC_BSLS,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    TO(L_NAV),                           KC_PLUS,    KC_4,    KC_5,    KC_6, KC_SLSH, KC_ASTR,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
                           KC_LGUI, KC_ESC, KC_BSPC, KC_TRNS, KC_MS_BTN1,         KC_MS_BTN2,  KC_ENT, KC_SPC, KC_DEL,  KC_LALT,
                                                     KC_LEFT, TO(L_BASE),         KC_RGHT, XXXXXXX, XXXXXXX, XXXXXXX
    ),
  //`------' O X O     O O O `------'
  [L_NAV] = LAYOUT(
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
 A(KC_LEFT), A(KC_RIGHT),   C(KC_W), C(KC_PGUP), C(KC_PGDN), C(S(KC_T)),                      KC_NO, CA(KC_LEFT), CA(KC_UP), CA(KC_DOWN), CA(KC_RGHT), KC_BSPC,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
  C(KC_GRV),     KC_LGUI,   KC_LALT,    KC_LCTL,   KC_LSFT,       KC_F3,                    CW_TOGG,     KC_LEFT,     KC_UP,     KC_DOWN,     KC_RGHT,  KC_APP,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
    KC_TRNS,     C(KC_Z), S(KC_DEL),  C(KC_INS), S(KC_INS),  TO(L_META),                     KC_INS,     KC_HOME,   KC_PGUP,     KC_PGDN,      KC_END, SCRL_MO,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
                            KC_LGUI, KC_ESC, KC_TRNS, KC_TAB, KC_MS_BTN1,         KC_MS_BTN2,  KC_ENT, KC_SPC, KC_DEL,  KC_LALT,
                                                     KC_WH_U, TO(L_BASE),         KC_WH_D, XXXXXXX, XXXXXXX, XXXXXXX
    ),
  //`------' X O O     O O O `------'
  [L_META] = LAYOUT(
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
      QK_BOOT, DB_TOGG,  EE_CLR, XXXXXXX, XXXXXXX,     XXXXXXX,                             SCRL_TO,  CPI_SW, SCRL_SW, ROT_L15,  ROT_R15, XXXXXXX,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
      XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT,     XXXXXXX,                             SCRL_MO, RGB_VAI, RGB_SAI, RGB_HUI,  RGB_MOD, XXXXXXX,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   TO(L_NUM),                             SCRL_IN, RGB_VAD, RGB_SAD, RGB_HUD, RGB_RMOD, XXXXXXX,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
                           KC_LGUI, KC_TRNS, KC_BSPC, KC_TAB, KC_MS_BTN1,         KC_MS_BTN2,  KC_ENT, KC_SPC, KC_DEL, KC_LALT,
                                                 PREV_WINDOW, TO(L_BASE),         NEXT_WINDOW, XXXXXXX, XXXXXXX, XXXXXXX
    ),
  //`------' O O O  X  O O O `------'
  [L_SWITCH] = LAYOUT(
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
                      XXXXXXX, TO(L_META), TO(L_NAV), TO(L_NUM), XXXXXXX,         XXXXXXX, TO(L_FUN), TO(L_SYM), TO(L_MEDIA), XXXXXXX,
                                                        XXXXXXX, KC_TRNS,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
};

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

keyevent_t encoder1_ccw = {
    .key = (keypos_t){.row = 4, .col = 2},
    .pressed = false
};

keyevent_t encoder1_cw = {
    .key = (keypos_t){.row = 4, .col = 5},
    .pressed = false
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            encoder1_cw.pressed = true;
            encoder1_cw.time = (timer_read() | 1);
            action_exec(encoder1_cw);
        } else {
            encoder1_ccw.pressed = true;
            encoder1_ccw.time = (timer_read() | 1);
            action_exec(encoder1_ccw);
        }
    }

    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) { // This will do most of the grunt work with the keycodes.
        case NEXT_WINDOW:
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
        case PREV_WINDOW:
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                register_code(KC_LSFT);
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
                unregister_code(KC_LSFT);
            }
            break;
    }
    return true;
}

void matrix_scan_user(void) {

    if (IS_PRESSED(encoder1_ccw)) {
        encoder1_ccw.pressed = false;
        encoder1_ccw.time = (timer_read() | 1);
        action_exec(encoder1_ccw);
    }

    if (IS_PRESSED(encoder1_cw)) {
        encoder1_cw.pressed = false;
        encoder1_cw.time = (timer_read() | 1);
        action_exec(encoder1_cw);
    }

    if (is_alt_tab_active && timer_elapsed(alt_tab_timer) > 1250) {
        unregister_code(KC_LALT);
        is_alt_tab_active = false;
    }
}



layer_state_t layer_state_set_user(layer_state_t state) {
    int hue_fst = rgblight_get_hue();
    int sat_fst = rgblight_get_sat();
    int val_fst = rgblight_get_val();

    switch (get_highest_layer(state)) {
    case L_FUN:
        rgblight_sethsv_range(HSV_BLUE, 0, 2);
        rgblight_set_effect_range( 2, 10);
        cocot_set_scroll_mode(true);
        break;
    case L_SYM:
        rgblight_sethsv_range(HSV_RED, 0, 2);
        rgblight_set_effect_range( 2, 10);
        cocot_set_scroll_mode(true);
        break;
    case L_MEDIA:
        rgblight_sethsv_range(HSV_WHITE, 0, 2);
        rgblight_set_effect_range( 2, 10);
        cocot_set_scroll_mode(true);
        break;
    case L_NUM:
        rgblight_sethsv_range(HSV_GREEN, 0, 2);
        rgblight_set_effect_range( 2, 10);
        cocot_set_scroll_mode(true);
        break;
    case L_NAV:
        rgblight_sethsv_range(HSV_PURPLE, 0, 2);
        rgblight_set_effect_range( 2, 10);
        break;
    case L_META:
        rgblight_sethsv_range(HSV_CYAN, 0, 2);
        rgblight_set_effect_range( 2, 10);
        cocot_set_scroll_mode(true);
        break;
    default:
        rgblight_sethsv_range(hue_fst, sat_fst, val_fst, 0, 2);
        rgblight_set_effect_range( 0, 12);
        cocot_set_scroll_mode(false);
        break;
    }
    return state;
};


#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    oled_set_brightness(80);
    return OLED_ROTATION_0;
}

void oled_write_layer_state_user(void) {

    oled_write_P(PSTR(" "), false);
    // int cpi = pointing_device_get_cpi();
    int cpi = cpi_array[cocot_config.cpi_idx];
    int scroll_div = scrl_div_array[cocot_config.scrl_div];
    int angle = angle_array[cocot_config.rotation_angle];

    char buf1[5];
    char buf2[3];
    char buf3[4];
    snprintf(buf1, 5, "%4d", cpi);
    snprintf(buf2, 3, "%2d", scroll_div);
    snprintf(buf3, 4, "%3d", angle);

    switch (get_highest_layer(layer_state | default_layer_state)) {
        case 0:
            oled_write_P(PSTR("BASE "), false);
            break;
        case 1:
            oled_write_P(PSTR(" FUN "), false);
            break;
        case 2:
            oled_write_P(PSTR(" SYM "), false);
            break;
        case 3:
            oled_write_P(PSTR("MEDIA"), false);
            break;
        case 4:
            oled_write_P(PSTR(" NUM "), false);
            break;
        case 5:
            oled_write_P(PSTR(" NAV "), false);
            break;
        case 6:
            oled_write_P(PSTR("META "), false);
            break;
        case 7:
            oled_write_P(PSTR("SWTCH"), false);
            break;
        default:
            oled_write_P(PSTR("Undef"), false);
            break;
    }
    oled_write_P(PSTR("/"), false);
    if (cocot_get_scroll_mode()){
        oled_write_P(PSTR("S"), false);
    } else{
        oled_write_P(PSTR("C"), false);
    }
    oled_write_P(PSTR("/"), false);
    oled_write(buf1, false);
    oled_write_P(PSTR("/"), false);
    oled_write(buf2, false);
    oled_write_P(PSTR("/"), false);
    oled_write_ln(buf3, false);
    oled_write_P(PSTR(QMK_VERSION "\n" QMK_BUILDDATE), false);
}

bool oled_task_user(void) {
    oled_write_layer_state_user();
    return false;
}
#endif

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  //debug_enable=true;
  //debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}
