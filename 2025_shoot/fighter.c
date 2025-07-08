#include "fighter.h"

fighterA player = { 1, 1, '^' };

Entity enemies[ENEMY_MAX] = { 0 };

static char fighter[7] = { '^', '#', 'w', 'A' };
static int death_count = 0;
static int enemy_count = 0;
static int kill_enemy();
static void spawn_enemy();

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

void spawn(int n) {
    if (!n) spawn_enemy();
    else spawn_item();
}

static void spawn_enemy() {
    if (enemy_count >= ENEMY_MAX) return;
    int x_spawn = (rand() % (XSIZE - 2)) + 1;
    Entity e;
    e.x = x_spawn;
    e.y = 1;
    e.shape = 'v';
    e.alive = TRUE;
    enemies[enemy_count++] = e;
}

void update_enemy() {
    static unsigned long last_spawn = 0UL;
    static unsigned long last_move = 0UL;
    unsigned long now = get_time_ms();

    // 1초마다 적 생성
    if (now - last_spawn >= 1000UL) {
        spawn_enemy();
        //spawn(now%100);
        last_spawn = now;
    }
    
    // 모든 적을 한 칸 아래로 이동
    if (now - last_move >= 500UL) {
        for (int i = 0; i < enemy_count; i++) {
            if (!enemies[i].alive) continue;
            enemies[i].y += 1;
            // 화면 밖으로 나가면 비활성화
            if (enemies[i].y >= YSIZE - 1)
                enemies[i].alive = FALSE;
        }
        last_move = now;
    }

    // 아이템 생성하기
    //int score = get_score();
    //if ((score % EXP) == 0) spawn_item();
}

void draw_enemy() {
    update_enemy();
    kill_enemy();
    for (int i = 0; i < enemy_count; i++) {
        if (enemies[i].alive == TRUE)
            screen[enemies[i].y][enemies[i].x] = enemies[i].shape;
    }
}

void init_enemy() {
    enemy_count = 0;
    for (int i = 0; i < enemy_count; i++) {
        enemies[i].alive = FALSE;
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
                enemies[i].alive = FALSE;
                add_score();
            }
        }
    }
    return 0;
}