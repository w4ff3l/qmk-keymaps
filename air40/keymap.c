/*
 * Copyright 2023
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
#include "keymap.h"

enum custom_keycodes {
    RAISE = SAFE_RANGE,
    LOWER
};

enum layer_name {
    _BASE_COLEMAK_DH,
    _LOWER,
    _RAISE,
    _SPEC
};

void custom_mod_t(bool pressed, uint16_t key, char key_tap);
void update_layer_state(bool pressed, enum layer_name layer);


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base layer (Colemak-DH)
     *                  ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
     * Tap for 'Esc' -- | esc │  Q  │  W  │  F  │  P  │  B  │  J  │  L  │  U  │  Y  │  ;  │  '  │
     *                  ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     *                  │ tab │  A  │  R  │  S  │  T  │  G  │  M  │  N  │  E  │  I  │  O  │ ent │
     *                  ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     * Tap for  '('  -- │  ⇧  │  Z  │  X  │  C  │  D  │  V  │  K  │  H  │  ,  │  .  │  /  │  ⇧  │ -- Tap for ')'
     *                  ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
     *                  │  [  │ Hyp │ Alt │ GUI │  ↓  │   Space   │  ↑  │ GUI │ Alt │ Hyp │  ]  │
     *                  └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
     *                          /                           /                         /
     * Hold for Shift ---------/---------------------------'                         /
     *                        /                                                     /
     * Tap for '{' and '}' --'-----------------------------------------------------'
     */
    [_BASE_COLEMAK_DH] = LAYOUT_ortho_4x12_1x2uC(
        KC_ESC,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_QUOT,
        CTL_TAB, LGUI__A, KC_R,    LALT__S, LCTL__T, RALT__G, RALT__M, RCTL__N, RALT__E, KC_I,    RGUI__O, CTL_ENT,
        SC_LSPO, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, SC_RSPC,
        KC_LBRC, KC_LCBR, KC_LALT, KC_LGUI, LOWER,       SP_SHF,       RAISE,   KC_RGUI, KC_RALT, KC_RCBR, KC_RBRC
        ),

    /* Number layer
     *                  ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
     *                  |     │ F1  │ F2  │ F3  │ F4  │ F5  │ F6  │ F7  │ F8  │ F9  │ F10 │     │
     *                  ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     *                  │     │  1  │  2  │  3  │  4  │  5  │  6  │  7  │  8  │  9  │  0  │     │
     *                  ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     *                  │     │  -  │  =  │  `  │  \  │  :  │ nda │ mda │  ,  │  .  │  /  │     │
     *                  ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
     *                  │     │     │     │     │  ↓  │ Backspace │  ↑  │     │     │     │     │
     *                  └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
     */
    [_LOWER] = LAYOUT_ortho_4x12_1x2uC(
        _______, KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
        _______, LGUI__1, KC_2,     LALT__3, LCTL__4, RALT__5, RALT__6, RCTL__7, RALT__8, KC_9,    RGUI__0, _______,
        _______, KC_MINS, KC_EQUAL, KC_GRV,  KC_BSLS, KC_COLN, _______, _______, KC_COMM, KC_DOT,  KC_SLSH, _______,
        _______, _______, _______,  _______, _______,     KC_BSPC,      _______, _______, _______, _______, _______
        ),

    /* Symbol layer
     *                  ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
     *                  |     │ F11 │ F12 │ F13 │ F14 │ F15 │ F16 │ F17 │ F18 │ F19 │ F20 │     │
     *                  ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     *                  │     │  !  │  @  │  #  │  $  │  %  │  ^  │  &  │  *  │  '  │  "  │     │
     *                  ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     *                  │     │  _  │  +  │  ~  │  |  │  :  │ nda │ mda │  ,  │  .  │  /  │     │
     *                  ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
     *                  │     │     │     │     │  ↓  │   Delete  │  ↑  │     │     │     │     │
     *                  └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
     */
    [_RAISE] = LAYOUT_ortho_4x12_1x2uC(
        _______, KC_F11,  KC_F12,  KC_F13,  KC_F14,    KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  _______,
        _______, KC_EXLM, KC_AT,   KC_HASH, KC_DOLLAR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_QUOT, KC_DQUO, _______,
        _______, KC_UNDS, KC_PLUS, KC_TILD, KC_PIPE,   KC_COLN, _______, _______, KC_COMM, KC_DOT,  KC_SLSH, _______,
        _______, _______, _______, _______, _______,       KC_DELETE,    _______, _______, _______, _______, _______
        ),

    /* Special layer */
    [_SPEC] = LAYOUT_ortho_4x12_1x2uC(
        _______, QK_BOOT, DB_TOGG, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI,  RGB_VAD, KC_DEL,
        _______, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, _______, _______, KC_LEFT, KC_DOWN,   KC_UP, KC_RIGHT, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,
        _______, _______, _______, _______, _______,      _______,     _______, _______, _______,  _______, _______
        )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LOWER:
            update_layer_state(record->event.pressed, _LOWER);
            return false;
        case RAISE:
            update_layer_state(record->event.pressed, _RAISE);
            return false;
        default:
            break;
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgb_matrix_sethsv(0, 255, 200);
    switch (get_highest_layer(state)) {
        case _LOWER:
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_left_column_glow);
            break;
        case _RAISE:
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_right_column_glow);
            break;
        case _SPEC:
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_top_row_glow);
            break;
        default:
            rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
            break;
    }
    return state;
}

void custom_mod_t(bool pressed, uint16_t key, char key_tap) {
    char key_tap_arr[2] = {key_tap, '\0'};
    static uint16_t timer;
    if(pressed) {
        timer = timer_read();
        register_code(key); // Change the key to be held here
    } else {
        unregister_code(key); // Change the key that was held here, too!
        if (timer_elapsed(timer) < TAPPING_TERM) {
            send_string_with_delay(key_tap_arr, 0);
        }
    }
}

void update_layer_state(bool pressed, enum layer_name layer) {
    if (pressed) {
        layer_on(layer);
    } else {
        layer_off(layer);
    }
    update_tri_layer(_LOWER, _RAISE, _SPEC);
}

void keyboard_post_init_user(void) {
    rgb_matrix_sethsv(0, 255, 200);
    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
}
