#include QMK_KEYBOARD_H

#include "./aliases.h"
#include "features/features.h"
#include "features/feature_keycodes.h"
#include "lib/logger.h"
#include "lib/config_manager.h"

#ifdef COMBO_ENABLE
#include "def/keymap_combos.h"
#endif

#ifdef LEADER_HASH_ENABLE
#include "def/leader/leader_hash_end.h"
#endif

void keyboard_pre_init_user(void) {
  config_load();
  log_init(config_get_log_level());
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return process_record_features(keycode, record);
}

void matrix_scan_user(void) {
  feature_task();
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_ergodox_pretty(
    ___, _F1,  _F2,  _F3,  _F4, _F5, FUNC,     FUNC,  _F6, _F7,  _F8,  _F9,  _F10, ___,
    ___, SCL_, CM_,  DT_,  P_,  Y_,  MACRO,    MACRO, F_,  G_,   C_,   R_,   L_,  ___,
    ___, A_,   AO_,  GE_,  CU_, I_,                   D_,  H_,   T_,   N_,   S_,  SH_MON,
    ___, DQ_,  Q_,   J_,   K_,  X_,  DM_P2,    DM_P1, B_,  M_,   W_,   V_,   Z_,  ___,
    ___, AHK_RST, WINPIN, WINMAX, WINCNTR,                APP,  PRV,  PLAY,  NXT, ___,
                                  MB2, MB1,     _F18, _F17,
                                       MB3,     _F19,
                           MDRAW, LS_, AHASH,   ATAB, NV_SPC, NUMBR
  ),
  [_NAVIGATE] = LAYOUT_ergodox_pretty(
    ___, ___, ___, ___, ___, ___, ___,          ___, ___, ___,  ___,  ___,  ___,  ___,
    ___, ___, ___, ___, ___, ___, ___,          ___, ___, WBck, PTAB, NTAB, WFwd, ___,
    ___, ___, ___, ___, ___, ___,                    ___, ArL,  ArD,  ArU,  ArR,  ___,
    ___, ___, ___, ___, ___, ___, ___,          ___, ___, HOME, PGDN, PGUP, END,  ___,
    ___, ___, ___, ___, ___,                              ___, ___, ___, ___,  ___,
                             ___, ___,          ___, ___,
                                  ___,          ___,
                        ___, ___, ___,          ___, FROM, ___
  ),
  [_NUMBER] = LAYOUT_ergodox_pretty(
___, _F11, _F12, _F13, _F14, _F15, FROM,       FROM, _F16, _F17, _F18, _F19, _F20, ___,
    ___, ___, ___, ___, ___, ___, ___,          ___, XTARE, _7,  _8,  _9,  XINCR, ___,
    ___, ___, ___, ___, ___, ___,                    _0,    _4,  _5,  _6,  XVALU, ___,
    ___, ___, ___, ___, ___, ___, ___,          ___, XTARE, _1,  _2,  _3,  XDECR, ___,
    ___, ___, ___, ___, ___,                              ___, ___, ___, ___, ___,
                             ___, ___,          ___, ___,
                                  ___,          ___,
                        ___, ___, ___,          ___, ___, FROM
  ),
  [_DYNMACRO] = LAYOUT_ergodox_pretty(
    ___, ___, ___, ___, ___, ___, ___,          ___,   ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___, FROM,         FROM,  ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___,                      ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___, DM_R2,        DM_R1, ___, DM_R2, DM_P2, ___, ___, ___,
    ___, ___, ___, ___, ___,                                ___, ___, ___, ___, ___,
                              ___, ___,         ___, ___,
                                   ___,         ___,
                         ___, ___, ___,         ___, ___, ___
  ),
  [_QWERTY] = LAYOUT_ergodox_pretty(
    ___, _1,  _2,  _3,  _4,  _5,  ___,          ___, _6,  _7,  _8,   _9,   _0, ___,
    ___, Q_,  W_,  E_,  R_,  T_,  ___,          ___, Y_,  U_,  I_,   O_,   P_, BSPC,
    ___, A_,  AS_, GD_, CF_, G_,                     H_,  J_,  K_,   L_,   SCL_, ENTR,
    ___, Z_,  X_,  C_,  V_,  B_,  ___,          ___, N_,  M_,  CM_,  DT_,  FSLS, ___,
    ___, ___, ___, ___, ___,                        TO(_BASE), ___, ___, ___, ___,
                              ___, ___,         ___, ___,
                                   ___,         ___,
                     KC_LCTL, LS_, ___,         ATAB, ___, ___
  )
};

