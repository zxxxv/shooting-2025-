#pragma once

typedef enum { BOOL_FALSE = 0, BOOL_TRUE = 1 } bool_t;

#define TRUE                BOOL_TRUE
#define FALSE               BOOL_FALSE

#define XSIZE               80			                    // 화면 가로 크기		80	
#define	YSIZE               30			                    // 세로 크기			모니터: 45, 노트북: 25
#define SPAWN_Y             1                               // y = 1
#define EXP                 4                               // 레벨업 경험치
#define ENEMY_MAX           999                             // 적기 최대 생성 수
#define SHIELD_COUNT        5                               // 쉴드 개수
#define DEATH_COUNT         5                               // 데카 수(목숨)
#define RANK_MAX            1000                            // 랭커 점수 배열
#define FIGHTER             4                               // 전투기 수

#define ITEM_X              4                               // 아이템 +
#define ITEM_EQUAL          2                               // 아이템 =
#define ITEM_MAX            6                               // 아이템 총 수
#define LEVEL_COUNT         3                               // 총알 레벨 수

#define BOSS_COUNT          2                               // 보스 수
#define BOSS_D_HP			50                              // 보스 생명
#define BOSS_M_HP			100                             // 보스 생명
#define BDINTERVAL			300UL                           // 보스D 이동 속도
#define BMINTERVAL			350UL                           // 보스B 이동 속도
#define BDSPAWN				15                              // D 스폰 타이밍(점수)
#define BMSPAWN				100							    // B 스폰 타이밍(점수)
#define BD_BULLET_INTERVAL			450UL					// 총알 생성 주기
#define BM_BULLET_INTERVAL			500UL					// 총알 생성 주기

#define MS_PER_SEC					1000UL                  // 1초
#define MOVE_INTERVAL_MS			50UL                    // 0.05초
#define SPAWN_INTERVAL_MS           1000UL                  // 소환 주기 
#define ENEMY_MOVE_INTERVAL_MS      500UL                   // 이동 주기 