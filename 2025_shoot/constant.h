#pragma once

// �Ѿ� �߻� �ӵ�
enum BULLET_SPEED {
    BULLET_SPEED_MIN = 300,
    BULLET_SPEED_LOW = 250,
    BULLET_SPEED_MEDIUM = 200,
    BULLET_SPEED_HIGH = 150,
    BULLET_SPEED_ULTRA = 100
};

// �Ѿ� ����
enum BULLET_LEVEL {
    BULLET_LEVEL_DEFAULT,
    BULLET_LEVEL_MEDIUM,
    BULLET_LEVEL_ULTRA
};

typedef enum { BOOL_FALSE = 0, BOOL_TRUE = 1 } bool_t;

#define TRUE                BOOL_TRUE
#define FALSE               BOOL_FALSE
#define XSIZE               80			                    // ȭ�� ���� ũ��		80
#define	YSIZE               45			                    // ���� ũ��			45
#define ENEMY_MAX           999                             // ���� �ִ� ���� ��
#define EXP                 15                              // ������ ����ġ
#define SHIELD_COUNT        5                               // ���� ����
#define DEATH_COUNT         5                               // ��ī ��
#define RANK_MAX            1000                            // ��Ŀ ���� �迭
#define FIGHTER             4                               // ������ ��
#define ITEM_X              4                               // ������ +
#define ITEM_EQUAL          2                               // ������ =
#define ITEM_MAX            6                               //������ �Ѽ�
#define MS_PER_SEC          1000UL                          // 1��
#define MOVE_INTERVAL_MS    50UL                            // 0.05��
#define SPAWN_Y             1                               // y = 1

#define SPAWN_INTERVAL_MS           1000UL                  // ��ȯ �ֱ� 
#define ENEMY_MOVE_INTERVAL_MS      500UL                   // �̵� �ֱ� 