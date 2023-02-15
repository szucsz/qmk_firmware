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


// Defines names for use in layer keycodes and the keymap
enum layer_number {
    L_BASE   = 0,
    L_FUN    = 1,
    L_SYM    = 2,
    L_MEDIA  = 3,
    L_NUM    = 4,
    L_NAV    = 5,
    L_META   = 6
};

// opposite layers
#define LO_FUN    L_NUM
#define LO_SYM    L_NAV
#define LO_MEDIA  L_META
#define LO_NUM    L_FUN
#define LO_NAV    L_SYM
#define LO_META   L_MEDIA

#define SYM(k)    LT(L_SYM,k)
#define NUM(k)    LT(L_NUM,k)
#define FUN(k)    LT(L_FUN,k)
#define META(k)   LT(L_META,k)
#define NAV(k)    LT(L_NAV,k)
#define MEDIA(k)  LT(L_MEDIA,k)

#define HMSHFT(k) MT(MOD_LSFT,k)
#define HMCTL(k)  MT(MOD_LCTL,k)
#define HMGUI(k)  MT(MOD_LGUI,k)
#define HMALT(k)  MT(MOD_LALT,k)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [L_BASE] = LAYOUT(
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
       KC_ESC,       KC_Q,       KC_W,       KC_E,        KC_R,   KC_T,                 KC_Y,        KC_U,       KC_I,       KC_O,          KC_P, KC_BSPC,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
      KC_LCTL,HMGUI(KC_A),HMALT(KC_S),HMCTL(KC_D),HMSHFT(KC_F),   KC_G,                 KC_H,HMSHFT(KC_J),HMCTL(KC_K),HMALT(KC_L),HMGUI(KC_SCLN), KC_QUOT,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
      KC_LSFT,       KC_Z,       KC_X,       KC_C,        KC_V,   KC_B,                 KC_N,        KC_M,    KC_COMM,     KC_DOT,       KC_SLSH, KC_MINS,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
            KC_LGUI, META(KC_ESC), NAV(KC_BSPC), NUM(KC_TAB), KC_MS_BTN1,        KC_MS_BTN2,  FUN(KC_ENT),  SYM(KC_SPC), MEDIA(KC_DEL), KC_ESC,
                                                      KC_WH_U, KC_MS_BTN3,        KC_WH_D, XXXXXXX, XXXXXXX, XXXXXXX
                               //`------------------------------------' O O O  O O O `------------------------------------'
    ),

// right hand activated layers
  [L_FUN] = LAYOUT(
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
      KC_NO,  KC_F9, KC_F10, KC_F11, KC_F12, KC_NO,                                       TO(L_BASE),   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
      KC_NO,  KC_F5,  KC_F6,  KC_F7,  KC_F8, KC_NO,                                            KC_NO, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, KC_NO,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
      KC_NO,  KC_F1,  KC_F2,  KC_F3,  KC_F4, KC_NO,                                       TO(LO_FUN),   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
                            KC_LGUI, KC_ESC, KC_BSPC, KC_TAB, KC_MS_BTN1,         KC_MS_BTN2,  KC_TRNS, KC_SPC, KC_DEL,  KC_ESC,
                                                     KC_WH_L, KC_MS_BTN3,         KC_WH_R, XXXXXXX, XXXXXXX, XXXXXXX
                               //`------------------------------------' O O O  X O O `------------------------------------'
    ),
  [L_SYM] = LAYOUT(
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
      KC_TILD, KC_AMPR, KC_PIPE,  KC_DLR, KC_LCBR, KC_RCBR,                               TO(L_BASE),   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
      KC_GRV,  KC_HASH, KC_EXLM,  KC_EQL,   KC_LT,   KC_GT,                                    KC_NO, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, KC_NO,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
      KC_NO,   KC_PERC,   KC_AT, KC_CIRC, KC_LBRC, KC_RBRC,                               TO(LO_SYM),   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
                            KC_LGUI, KC_ESC, KC_BSPC, KC_TAB, KC_MS_BTN1,         KC_MS_BTN2,  KC_ENT, KC_TRNS, KC_DEL,  KC_ESC,
                                                     KC_WH_L, KC_MS_BTN3,         KC_WH_R, XXXXXXX, XXXXXXX, XXXXXXX
                               //`------------------------------------' O O O  O X O `------------------------------------'
    ),
  [L_MEDIA] = LAYOUT(
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
      G(A(KC_K)), KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,                               TO(L_BASE),   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
      KC_NO,    KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT,  KC_NO,                                    KC_NO, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, KC_NO,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
      KC_NO,      KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,                             TO(LO_MEDIA),   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
                          KC_LGUI, KC_MSTP, KC_MPLY, KC_MUTE, KC_MS_BTN1,         KC_MS_BTN2,  KC_ENT, KC_SPC, KC_TRNS, KC_F13,
                                                     KC_VOLD, KC_MS_BTN3,         KC_VOLU, XXXXXXX, XXXXXXX, XXXXXXX
                               //`------------------------------------' O O O  O O X `------------------------------------'
    ),

// left hand activated
  [L_NUM] = LAYOUT(
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   TO(L_BASE),                             KC_NO,    KC_7,    KC_8,    KC_9, KC_LPRN, KC_RPRN,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
      KC_NO, KC_RGUI, KC_RALT, KC_RCTL, KC_RSFT,        KC_NO,                              KC_0,    KC_4,    KC_5,    KC_6, KC_COLN, KC_BSLS,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   TO(LO_NUM),                           KC_PLUS,    KC_1,    KC_2,    KC_3, KC_SLSH, KC_ASTR,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
                           KC_LGUI, KC_ESC, KC_BSPC, KC_TRNS, KC_MS_BTN1,         KC_MS_BTN2,  KC_ENT, KC_SPC, KC_DEL,  KC_ESC,
                                                     KC_WH_L, KC_MS_BTN3,         KC_WH_R, XXXXXXX, XXXXXXX, XXXXXXX
                               //`------------------------------------' O O X  O O O `------------------------------------'
    ),
  [L_NAV] = LAYOUT(
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
      KC_NO,   KC_NO,     KC_NO,     KC_NO,     KC_NO, TO(L_BASE),                       C(KC_Y), S(KC_INS), C(KC_INS), S(KC_DEL), C(KC_Z),  KC_NO,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
      KC_NO, KC_RGUI,   KC_RALT,   KC_RCTL,   KC_RSFT,      KC_NO,                       CW_TOGG,   KC_LEFT,     KC_UP,   KC_DOWN, KC_RGHT, KC_APP,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
      KC_NO,   KC_NO, S(KC_DEL), C(KC_INS), S(KC_INS), TO(LO_NAV),                        KC_INS,   KC_HOME,   KC_PGUP,   KC_PGDN,  KC_END,  KC_NO,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
                            KC_LGUI, KC_ESC, KC_TRNS, KC_TAB, KC_MS_BTN1,         KC_MS_BTN2,  KC_ENT, KC_SPC, KC_DEL,  KC_ESC,
                                                     KC_WH_L, KC_MS_BTN3,         KC_WH_R, XXXXXXX, XXXXXXX, XXXXXXX
                               //`------------------------------------' O X O  O O O `------------------------------------'
    ),
  [L_META] = LAYOUT(
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
      QK_BOOT, DB_TOGG,  EE_CLR, XXXXXXX, XXXXXXX, TO(L_BASE),                             SCRL_TO,  CPI_SW, SCRL_SW, ROT_L15,  ROT_R15, XXXXXXX,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
      XXXXXXX, KC_RGUI, KC_RALT, KC_RCTL, KC_RSFT,    XXXXXXX,                             SCRL_MO, RGB_VAI, RGB_SAI, RGB_HUI,  RGB_MOD, XXXXXXX,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TO(LO_META),                            SCRL_IN, RGB_VAD, RGB_SAD, RGB_HUD, RGB_RMOD, XXXXXXX,
  //|------------------------------------------------------------------|            |------------------------------------------------------------------------|
                           KC_LGUI, KC_TRNS, KC_BSPC, KC_TAB, KC_MS_BTN1,         KC_MS_BTN2,  KC_ENT, KC_SPC, KC_DEL, KC_ESC,
                                                     KC_WH_L, KC_MS_BTN3,         KC_WH_R, XXXXXXX, XXXXXXX, XXXXXXX
                               //`------------------------------------' X O O  O O O `------------------------------------'
    )
};

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
        cocot_set_scroll_mode(true);
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
    oled_set_brightness(100);
    return OLED_ROTATION_0;
}

bool oled_task_user(void) {
    render_logo();
    oled_write_layer_state();
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
