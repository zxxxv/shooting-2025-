#pragma once
#include <time.h>
#include "constant.h"
#include "input.h"

typedef unsigned long Timestamp;
typedef size_t       Index;

// 총알 발사 속도
typedef enum {
    BULLET_SPEED_MIN = 300,
    BULLET_SPEED_LOW = 250,
    BULLET_SPEED_MEDIUM = 200,
    BULLET_SPEED_HIGH = 150,
    BULLET_SPEED_ULTRA = 100
} BULLET_SPEED;

// 총알 레벨
typedef enum {
    BULLET_LEVEL_DEFAULT,
    BULLET_LEVEL_MEDIUM,
    BULLET_LEVEL_ULTRA
} BULLET_LEVEL;

typedef struct Bullet {
	int x, y;
    int dx, dy;     // 이동 벡터
	char shape;		// '+' , '=', '*'
} Bullet;

typedef struct BulletClass {
    Bullet*         buf;            // bullets_default, bullets_medium, bullets_ultra 중 하나
    Index           capacity;       // YSIZE
    Index           count;          // 현재 발사된 총알 수
    Timestamp       last_spawn_ms;  // 최근 생성 시간
    Timestamp       last_move_ms;   // 최근 이동 시간

    void            (*update)(struct BulletClass* self, BULLET_SPEED sp);
} BulletClass;

extern BulletClass BulletManagers[LEVEL_COUNT];

void draw_bullets();							// 버퍼에 모든 총알 찍기
char* get_bullet_speed();
char* get_bullet_level();
void init_bullets();                            // 총알 초기화
int get_level();                                // 총알 레벨 반환
unsigned long get_time_ms();					//
