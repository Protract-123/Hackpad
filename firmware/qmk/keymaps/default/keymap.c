// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keymap.h"
#include "print.h"

#ifdef RAW_ENABLE
    static char active_app[RAW_EPSIZE] = {0};
    static uint32_t last_app_update = 0;

    static uint8_t current_app_layer = _BASE;

    static uint8_t host_volume = 0;        // 0–100
    static bool host_volume_valid = false;
    static uint32_t last_volume_update = 0;
#endif


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
    [_BASE] = LAYOUT_ortho_3x3(
        KC_MPRV, KC_MPLY, KC_MNXT,
        KC_D,    KC_E,    KC_F,
        KC_G,    KC_H,    QK_BOOT
    ),
    [_CODE] = LAYOUT_ortho_3x3(
        KC_MPRV, KC_MPLY, KC_MNXT,
        KC_L,    KC_M,    KC_F,
        KC_G,    KC_H,    QK_BOOT

    ),
    [_BROWSER] = LAYOUT_ortho_3x3(
        KC_MPRV, KC_MPLY, KC_MNXT,
        KC_L,    KC_M,    KC_F,
        KC_G,    KC_H,    QK_BOOT
    ),
    [_TERMINAL] = LAYOUT_ortho_3x3(
        KC_MPRV, KC_MPLY, KC_MNXT,
        KC_L,    KC_M,    KC_F,
        KC_G,    KC_H,    QK_BOOT
    )
};


#ifdef ENCODER_ENABLE
    bool encoder_update_user(uint8_t index, bool clockwise) {
        if (index == 0) {
            tap_code(clockwise ? KC_VOLD : KC_VOLU);
        }
        return false;
    }
#endif


#ifdef OLED_ENABLE

void render_centered_text(char *text, uint8_t row) {
    static char last_text[32] = {0};

    if (strcmp(last_text, text) == 0) {
        return;
    }
    strlcpy(last_text, text, sizeof(last_text));

    oled_clear();

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

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

bool shutdown_user(bool jump_to_bootloader) {
    oled_render_boot(jump_to_bootloader);
    return false;
}

bool oled_task_user(void) {
    #ifdef RAW_ENABLE
        if (host_volume_valid &&
            timer_elapsed32(last_volume_update) < VOLUME_DISPLAY_TIMEOUT) {

            char buf[8];
            snprintf(buf, sizeof(buf), "VOL %3u", host_volume);
            // printf("%s\n", buf);
            
            render_centered_text(buf, 1);
            return false;
        }

        if (active_app[0] != '\0' &&
            timer_elapsed32(last_app_update) < APP_TIMEOUT) {
            // printf("Active App: %s\n", active_app);
            render_centered_text(active_app, 1);
            return false;
        }

        if (timer_elapsed32(last_app_update) > APP_TIMEOUT) {
            switch_to_layer(_BASE);
        }
    #endif

    render_centered_text(PSTR("Display OK"), 1);
    return false;
}

#endif


#ifdef RAW_ENABLE

void raw_hid_receive(uint8_t *data, uint8_t length) {
    if (length < 4) {
        return;
    }

    if (data[0] != HID_MAGIC_0 ||
        data[1] != HID_MAGIC_1 ||
        data[2] != HID_MAGIC_2) {
        return;
    }

    payload_type_t type = data[3];

    switch (type) {
        case PAYLOAD_UNKNOWN:
            break;

        case PAYLOAD_ACTIVE_WINDOW:
            handle_active_window_payload(data + 4, length - 4);
            break;

        case PAYLOAD_VOLUME:
            handle_volume_payload(data + 4, length - 4);
            break;

        default:
            break;
    }
}

static void handle_volume_payload(const uint8_t *data, uint8_t length) {
    if (length == 0) {
        return;
    }

    char buf[5];
    uint8_t copy_len = length;

    if (copy_len >= sizeof(buf)) {
        copy_len = sizeof(buf) - 1;
    }

    memcpy(buf, data, copy_len);
    buf[copy_len] = '\0';

    int vol = atoi(buf);

    // Validate range
    if (vol < 0 || vol > 100) {
        host_volume_valid = false;
        return;
    }

    if (!host_volume_valid || host_volume != (uint8_t)vol) {
        host_volume = (uint8_t)vol;
        host_volume_valid = true;
        last_volume_update = timer_read32();
    }
}

static void handle_active_window_payload(
    const uint8_t *data,
    uint8_t length
) {
    if (length == 0) {
        return;
    }

    uint8_t copy_len = length;

    if (copy_len >= RAW_EPSIZE) {
        copy_len = RAW_EPSIZE - 1;
    }

    memcpy(active_app, data, copy_len);
    active_app[copy_len] = '\0';

    uint8_t new_layer = app_name_to_layer(active_app);
    switch_to_layer(new_layer);

    last_app_update = timer_read32();
}

void switch_to_layer(uint8_t new_layer) {
    if (current_app_layer == new_layer) {
        return;
    }

    current_app_layer = new_layer;
    layer_move(current_app_layer);
}

uint8_t app_name_to_layer(const char *app) {
    if (strcmp(app, "Code") == 0) {
        return _CODE;
    }
    if (strcmp(app, "Safari") == 0) {
        return _BROWSER;
    }
    if (strcmp(app, "Terminal") == 0) {
        return _TERMINAL;
    }

    return _BASE;
}

#endif
