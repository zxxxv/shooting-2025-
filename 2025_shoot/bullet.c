#include "bullet.h"

Bullet bullets_default[YSIZE];
Bullet bullets_medium[2*YSIZE];
Bullet bullets_ultra[3*YSIZE];

static BULLET_SPEED speed = BULLET_SPEED_MIN;
static BULLET_LEVEL level = BULLET_LEVEL_DEFAULT;

static BULLET_SPEED set_bullet_speed(int x);                          // 속도 설정
static BULLET_LEVEL set_bullet_level(int e);                          // 레벨 설정
static void update_default(BulletClass* self, BULLET_SPEED sp);       // 기본 한줄
static void update_medium(BulletClass* self, BULLET_SPEED sp);        // 대각 양방향
static void update_ultra(BulletClass* self, BULLET_SPEED sp);         // 전방 3줄

BulletClass BulletManagers[LEVEL_COUNT] = {
    { bullets_default,  YSIZE, 0, 0, 0, update_default },
    { bullets_medium,   2 * YSIZE, 0, 0, 0, update_medium  },
    { bullets_ultra,    3 * YSIZE, 0, 0, 0, update_ultra   },
};

int get_level() {
    return level;
}

unsigned long get_time_ms() {
    return (unsigned long)(clock() * MS_PER_SEC / CLOCKS_PER_SEC);
}

static enum BULLET_SPEED set_bullet_speed(int x) {
    int k = x;
    enum BULLET_SPEED lev;
    switch (k) {
        case 0: lev = BULLET_SPEED_MIN; break;
        case 1: lev = BULLET_SPEED_LOW; break;
        case 2: lev = BULLET_SPEED_MEDIUM; break;
        case 3: lev = BULLET_SPEED_HIGH; break;
        default: lev = BULLET_SPEED_ULTRA; break;
    }
    return lev;
}

static enum BULLET_LEVEL set_bullet_level(int e) {
    int k = e;
    enum BULLET_LEVEL lev;
    switch (k) {
    case 0: lev = BULLET_LEVEL_DEFAULT; break;
    case 1: lev = BULLET_LEVEL_MEDIUM; break;
    default: lev = BULLET_LEVEL_ULTRA; break;
    }
    return lev;
}

static void update_default(BulletClass* self, BULLET_SPEED sp) {
    Timestamp now = get_time_ms();
    // 스폰 타이밍, 용량 체크
    if (now - self->last_spawn_ms >= (unsigned)sp && self->count < self->capacity) {
        self->buf[self->count++] = (Bullet){
            .x = player.x,
            .y = player.y - 1,
            .shape = '+'
        };
        self->last_spawn_ms = now;
    }
    // 이동
    if (now - self->last_move_ms >= MOVE_INTERVAL_MS) {
        for (Index i = 0; i < self->count; ) {
            Bullet* b = &self->buf[i];
            b->y--;
            if (b->y < 1)
                self->buf[i] = self->buf[--self->count];
            else i++;
        }
        self->last_move_ms = now;
    }
    // 렌더링
    for (Index i = 0; i < self->count; i++) {
        Bullet* b = &self->buf[i];
        screen[b->y][b->x] = b->shape;
    }
}

static void update_medium(BulletClass* self, BULLET_SPEED sp) {
    Timestamp now = get_time_ms();
    // 스폰 타이밍, 용량 체크 (대각선 2발)
    if (now - self->last_spawn_ms >= (unsigned)sp && self->count + 2 <= self->capacity) {
        // 좌/우 대각선 발사
        for (int dx = -1; dx <= 1; dx += 2) {
            self->buf[self->count++] = (Bullet){
                .x = player.x,
                .y = player.y - 1,
                .shape = '=',
                .dx = dx,
                .dy = -1
            };
        }
        self->last_spawn_ms = now;
    }
    // 이동
    if (now - self->last_move_ms >= MOVE_INTERVAL_MS) {
        for (Index i = 0; i < self->count; ) {
            Bullet* b = &self->buf[i];
            b->x += b->dx;
            b->y += b->dy;
            if (b->y < 1 || b->x < 1 || b->x >= XSIZE - 1)
                self->buf[i] = self->buf[--self->count];
            else i++;
        }
        self->last_move_ms = now;
    }
    // 렌더링
    for (Index i = 0; i < self->count; i++) {
        Bullet* b = &self->buf[i];
        screen[b->y][b->x] = b->shape;
    }
}

static void update_ultra(BulletClass* self, BULLET_SPEED sp) {
    Timestamp now = get_time_ms();
    // 스폰 타이밍, 용량 체크
    if (now - self->last_spawn_ms >= (unsigned)sp && self->count < self->capacity) {
        // 전방 3발 발사
        for (int dx = -1; dx <= 1; dx++) {
            Index idx = self->count++;
            self->buf[idx] = (Bullet){
                .x = player.x + dx,
                .y = player.y - 1,
                .shape = '*',
                .dx = 0,
                .dy = -1
            };
        }
        self->last_spawn_ms = now;
    }
    // 이동
    if (now - self->last_move_ms >= MOVE_INTERVAL_MS) {
        for (Index i = 0; i < self->count; ) {
            Bullet* b = &self->buf[i];
            b->y += b->dy;
            if (b->y < 1)
                self->buf[i] = self->buf[--self->count];
            else i++;
        }
        self->last_move_ms = now;
    }
    // 렌더링
    for (Index i = 0; i < self->count; i++) {
        Bullet* b = &self->buf[i];
        screen[b->y][b->x] = b->shape;
    }
}

void draw_bullets() {
    speed = set_bullet_speed(eatX);
    level = set_bullet_level(eatE);
    BulletManagers[level].update(&BulletManagers[level], speed);
}

void init_bullets() {
    for (int i = 0; i < LEVEL_COUNT; i++) {
        BulletManagers[i].count = 0;
        BulletManagers[i].last_spawn_ms = BulletManagers[i].last_move_ms = get_time_ms();
    }
}

char *get_bullet_speed() {
    int i = speed /50 - 2;
    char* bullet_speed[] = { "V", "IV", "III", "II", "I" };
    return bullet_speed[i];
}

char* get_bullet_level() {
    int i = level;
    char* bullet_level[] = { "I", "II", "III" };
    return bullet_level[i];
}