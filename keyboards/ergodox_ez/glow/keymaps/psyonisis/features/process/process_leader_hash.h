#ifndef PROCESS_LEADER_HASH_H
#define PROCESS_LEADER_HASH_H

#include "../leader_hash.h"
#include "../feature_keycodes.h"
#include "../../lib/logger.h"
#include "stdbool.h"
#include "quantum.h"

bool process_leader_hash(uint16_t keycode, keyrecord_t *record);

#endif //PROCESS_LEADER_HASH_H