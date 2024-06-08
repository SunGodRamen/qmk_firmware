#include "./config_interface.h"

user_config_t config_store;

void config_load(void) {
  if (config_store.raw == 0xFFFFFFFF) {
    config_init_user(); // Reinitialize if EEPROM is not set
  }
}

void config_save(void) {
    // place holder function for excluding from compilation
}

void config_init_user(void) {
  config_store.raw = 0;
  config_store.log_level = (uint8_t)default_log_level;
}

user_config_t get_config_store(void) {
  return config_store;
}

void set_config_store(user_config_t updated_config) {
  config_store = updated_config;
}

// Setters and Getters

void config_set_log_level(uint8_t new_log_level) {
  config_store.log_level = new_log_level;
}

uint8_t config_get_log_level(void) {
  return config_store.log_level;
}
