#include "leader_hash_end.h"

LeaderSequence leader_macros[] = {
    { (uint16_t[]){A_}, 1, macro_fname },
    { (uint16_t[]){V_}, 1, macro_lname },
    { (uint16_t[]){E_}, 1, macro_email },
    { (uint16_t[]){P_}, 1, macro_phone },
    { (uint16_t[]){I_, D_}, 2, macro_workid },
    { (uint16_t[]){N_, I_}, 2, macro_npm_install },
    { (uint16_t[]){N_, R_, S_}, 3, macro_npm_run_storybook },
    { (uint16_t[]){N_, R_, D_, S_}, 4, macro_npm_run_devserve },
};

LeaderSequence leader_hotkeys[] = {
    { (uint16_t[]){P_}, 1, hotkey_vs_command },
    { (uint16_t[]){O_}, 1, hotkey_vs_open },
    { (uint16_t[]){E_}, 1, hotkey_ditto },
    { (uint16_t[]){F_}, 1, hotkey_everything }
};

LeaderSequence leader_functions[] = {
    { (uint16_t[]){R_, B_}, 2, function_reboot },
    { (uint16_t[]){M_, C_}, 2, function_minecraft },
};

LeaderSequence leader_ahk[] = {
    { (uint16_t[]){D_}, 1, hotkey_RGP0 },
    { (uint16_t[]){M_}, 1, hotkey_RGP1 },
    { (uint16_t[]){W_}, 1, hotkey_RGP2 },
    { (uint16_t[]){V_}, 1, hotkey_RGP3 },
    { (uint16_t[]){H_}, 1, hotkey_RGP4 },
    { (uint16_t[]){T_}, 1, hotkey_RGP5 },
    { (uint16_t[]){N_}, 1, hotkey_RGP6 },
    { (uint16_t[]){G_}, 1, hotkey_RGP7 },
    { (uint16_t[]){C_}, 1, hotkey_RGP8 },
    { (uint16_t[]){R_}, 1, hotkey_RGP9 },
};

void leader_hash_end_user(uint16_t leader_key) {
    switch (leader_key) {
        case FT_LEADER_HASH_1:
            for (size_t i = 0; i < sizeof(leader_macros) / sizeof(leader_macros[0]); i++) {
                if (leader_hash_is(leader_macros[i].sequence, leader_macros[i].size)) {
                    leader_macros[i].action();
                    return;
                }
            }
            break;
        case FT_LEADER_HASH_2:
            for (size_t i = 0; i < sizeof(leader_hotkeys) / sizeof(leader_hotkeys[0]); i++) {
                if (leader_hash_is(leader_hotkeys[i].sequence, leader_hotkeys[i].size)) {
                    leader_hotkeys[i].action();
                    return;
                }
            }
            break;
        case FT_LEADER_HASH_3:
            for (size_t i = 0; i < sizeof(leader_functions) / sizeof(leader_functions[0]); i++) {
                if (leader_hash_is(leader_functions[i].sequence, leader_functions[i].size)) {
                    leader_functions[i].action();
                    return;
                }
            }
            for (size_t i = 0; i < sizeof(leader_ahk) / sizeof(leader_ahk[0]); i++) {
                if (leader_hash_is(leader_ahk[i].sequence, leader_ahk[i].size)) {
                    leader_ahk[i].action();
                    return;
                }
            }
            break;
    }
}
