#include "process_rawhid_mod.h"

bool raw_modifying = false;
uint8_t response_data[32] = {0};
static uint16_t ft_raw_mod_timer;

bool process_rawhid_mod(uint16_t keycode, keyrecord_t *record) {
    write_log_format(LOG_LEVEL_DEBUG, "\nprocess_rawhid_mod in\n");

    if (keycode == FT_RAW_MOD) {
        if (record->event.pressed) {
            ft_raw_mod_timer = timer_read();
        } else {
            if (timer_elapsed(ft_raw_mod_timer) < TAPPING_TERM) {
                write_log_format(LOG_LEVEL_DEBUG, "process_rawhid_mod out: tap raw modifier\n");
                return true; // Process FT_RAW_MOD as a regular keypress
            } else {
                raw_modifying = false; // Release the raw_modifying mode when the key is released after holding
            }
        }
        write_log_format(LOG_LEVEL_DEBUG, "process_rawhid_mod out: raw modifier pressed or released\n");
        return false; // Don't process FT_RAW_MOD any further
    }

    // If raw_modifying is true and the keycode is a layer toggle
    if (raw_modifying && IS_LAYER_TOGGLE(keycode)) {
        // Use QMK's timer feature to differentiate between tap and hold
        static uint16_t layer_key_timer;

        if (record->event.pressed) {
            layer_key_timer = timer_read();
            write_log_format(LOG_LEVEL_DEBUG, "process_rawhid_mod out: listening for layer key tap or hold\n");
            return false; // Don't process the key further here, wait to decide between tap or hold
        } else {
            if (timer_elapsed(layer_key_timer) < TAPPING_TERM) {
                // Key was tapped
                convert_keycode_to_raw_hid(keycode, true, response_data);

                write_log_format(LOG_LEVEL_INFO, "Sending Raw Data: [%02X, %02X, %02X]\n", response_data[0], response_data[1], response_data[2]);
                raw_hid_send(response_data, 32);
                write_log_format(LOG_LEVEL_DEBUG, "process_rawhid_mod out: sent raw layer key tap info\n");
                return false; // Don't process this key as a regular keypress
            } else {
                // Key was held, the layer switch will be handled by QMK's default process
                write_log_format(LOG_LEVEL_DEBUG, "process_rawhid_mod out: layer switch key\n");
                return true;
            }
        }
    }

    // Process raw HID functionality for other keys
    if (raw_modifying) {
        if (record->event.pressed) {
            convert_keycode_to_raw_hid(keycode, true, response_data);
        } else {
            convert_keycode_to_raw_hid(keycode, false, response_data);
        }
        write_log_format(LOG_LEVEL_INFO, "Sending Raw Data: [%02X, %02X, %02X]\n", response_data[0], response_data[1], response_data[2]);
        raw_hid_send(response_data, 32);
        write_log_format(LOG_LEVEL_DEBUG, "process_rawhid_mod out: sent raw key info\n");
        return false; // Don't process this key further
    }

    write_log_format(LOG_LEVEL_DEBUG, "process_rawhid_mod out: not raw modifying\n");
    return true; // Process other keycodes normally
}

// Define constants for ping request and pong response
#define PING_REQUEST 0x01
#define PONG_RESPONSE 0x02

void raw_hid_receive(uint8_t *data, uint8_t length) {
    if (length > 0) {
        write_log_format(LOG_LEVEL_INFO, "Received Raw Data: [%02X, %02X, %02X]\n", data[0], data[1], data[2]);

        // Check if the received data is a ping request
        if (data[0] == PING_REQUEST) {
            ergodox_right_led_1_on();
            // Respond with a pong
            response_data[0] = PONG_RESPONSE;
            for (int i = 1; i < 32; i++) {
                response_data[i] = 0; // Clear the rest of the response data
            }
        } else {
            // Echo the data back
            response_data[0] = data[0];
            response_data[1] = data[1];
        }

        write_log_format(LOG_LEVEL_INFO, "Sending Raw Response: [%02X, %02X, %02X]\n", response_data[0], response_data[1], response_data[2]);
        raw_hid_send(response_data, 32);

        if (data[0] == PING_REQUEST) {
            ergodox_right_led_1_off();
        }
    } else {
        write_log_format(LOG_LEVEL_WARN, "Data length less than expected.\n");
    }
}
