#include "./process_alt_tab.h"

static uint16_t atab_timer;
static bool atab_active = false;
static deferred_token atab_deferred_token;

#define ALT_TAB_TERM 100

uint32_t atab_callback(uint32_t trigger_time, void *cb_arg) {
    if (atab_active && timer_elapsed(atab_timer) > TAPPING_TERM + ALT_TAB_TERM) {
        unregister_code(KC_LALT); // Release Alt
        atab_active = false;
    }
    return 0; // Do not repeat
}

bool process_alt_tab(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ATAB:
            if (record->event.pressed) {
                if (!atab_active) {
                    register_code(KC_LALT); // Press Alt
                    atab_active = true;
                }
                tap_code(KC_TAB); // Press and release Tab
                atab_timer = timer_read();

                // Cancel the previous deferred execution if it exists
                if (atab_deferred_token != INVALID_DEFERRED_TOKEN) {
                    cancel_deferred_exec(atab_deferred_token);
                }

                // Schedule deferred execution
                atab_deferred_token = defer_exec(TAPPING_TERM + 10, atab_callback, NULL);
            }
            return false; // Skip all further processing of this key
    }
    return true; // Process all other keys normally
}