#include "bullet.h"

Bullet bullets[YSIZE];
static unsigned long last_spawn_ms = 0UL;
static unsigned long last_move_ms = 0UL;
static enum BULLET_SPEED speed = BULLET_SPEED_MIN;
static enum BULLET_LEVEL level = BULLET_LEVEL_DEFAULT;
static int bullet_count = 0;

static void init_bullet_speed();
static void init_bullet_level();
static enum BULLET_SPEED set_bullet_speed(int x);       // �ӵ� ����
static enum BULLET_LEVEL set_bullet_level(int e);       // ���� ����
static int update_bullets(enum BULLET_SPEED sp);        // �Ѿ� ��ĭ �ö󰡱�, y��ǥ--, ȭ�� ������ ���� �Ѿ� ����

int get_bullet_count() {
    return bullet_count;
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

static int update_bullets(enum BULLET_SPEED sp) {
    unsigned long now = get_time_ms();
    unsigned int speed = (unsigned int)sp;
    if (now - last_spawn_ms >= speed) {
        if (bullet_count < YSIZE) {
            Bullet b;
            b.x = player.x;
            b.y = player.y - 1;
            b.shape = '+';
            bullets[bullet_count++] = b;
        }
        last_spawn_ms = now;
    }

    // 0.05�ʸ��� �Ѿ� �� ĭ�� ������ �̵�
    if (now - last_move_ms >= MOVE_INTERVAL_MS) {
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
    // �Ѿ� �ӵ� up
    speed = set_bullet_speed(eatX);
    update_bullets(speed);
    // �Ѿ� lev up
    level = set_bullet_level(eatE);
    for (int i = 0; i < bullet_count; i++) {
        screen[bullets[i].y][bullets[i].x] = bullets[i].shape;
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


void init_bullet() {
    last_spawn_ms = last_move_ms = get_time_ms();
    Bullet bullets[YSIZE] = { 0, };
    bullet_count = 0;
    init_bullet_speed();
    init_bullet_level();
}

static void init_bullet_speed() {
    speed = BULLET_SPEED_MIN;
}

static void init_bullet_level() {
    level = BULLET_LEVEL_DEFAULT;
}