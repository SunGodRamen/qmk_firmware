#pragma once

#include "quantum.h"
#include "../business/leader_hash.h"
#include "../feature_keycodes.h"
#include "../../lib/logger.h"
#include "stdbool.h"

bool process_leader_hash(uint16_t keycode, keyrecord_t *record);
