#ifndef LEADER_HASH_H
#define LEADER_HASH_H

#include <stdbool.h>
#include <stdint.h>
#include "timer.h"
#include "util.h"
#include <string.h>
#include "quantum.h"

void leader_hash_start_user(void);
void leader_hash_end_user(uint16_t leader_key);

void leader_hash_start(uint16_t leader_key);
bool leader_hash_active(void);
bool leader_hash_timed_out(void);
void leader_hash_reset_timer(void);
void leader_hash_task(void);
bool leader_hash_add(uint16_t keycode);
void leader_hash_end(void);
bool leader_hash_is(uint16_t keycodes[], uint8_t size);

#endif //LEADER_HASH_H