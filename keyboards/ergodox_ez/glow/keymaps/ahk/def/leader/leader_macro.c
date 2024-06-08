#include "leader_macro.h"

void macro_fname(void) {
    SEND_STRING("Alexander");
}

void macro_lname(void) {
    SEND_STRING("von Stuelpnagel");
}

void macro_email(void) {
    SEND_STRING("avons394@gmail.com");
}

void macro_phone(void) {
    SEND_STRING("3236466099");
}

void macro_workid(void) {
    SEND_STRING("e947984");
}

void macro_npm_install(void) {
    SEND_STRING("npm install");
}

void macro_npm_run_storybook(void) {
    SEND_STRING("npm run storybook");
}

void macro_npm_run_devserve(void) {
    SEND_STRING("npm run dev:serve");
}
