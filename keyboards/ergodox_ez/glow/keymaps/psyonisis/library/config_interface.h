#pragma once
#include "./logger.h"
#include <stdint.h>

typedef union {
  uint32_t raw;
  struct {
    uint8_t  log_level : 3; // 0-3 (LOG_LEVEL_ERROR, LOG_LEVEL_WARN, LOG_LEVEL_INFO, LOG_LEVEL_DEBUG)
  };
} user_config_t;

void config_load(void);
void config_save(void);
void config_init_user(void);
user_config_t get_config_stage(void);
void set_config_stage(user_config_t updated_config);


void config_set_log_level(uint8_t new_log_level);
uint8_t config_get_log_level(void);

