#include "bullet.h"

DWORD last_spawn_ms = 0;
DWORD last_move_ms = 0;
Bullet bullets[YSIZE];
int bullet_count = 0;

int update_bullets() {
    DWORD now = GetTickCount();

    // 0.1초마다 총알 생성
    if (now - last_spawn_ms >= 100) {
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
            if (bullets[i].y < 1) {
                bullets[i] = bullets[--bullet_count];
            }
            else {
                i++;
            }
        }
        last_move_ms = now;
    }

    return 0;
}

void draw_bullets() {
    update_bullets();
    for (int i = 0; i < bullet_count; i++) {
        screen[bullets[i].y][bullets[i].x] = bullets[i].shape;
    }
}