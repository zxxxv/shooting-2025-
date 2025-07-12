#include "skill.h"

// ½¯µå
Shield shield = {
    .active = FALSE,
    .shape1 = '=',
    .shape2 = '|',
    .count = SHIELD_COUNT,
    .areaX[1][1] = 0,
    .areaY[1][1] = 0
};

void init_shield_count() {
    shield.count = SHIELD_COUNT;
}

int get_shield_count() {
    return shield.count;
}

void active_shield() {
    shield.active = TRUE;
    shield.count--;
    //set_shield_area();
}

void deactive_shield() {
    shield.active = FALSE;
}

bool_t shield_status() {
    return shield.active;
}

void draw_skill() {
    if (shield.active == FALSE) return;
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

void off_shield_at(int idx) {
    enemies[idx] = enemies[--enemy_count];
    deactive_shield();
}
