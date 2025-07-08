#include "bullet.h"

Bullet bullets[YSIZE];
static unsigned long last_spawn_ms = 0UL;
static unsigned long last_move_ms = 0UL;
static enum BULLET_LEV level = BULLET_LEV_MIN;
static int bullet_count = 0;

static void init_bullet_lev();

int get_bullet_count() {
    return bullet_count;
}

unsigned long get_time_ms() {
    return (unsigned long)(clock() * MS_PER_SEC / CLOCKS_PER_SEC);
}

enum BULLET_LEV set_bullet_lev(int score) {
    int k = score / EXP;    
    enum BULLET_LEV lev;
    switch (k) {
        case 0: lev = BULLET_LEV_MIN; break;
        case 1: lev = BULLET_LEV_LOW; break;
        case 2: lev = BULLET_LEV_MEDIUM; break;
        case 3: lev = BULLET_LEV_HIGH; break;
        default: lev = BULLET_LEV_ULTRA; break;
    }
    return lev;
}

int update_bullets(enum BULLET_LEV level) {
    unsigned long now = get_time_ms();
    unsigned int speed = (unsigned int)level;
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
    if (now - last_move_ms >= 50UL) {
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
    int score = get_score();
    level = set_bullet_lev(score);
    update_bullets(level);
    for (int i = 0; i < bullet_count; i++) {
        screen[bullets[i].y][bullets[i].x] = bullets[i].shape;
    }
}

char *get_bullet_lev() {
    int i = level/50 - 2;
    char* bullet_speed[] = { "V", "IV", "III", "II", "I" };
    return bullet_speed[i];
}

void init_bullet() {
    last_spawn_ms = last_move_ms = get_time_ms();
    Bullet bullets[YSIZE] = { 0, };
    bullet_count = 0;
    init_bullet_lev();
}

static void init_bullet_lev() {
    level = BULLET_LEV_MIN;
}