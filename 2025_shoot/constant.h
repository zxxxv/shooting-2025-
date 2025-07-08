#pragma once

// 총알 발사 속도
enum BULLET_SPEED {
    BULLET_SPEED_MIN = 300,
    BULLET_SPEED_LOW = 250,
    BULLET_SPEED_MEDIUM = 200,
    BULLET_SPEED_HIGH = 150,
    BULLET_SPEED_ULTRA = 100
};

// 총알 레벨
enum BULLET_LEVEL {
    BULLET_LEVEL_DEFAULT,
    BULLET_LEVEL_MEDIUM,
    BULLET_LEVEL_ULTRA
};

typedef enum { BOOL_FALSE = 0, BOOL_TRUE = 1 } bool_t;

#define TRUE                BOOL_TRUE
#define FALSE               BOOL_FALSE
#define XSIZE               80			                    // 화면 가로 크기		80
#define	YSIZE               45			                    // 세로 크기			45
#define ENEMY_MAX           999                             // 적기 최대 생성 수
#define EXP                 15                              // 레벨업 경험치
#define SHIELD_COUNT        5                               // 쉴드 개수
#define DEATH_COUNT         5                               // 데카 수
#define RANK_MAX            1000                            // 랭커 점수 배열
#define FIGHTER             4                               // 전투기 수
#define ITEM_X              4                               // 아이템 +
#define ITEM_EQUAL          2                               // 아이템 =
#define ITEM_MAX            6                               //아이템 총수
#define MS_PER_SEC          1000UL                          // 1초
#define MOVE_INTERVAL_MS    50UL                            // 0.05초
#define SPAWN_Y             1                               // y = 1

#define SPAWN_INTERVAL_MS           1000UL                  // 소환 주기 
#define ENEMY_MOVE_INTERVAL_MS      500UL                   // 이동 주기 