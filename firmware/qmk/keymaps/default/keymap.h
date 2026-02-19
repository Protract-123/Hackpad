// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include QMK_KEYBOARD_H

#ifdef RAW_ENABLE
    #define RAW_EPSIZE   32
    #define APP_TIMEOUT 10000 // 10 seconds 
    #define VOLUME_DISPLAY_TIMEOUT 4000  // 4 seconds

    #define HID_MAGIC_0 0x10
    #define HID_MAGIC_1 0xFF
    #define HID_MAGIC_2 0x5B
#endif

enum layers {
    _BASE,
    _CODE,
    _BROWSER,
    _TERMINAL,
};

typedef enum {
    PAYLOAD_UNKNOWN = 0,
    PAYLOAD_ACTIVE_WINDOW,
    PAYLOAD_VOLUME
} payload_type_t;


#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise);
#endif

#ifdef OLED_ENABLE
void render_centered_text(char *text, uint8_t row);
void oled_render_boot(bool bootloader);
oled_rotation_t oled_init_user(oled_rotation_t rotation);
bool shutdown_user(bool jump_to_bootloader);
bool oled_task_user(void);
#endif

#ifdef RAW_ENABLE
void raw_hid_receive(uint8_t *data, uint8_t length);

void switch_to_layer(uint8_t new_layer);
uint8_t app_name_to_layer(const char *app);

static void handle_active_window_payload(const uint8_t *data, uint8_t length);
static void handle_volume_payload(const uint8_t *data, uint8_t length);
#endif
