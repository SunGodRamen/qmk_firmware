# rules.mk

KEYBOARD_NAME = ergodox_ez
KEYMAP_NAME = ahk
KEYMAP_DIR = keyboards/$(KEYBOARD_NAME)/glow/keymaps/$(KEYMAP_NAME)
BOOTLOADER = halfkay

LTO_ENABLE = yes

DEFERRED_EXEC_ENABLE = yes

OS_DETECTION_ENABLE = no

NKRO_ENABLE = no

MOUSEKEY_ENABLE  = no  # Mouse keys
EXTRAKEY_ENABLE = no # Media keys
# MOUSE_SHARED_EP = yes

DYNAMIC_MACRO_ENABLE = yes
COMBO_ENABLE = yes
SWAP_HANDS_ENABLE = no
TAP_DANCE_ENABLE = no

#FEATURES
FEATURE_DIR = $(KEYMAP_DIR)/features
$(info FEATURE_DIR is $(FEATURE_DIR))
include $(FEATURE_DIR)/features.mk