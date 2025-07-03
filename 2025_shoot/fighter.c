#include "fighter.h"

fighterA player = {
    .x = 1,
    .y = 1,
    .shape = '^'
};

Entity enemies[ENEMY_MAX] = { 0 };

char fighter[7] = { '^', '@', '#', 'w', 'A', 'O', 'o' };
static int death_count = 0;
static int enemy_count = 0;

static int kill_enemy();

void set_player(int n) {
    player.shape = fighter[n];
}

int get_enemy_count() {
    return enemy_count;
}

void init_death_count() {
    death_count = DEATH_COUNT;
}

int get_death_count() {
    return death_count;
}

int minus_death_count() {
    if (--death_count <= 0) {
        death_count = 0;
        game_over = 1;
    }
    return death_count;
}

int set_player_position(int new_x, int new_y) {
    if (0 < new_x < XSIZE - 1 && 0 < new_y < YSIZE - 1) {
        player.x = new_x;
        player.y = new_y;
    }
    return 0;
}

int update_player(int dx, int dy) {
    int tmpx = player.x + dx;
    int tmpy = player.y + dy;
    if (tmpx == 0 || tmpx >= XSIZE - 1 || tmpy == 0 || tmpy >= YSIZE - 1)
        return 1;
    player.x += dx;
    player.y += dy;
    return 0;
}

void draw_player() {
    screen[player.y][player.x] = player.shape;
}

void spawn_enemy() {
    if (enemy_count >= ENEMY_MAX) return;
    int x_spawn = (rand() % (XSIZE - 2)) + 1;
    enemies[enemy_count++] = (Entity){
        .x = x_spawn,
        .y = 1,
        .shape = 'V',
        .alive = true
    };
}

void update_enemy() {
    static DWORD last_spawn = 0;
    static DWORD last_move = 0;
    DWORD now = GetTickCount();

    // 1초마다 적 생성
    if (now - last_spawn >= 1000) {
        spawn_enemy();
        last_spawn = now;
    }

    if (now - last_move >= 500) {
        // 모든 적을 한 칸 아래로 이동
        for (int i = 0; i < enemy_count; i++) {
            if (!enemies[i].alive) continue;
            enemies[i].y += 1;
            // 화면 밖으로 나가면 비활성화
            if (enemies[i].y >= YSIZE - 1)
                enemies[i].alive = false;
        }
        last_move = now;
    }
}

void draw_enemy() {
    update_enemy();
    kill_enemy();
    for (int i = 0; i < enemy_count; i++) {
        if (enemies[i].alive == true)
            screen[enemies[i].y][enemies[i].x] = enemies[i].shape;
    }
}

void init_enemy() {
    enemy_count = 0;
    for (int i = 0; i < enemy_count; i++) {
        enemies[i].alive = false;
    }
}

static int kill_enemy() {
    int bcount = get_bullet_count();
    for (int i = 0; i < enemy_count; i++) {
        if (!enemies[i].alive) continue;
        if (player.x == enemies[i].x && player.y == enemies[i].y) {
            minus_death_count();
            set_player_position(XSIZE / 2, YSIZE - 2);
        }
        for (int j = 0; j < bcount; j++) {
            if (bullets[j].x == enemies[i].x && bullets[j].y == enemies[i].y) {
                enemies[i].alive = false;
                add_score();
            }
        }
    }
    return 0;
}