#include "bullet.h"

DWORD last_spawn_ms = 0;
DWORD last_move_ms = 0;
Bullet bullets[YSIZE];
static int bullet_count = 0;

int get_bullet_count() {
    return bullet_count;
}

enum BULLET_LEV set_bullet_lev(int score) {
    int k = score / 15;
    enum BULLET_LEV lev;
    switch (k) {
        case 0:
            lev = BULLET_LEV_MIN;
            break;
        case 1:
            lev = BULLET_LEV_LOW;
            break;
        case 2:
            lev = BULLET_LEV_MEDIUM;
            break;
        case 3:
            lev = BULLET_LEV_HIGH;
            break;
        default:
            lev = BULLET_LEV_ULTRA;
            break;
    }
    return lev;
}

int update_bullets(enum BULLET_LEV level) {
    DWORD now = GetTickCount();
    int speed = level;
    // level 마다 총알 생성
    if (now - last_spawn_ms >= speed) {
        if (bullet_count < YSIZE) {
            bullets[bullet_count++] = (Bullet){
                .x = player.x,
                .y = player.y - 1,
                .shape = '+'
            };
        }
        last_spawn_ms = now;
    }

    // 0.05초마다 총알 한 칸씩 앞으로 이동
    if (now - last_move_ms >= 50) {
        for (int i = 0; i < bullet_count; ) {
            bullets[i].y--;
            if (bullets[i].y < 1)
                bullets[i] = bullets[--bullet_count];
            else i++;
        }
        last_move_ms = now;
    }

    return 0;
}

void draw_bullets() {
    score = get_score();
    enum BULLET_LEV level = set_bullet_lev(score);
    update_bullets(level);
    for (int i = 0; i < bullet_count; i++) {
        screen[bullets[i].y][bullets[i].x] = bullets[i].shape;
    }
}

