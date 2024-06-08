#include "process_leader_hash.h"

bool process_leader_hash(uint16_t keycode, keyrecord_t *record) {
    write_log_format(LOG_LEVEL_DEBUG, "\nprocess_leader_hash in\n");

    if (record->event.pressed) {
        if (leader_hash_active() && !leader_hash_timed_out()) {
            write_log_format(LOG_LEVEL_DEBUG, "Leader hash is active and not timed out\n");

#ifndef LEADER_HASH_STRICT_KEY_PROCESSING
            if (IS_QK_MOD_TAP(keycode)) {
                keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
                write_log_format(LOG_LEVEL_INFO, "Modified keycode (MOD_TAP): 0x%04X\n", keycode);
            } else if (IS_QK_LAYER_TAP(keycode)) {
                keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
                write_log_format(LOG_LEVEL_INFO, "Modified keycode (LAYER_TAP): 0x%04X\n", keycode);
            }
#endif //LEADER_HASH_STRICT_KEY_PROCESSING

            if (!leader_hash_add(keycode)) {
                write_log_format(LOG_LEVEL_WARN, "Failed to add keycode to leader hash, ending leader hash\n");
                leader_hash_end();
                write_log_format(LOG_LEVEL_DEBUG, "process_leader_hash out: warn could not add key\n");
                return true;
            }

#ifdef LEADER_HASH_PER_KEY_TIMING
            write_log_format(LOG_LEVEL_DEBUG, "Resetting leader hash timer\n");
            leader_hash_reset_timer();
#endif //LEADER_HASH_PER_KEY_TIMING

            write_log_format(LOG_LEVEL_DEBUG, "process_leader_hash out: added key to hash\n");
            return false;
        } else if ((keycode >= FT_LEADER_HASH_1) && (keycode <= FT_LEADER_HASH_3)) {
            write_log_format(LOG_LEVEL_INFO, "Starting leader hash with keycode: 0x%04X\n", keycode);

            leader_hash_start(keycode);

            write_log_format(LOG_LEVEL_DEBUG, "process_leader_hash out: leader hash start\n");
            return false;
        }
        write_log_format(LOG_LEVEL_DEBUG, "process_leader_hash out: leader hash not active\n");
        return true;
    }

    write_log_format(LOG_LEVEL_DEBUG, "process_leader_hash out: key release\n");
    return true;
}
