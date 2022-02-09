#include QMK_KEYBOARD_H

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        tap_code(KC_VOLU);
    } else {
        tap_code(KC_VOLD);
    }
    return true;
}

#ifdef VIA_ENABLE
    #define USER_START USER00
#else
    #define USER_START SAFE_RANGE
#endif

enum custom_keycodes {
    KC_MISSION_CONTROL = USER_START,
    KC_LAUNCHPAD,
};

#define KC_MCTL KC_MISSION_CONTROL
#define KC_LPAD KC_LAUNCHPAD


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_MCTL:
            if (record->event.pressed) {
                host_consumer_send(0x29F);
            } else {
                host_consumer_send(0);
            }
            return false;  // Skip all further processing of this key
        case KC_LPAD:
            if (record->event.pressed) {
                host_consumer_send(0x2A0);
            } else {
                host_consumer_send(0);
            }
            return false;  // Skip all further processing of this key
        default:
            return true;  // Process all other keycodes normally
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
        KC_ESC,  KC_F1,    KC_F2,   KC_F3,        KC_F4,      KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_MUTE,
        KC_GRV,  KC_1,     KC_2,    KC_3,         KC_4,       KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_HOME,
        KC_TAB,  KC_Q,     KC_W,    KC_E,         KC_R,       KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_PGUP,
        KC_LSFT, KC_A,     KC_S,    KC_D,         KC_F,       KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,  KC_PGDN,
        KC_LSFT, KC_NUBS,  KC_Z,    KC_X,         KC_C,       KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI,  KC_LALT, KC_SPC,                                                       KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),

	[1] = LAYOUT(
        KC_TRNS, KC_BRID,  KC_BRIU, LGUI(KC_TAB), LGUI(KC_E), RGB_VAD, RGB_VAI, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, KC_TRNS, KC_TRNS,
        KC_TRNS, DF(0),    DF(2),   KC_TRNS,      KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET,   KC_TRNS,
        RGB_TOG, RGB_MOD,  RGB_VAI, RGB_HUI,      RGB_SAI,    RGB_SPI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
        KC_TRNS, RGB_RMOD, RGB_VAD, RGB_HUD,      RGB_SAD,    RGB_SPD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,      KC_TRNS,    KC_TRNS, KC_TRNS, NK_ON,   NK_OFF,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_TRNS,
        KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,                                                      KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_END),

	[2] = LAYOUT(
        KC_ESC,  KC_F1,    KC_F2,   KC_F3,        KC_F4,      KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_MUTE,
        KC_NUBS, KC_1,     KC_2,    KC_3,         KC_4,       KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_HOME,
        KC_TAB,  KC_Q,     KC_W,    KC_E,         KC_R,       KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_PGUP,
        KC_LSFT, KC_A,     KC_S,    KC_D,         KC_F,       KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_BSLS, KC_ENT,  KC_PGDN,
        KC_LSFT, KC_GRV,   KC_Z,    KC_X,         KC_C,       KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LALT,  KC_LGUI, KC_SPC,                                                       KC_RGUI, MO(3),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),

	[3] = LAYOUT(
        KC_TRNS, KC_BRID,  KC_BRIU, KC_MCTL,      KC_LPAD,    RGB_VAD, RGB_VAI, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, KC_TRNS, KC_TRNS,
        KC_TRNS, DF(0),    DF(2),   KC_TRNS,      KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET,   KC_TRNS,
        RGB_TOG, RGB_MOD,  RGB_VAI, RGB_HUI,      RGB_SAI,    RGB_SPI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
        KC_TRNS, RGB_RMOD, RGB_VAD, RGB_HUD,      RGB_SAD,    RGB_SPD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,      KC_TRNS,    KC_TRNS, KC_TRNS, NK_ON,   NK_OFF,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_TRNS,
        KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,                                                      KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_END)
};


