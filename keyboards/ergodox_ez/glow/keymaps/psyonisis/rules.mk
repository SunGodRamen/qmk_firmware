# rules.mk
KEYBOARD_NAME = ergodox_ez
KEYMAP_NAME = psyonisis
KEYMAP_DIR = keyboards/$(KEYBOARD_NAME)/glow/keymaps/$(KEYMAP_NAME)

BOOTLOADER = halfkay

LTO_ENABLE = yes
DEFERRED_EXEC_ENABLE = yes

NKRO_ENABLE = yes

DYNAMIC_MACRO_ENABLE = no
COMBO_ENABLE = yes
SWAP_HANDS_ENABLE = no

#FEATURES
FEATURE_DIR = $(KEYMAP_DIR)/features
include $(FEATURE_DIR)/features.mk
