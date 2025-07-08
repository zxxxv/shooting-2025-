#include "fighter.h"

fighterA player = { 1, 1, '^' };

Entity enemies[ENEMY_MAX] = { 0 };

int enemy_count = 0;

static char fighter[7] = { '^', '#', 'w', 'A' };
static int death_count = 0;
static int kill_enemy();
static void spawn_enemy();
static void update_enemy();
static void spawn(bool_t n, unsigned long now);

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
    if (new_x > 0 && new_x < XSIZE - 1
        && new_y > 0 && new_y < YSIZE - 1) {
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

// 플래그 값에 따라 생성 대상이 달라짐
static void spawn(bool_t n, unsigned long now) {
    if (n == TRUE) spawn_item((int)now % 2);
    else spawn_enemy();
}

static void spawn_enemy() {
    if (enemy_count >= ENEMY_MAX) return;
    int x_spawn = (rand() % (XSIZE - 2)) + 1;
    Entity e;
    e.x = x_spawn;
    e.y = SPAWN_Y;
    e.shape = 'v';
    e.alive = TRUE;
    enemies[enemy_count++] = e;
}

static void update_enemy() {
    static unsigned long last_spawn = 0UL;
    static unsigned long last_move = 0UL;
    unsigned long now = get_time_ms();
    bool_t flag = get_item_flag();

    if (now - last_spawn >= SPAWN_INTERVAL_MS) {
        spawn(flag, now);
        last_spawn = now;
    }
    
    // 한 칸 아래로 이동
    if (now - last_move >= ENEMY_MOVE_INTERVAL_MS) {
        for (int i = 0; i < enemy_count; i++) {
            if (!enemies[i].alive) continue;
            enemies[i].y += 1;
            // 적 화면 밖으로 나가면 비활성화
            if (enemies[i].y >= YSIZE - 1)
                enemies[i].alive = FALSE;
        }
        for (int i = 0; i < item_count; ) {
            item[i].y += 1;
            // 아이템 화면 밖으로 나가면 없애기
            if (item[i].y >= YSIZE - 1) {
                plus_item(item[i].shape);
                item[i] = item[--item_count];
            }
            else i++;
        }
        last_move = now;
    }
}

void draw_enemy() {
    update_enemy();
    kill_enemy();
    for (int i = 0; i < enemy_count; i++) {
        if (enemies[i].alive == TRUE)
            screen[enemies[i].y][enemies[i].x] = enemies[i].shape;
    }
    draw_item();
}

void init_enemy() {
    enemy_count = 0;
    for (int i = 0; i < ENEMY_MAX; i++) {
        enemies[i].alive = FALSE;
    }
}

static int kill_enemy() {
    int lvl = get_level();
    int bcount = (int)BulletManagers[lvl].count;
    Bullet* buf = BulletManagers[lvl].buf;
    for (int i = 0; i < enemy_count; ) {
        // 총알 충돌 검사
        bool_t removed = FALSE;
        for (int j = 0; j < bcount; j++) {
            if (buf[j].x == enemies[i].x && buf[j].y == enemies[i].y) {
                add_score();
                check_exp();
                enemies[i] = enemies[--enemy_count];
                removed = TRUE;
                break;
            }
        }
        if (removed) continue;

        bool_t collision = FALSE;
        if (shield.active) {
            int dx = enemies[i].x - player.x;
            int dy = enemies[i].y - player.y;
            if (abs(dx) <= 1 && abs(dy) <= 1)
                collision = TRUE;
        }
        else {
            if (enemies[i].x == player.x && enemies[i].y == player.y)
                collision = TRUE;
        }

        if (collision) {
            if (shield.active) {
                off_shield_at(i);
                add_score();
                check_exp();
                continue;
            }
            else {
                minus_death_count();
                set_player_position(XSIZE / 2, YSIZE - 2);
                enemies[i] = enemies[--enemy_count];
                continue;
            }
        }
        i++;
    }
    return 0;
}