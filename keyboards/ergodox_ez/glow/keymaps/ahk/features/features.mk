# feature.mk
FEATURE_DIR = features
PROCESS_FEATURE_DIR = $(FEATURE_DIR)/process_features
LIBRARY_DIR = lib

EEPROM_ENABLE = no
CONSOLE_ENABLE = yes

MOD_KEYS_ENABLE = yes
LEADER_HASH_ENABLE = no
RAWHID_MOD_ENABLE = no
COUNTER_KEYS_ENABLE = no
ALT_TAB_KEY_ENABLE = no

SRC += $(FEATURE_DIR)/features.c

ifeq ($(CONSOLE_ENABLE),yes)
OPT_DEFS += -DCONSOLE_ENABLE
SRC += $(LIBRARY_DIR)/logger.c
endif

ifeq ($(EEPROM_ENABLE),yes)
OPT_DEFS += -DEEPROM_ENABLE
SRC += $(LIBRARY_DIR)/eeprom_config.c
else
SRC += $(LIBRARY_DIR)/config_store.c
endif

ifeq ($(MOD_KEYS_ENABLE),yes)
OPT_DEFS += -DMOD_KEYS_ENABLE
SRC += $(PROCESS_FEATURE_DIR)/process_mod_keys.c
SRC += def/mod_keys.c
endif

ifeq ($(LEADER_HASH_ENABLE),yes)
LEADER_ENABLE = no
OPT_DEFS += -DLEADER_HASH_ENABLE
SRC += $(FEATURE_DIR)/leader_hash.c
SRC += $(PROCESS_FEATURE_DIR)/process_leader_hash.c
SRC += def/leader/leader_macro.c
SRC += def/leader/leader_hotkey.c
SRC += def/leader/leader_function.c
SRC += def/leader/leader_ahk.c
SRC += def/leader/leader_hash_end.c
endif

ifeq ($(RAWHID_MOD_ENABLE),yes)
RAW_ENABLE = yes
OPT_DEFS += -DRAWHID_MOD_ENABLE
SRC += $(FEATURE_DIR)/rawhid_mod.c
SRC += $(PROCESS_FEATURE_DIR)/process_rawhid_mod.c
endif

ifeq ($(COUNTER_KEYS_ENABLE),yes)
OPT_DEFS += -DCOUNTER_KEYS_ENABLE
SRC += $(FEATURE_DIR)/counter_keys.c
SRC += $(PROCESS_FEATURE_DIR)/process_counter_keys.c
SRC += $(LIBRARY_DIR)/keymap_ascii.c
endif

ifeq ($(ALT_TAB_KEY_ENABLE),yes)
OPT_DEFS += -DALT_TAB_KEY_ENABLE
SRC += $(PROCESS_FEATURE_DIR)/process_alt_tab.c
endif
