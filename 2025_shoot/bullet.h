#pragma once
#include <time.h>
#include "constant.h"
#include "input.h"

typedef unsigned long Timestamp;
typedef size_t       Index;

// �Ѿ� �߻� �ӵ�
typedef enum {
    BULLET_SPEED_MIN = 300,
    BULLET_SPEED_LOW = 250,
    BULLET_SPEED_MEDIUM = 200,
    BULLET_SPEED_HIGH = 150,
    BULLET_SPEED_ULTRA = 100
} BULLET_SPEED;

// �Ѿ� ����
typedef enum {
    BULLET_LEVEL_DEFAULT,
    BULLET_LEVEL_MEDIUM,
    BULLET_LEVEL_ULTRA
} BULLET_LEVEL;

typedef struct Bullet {
	int x, y;
    int dx, dy;     // �̵� ����
	char shape;		// '+' , '=', '*'
} Bullet;

typedef struct BulletClass {
    Bullet*         buf;            // bullets_default, bullets_medium, bullets_ultra �� �ϳ�
    Index           capacity;       // YSIZE
    Index           count;          // ���� �߻�� �Ѿ� ��
    Timestamp       last_spawn_ms;  // �ֱ� ���� �ð�
    Timestamp       last_move_ms;   // �ֱ� �̵� �ð�

    void            (*update)(struct BulletClass* self, BULLET_SPEED sp);
} BulletClass;

extern BulletClass BulletManagers[LEVEL_COUNT];

void draw_bullets();							// ���ۿ� ��� �Ѿ� ���
char* get_bullet_speed();
char* get_bullet_level();
void init_bullets();                            // �Ѿ� �ʱ�ȭ
int get_level();                                // �Ѿ� ���� ��ȯ
unsigned long get_time_ms();					//
