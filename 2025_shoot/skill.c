#include "skill.h"

// ½¯µå
Shield shield = { .active = false, .shape1 = '*', .shape2 = '!', .count = SHIELD_COUNT };

void init_shield_count() {
    shield.count = SHIELD_COUNT;
}

int get_shield_count() {
    return shield.count;
}

void active_shield() {
    shield.active = true;
    shield.count--;
}

void deactive_shield() {
    shield.active = false;
}

bool shield_status() {
    return shield.active;
}

void draw_skill() {
    if (shield.active == false) return;
    int x = player.x;
    int y = player.y;
    screen[y + 1][x + 1] = shield.shape1;
    screen[y][x + 1] = shield.shape2;
    screen[y - 1][x + 1] = shield.shape1;
    screen[y - 1][x] = shield.shape1;
    screen[y - 1][x - 1] = shield.shape1;
    screen[y][x - 1] = shield.shape2;
    screen[y + 1][x - 1] = shield.shape1;
    screen[y + 1][x] = shield.shape1;
}