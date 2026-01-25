// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌─────┬─────┬─────┐
     * │ PRV │ PLY │ NXT │
     * ├─────┼─────┼─────┤
     * │  D  │  E  │  F  │
     * ├─────┼─────┼─────┤
     * │  G  │ DBG │ UPG │
     * └─────┴─────┴─────┘
     */
    [0] = LAYOUT_ortho_3x3(
        KC_MPRV, KC_MPLY, KC_MNXT,
        KC_D,    KC_E,    KC_F,
        KC_G,    KC_H,    QK_BOOT
    )
};

#define RAW_EPSIZE 32

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return false;
}

#endif

#ifdef OLED_ENABLE

void render_centered_text(char *text, uint8_t row){
    static char last_text[RAW_EPSIZE] = {0};

    if (strcmp(last_text, text) == 0) {
        return;
    }

    oled_clear();

    strlcpy(last_text, text, sizeof(last_text));

    uint8_t len = strlen(text);
    uint8_t col = (oled_max_chars() - len) / 2;

    oled_set_cursor(col, row);
    oled_write(text, false);
}

void oled_render_boot(bool bootloader) {
    if (bootloader) {
        render_centered_text(PSTR("Awaiting New Firmware"), 1);
    } else {
        render_centered_text(PSTR("Rebooting"), 1);
    }

    oled_render_dirty(true);
}

bool shutdown_user(bool jump_to_bootloader) {
    oled_render_boot(jump_to_bootloader);
    return false;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180; 
}

bool oled_task_user(void) {
    render_centered_text(PSTR("Display OK"), 1);
    return false;
}

#endif