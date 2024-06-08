#include "process_mod_keys.h"

static uint16_t registered_keycode = KC_NO; // Static variable to keep track of the registered keycode
static uint16_t active_layer = UINT16_MAX;

bool is_layer_key(uint16_t keycode) {
    // Check if the keycode is within the range of known layer keycodes
    return (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) || 
           (keycode >= QK_MOMENTARY && keycode <= QK_MOMENTARY_MAX) ||
           (keycode >= QK_TO && keycode <= QK_TO_MAX) ||
           (keycode >= QK_TOGGLE_LAYER && keycode <= QK_TOGGLE_LAYER_MAX) ||
           (keycode >= QK_ONE_SHOT_LAYER && keycode <= QK_ONE_SHOT_LAYER_MAX) ||
           (keycode >= QK_LAYER_MOD && keycode <= QK_LAYER_MOD_MAX);
}

bool process_mod_keys(uint16_t keycode, keyrecord_t *record) {
    write_log_format(LOG_LEVEL_DEBUG, "\nprocess_mod_keys in\n");// Log the entry into the function );
    // Check if the key is a modifier or a layer key
    if (IS_MODIFIER_KEYCODE(keycode) || is_layer_key(keycode)) {
        if (IS_QK_LAYER_TAP(keycode)) {
            active_layer = QK_LAYER_TAP_GET_LAYER(keycode);
        }
        write_log_format(LOG_LEVEL_DEBUG, "process_mod_keys out: key is a modifier or layer key\n");
        return true; // If it's a modifier or layer key, just return true
    }

    // Check if the key is pressed
    if (record->event.pressed) {
        const uint8_t mods = get_mods(); // Get the current modifiers
        
        write_log_format(LOG_LEVEL_DEBUG, "Mods: 0x%02X\n", mods);
        
#ifndef NO_ACTION_ONESHOT
        uint8_t mod_masks = mods | get_weak_mods() | get_oneshot_mods(); // Combine modifiers with weak and oneshot mods
        write_log_format(LOG_LEVEL_DEBUG, "Mods with weak and oneshot: 0x%02X\n", mod_masks);
#else //NO_ACTION_ONESHOT
        uint8_t mod_masks = mods; // Only use the current modifiers
        write_log_format(LOG_LEVEL_DEBUG, "Mods: 0x%02X\n", mod_masks);
#endif //NO_ACTION_ONESHOT

        // If there are any active modifiers
        if (mod_masks) {
            // Iterate through custom mod keys to check for matches
            for (int i = 0; i < NUM_CUSTOM_MOD_KEYS; ++i) {
                // If the keycode matches a custom mod key
                if (keycode == custom_mod_keys[i].keycode) {
                    keypos_t modifier_keypos = {.col = custom_mod_keys[i].modifier & 0xF, .row = custom_mod_keys[i].modifier >> 4}; // Get key position of the modifier
                    uint16_t modifier_keycode = keymap_key_to_keycode(0, modifier_keypos); // Get the keycode of the modifier

                    uint8_t mod_bit = MOD_BIT(custom_mod_keys[i].modifier); // Get the modifier bit
                    bool is_mod_active = (mod_masks & mod_bit) || (modifier_keycode != KC_NO && (get_mods() & (1 << (modifier_keycode - KC_LCTL)))); // Check if the modifier is active
                    if (is_mod_active) { // If the defined key modifier is active        
                        registered_keycode = custom_mod_keys[i].mod_keycode; // Register the custom mod key
                        write_log_format(LOG_LEVEL_INFO, "Match found, registering keycode: 0x%04X\n", registered_keycode);

                        // If the registered keycode has modifiers and the mod bit matches
                        if (IS_QK_MODS(registered_keycode) && (QK_MODS_GET_MODS(registered_keycode) & mod_bit) != 0) {
                            write_log_format(LOG_LEVEL_DEBUG, "Registering keycode with mod: 0x%04X\n", registered_keycode);
                            register_code16(registered_keycode); // Register the keycode
                        } else {
                            // If it's a modifier keycode, remove weak and oneshot mods and unregister mods
                            if (IS_MODIFIER_KEYCODE(custom_mod_keys[i].modifier)) {
                                write_log_format(LOG_LEVEL_DEBUG, "Removing weak and oneshot mods for: 0x%02X\n", mod_bit);
                                del_weak_mods(mod_bit);
#ifndef NO_ACTION_ONESHOT
                                del_oneshot_mods(mod_bit);
#endif
                                unregister_mods(mod_bit);
                            } else {
                                write_log_format(LOG_LEVEL_DEBUG, "Unregistering modifier keycode: 0x%04X\n", custom_mod_keys[i].modifier);
                                unregister_code(custom_mod_keys[i].modifier); // Unregister the modifier keycode
                            }
                            register_code16(registered_keycode); // Register the custom mod key
                            write_log_format(LOG_LEVEL_DEBUG, "Registering custom mod key and restoring mods: 0x%04X\n", registered_keycode);
                            set_mods(mods); // Restore the modifiers
                        }
                            write_log_format(LOG_LEVEL_DEBUG, "process_mod_keys out: key modified\n");
                        return false; // Return false as the key has been handled
                    }
                    write_log_format(LOG_LEVEL_DEBUG, "defined key modifier not active\n");
                }
            }
            write_log_format(LOG_LEVEL_DEBUG, "process_mod_keys out: key not in mod keys\n");
            return true; // Return true if no matching custom mod key was found
        }
        write_log_format(LOG_LEVEL_DEBUG, "process_mod_keys out: unmodified key\n");
        return true; // Return true if no modifiers are active
    }

    // If the key is released
    if (registered_keycode != KC_NO) {
        write_log_format(LOG_LEVEL_DEBUG, "Unregistering previous keycode: 0x%04X\n", registered_keycode);
        unregister_code16(registered_keycode); // Unregister the previously registered keycode
        registered_keycode = KC_NO; // Reset the registered keycode
        write_log_format(LOG_LEVEL_DEBUG, "process_mod_keys out: registered key release\n");
        return false; // Return false as the key release has been handled
    }

    write_log_format(LOG_LEVEL_DEBUG, "process_mod_keys out: key release keycode: 0x%04X\n", keycode);
    return true; // Return true for other key releases
}
