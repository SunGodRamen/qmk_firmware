# feature.mk
FEATURE_DIR = features
FEATURE_PROCESS_DIR = $(FEATURE_DIR)/process
LIBRARY_DIR = library

LOGGER_ENABLE = yes
EECONFIG_ENABLE = no
MOD_KEYS_ENABLE = no
LEADER_HASH_ENABLE = no

SRC += $(FEATURE_DIR)/features.c

ifeq ($(LOGGER_ENABLE),yes)
OPT_definitionS += -DLOGGER_ENABLE

CONSOLE_ENABLE = yes

SRC += $(LIBRARY_DIR)/logger.c
endif

ifeq ($(EECONFIG_ENABLE),yes)
OPT_definitionS += -DEECONFIG_ENABLE

EEPROM_ENABLE = yes

SRC += $(LIBRARY_DIR)/config_eeprom.c
else
SRC += $(LIBRARY_DIR)/config_session.c
endif

ifeq ($(LEADER_HASH_ENABLE),yes)
OPT_definitionS += -DLEADER_HASH_ENABLE

LEADER_ENABLE = no

SRC += $(FEATURE_DIR)/leader_hash.c
SRC += $(FEATURE_PROCESS_DIR)/process_leader_hash.c

SRC += definition/leader/macro.c
SRC += definition/leader/hotkey.c
SRC += definition/leader/function.c
SRC += definition/leader/ahk.c
SRC += definition/leader/hash_end.c
endif
