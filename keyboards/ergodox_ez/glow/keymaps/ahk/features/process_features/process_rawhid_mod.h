#ifndef PROCESS_RAWHID_MOD_H
#define PROCESS_RAWHID_MOD_H

#include "quantum.h"
#include "../../../../ergodox_ez.h"
#include "../../config.h"
#include "../feature_keycodes.h"
#include "../rawhid_mod.h"
#include "raw_hid.h"
#include "../../lib/logger.h"
#include "stdbool.h"
#include "string.h"

#define IS_LAYER_TOGGLE(kc) ( \
    (kc >= QK_LAYER_TAP && kc <= QK_LAYER_TAP_MAX) || \
    (kc >= QK_TO && kc <= QK_TO_MAX) || \
    (kc >= QK_MOMENTARY && kc <= QK_MOMENTARY_MAX) \
)

bool process_rawhid_mod(uint16_t keycode, keyrecord_t *record);

#endif //PROCESS_RAWHID_MOD_H
