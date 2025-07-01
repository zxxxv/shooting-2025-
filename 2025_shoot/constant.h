#pragma once

// 총알 발사 속도
enum BULLET_LEV {
    BULLET_LEV_MIN = 300,
    BULLET_LEV_LOW = 250,
    BULLET_LEV_MEDIUM = 200,
    BULLET_LEV_HIGH = 150,
    BULLET_LEV_ULTRA = 100
};

#define XSIZE               80			// 화면 가로 크기		80
#define	YSIZE               45			// 세로 크기			45
#define ENEMY_MAX           999         // 적기 최대 생성 수
#define RANK_MAX            1000        // 랭커 점수 배열
#define EXP                 20          // 레벨업 경험치
#define SHIELD_COUNT        5           // 쉴드 개수
#define DEATH_COUNT         5           // 데카 수