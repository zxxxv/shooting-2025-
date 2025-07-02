#include "skill.h"

// ½¯µå
Shield shield = {
    .active = false,
    .shape1 = '*',
    .shape2 = '!',
    .count = SHIELD_COUNT,
    .areaX[1][1] = 0,
    .areaY[1][1] = 0
};

static void set_shield_area();
static void off_shield();

void init_shield_count() {
    shield.count = SHIELD_COUNT;
}

int get_shield_count() {
    return shield.count;
}

void active_shield() {
    shield.active = true;
    shield.count--;
    //set_shield_area();
}

void deactive_shield() {
    shield.active = false;
}

bool shield_status() {
    return shield.active;
}

// »ç¿ë X
static void set_shield_area() {
    int x = player.x;
    int y = player.y;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            shield.areaX[i][j] = x + (j - 1);
            shield.areaY[i][j] = y + (i - 1);
        }
    }
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
    off_shield();
}

static void off_shield(void) {
    int px = player.x, py = player.y;
    int ecount = get_enemy_count();
    for (int i = 0; i < ecount; i++) {
        if (!enemies[i].alive) continue;
        int dx = enemies[i].x - px;
        int dy = enemies[i].y - py;
        if (abs(dx) <= 1 && abs(dy) <= 1) {
            enemies[i].alive = false;
            deactive_shield();
            return;
        }
    }
}
