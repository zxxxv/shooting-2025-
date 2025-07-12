#pragma once

typedef enum { BOOL_FALSE = 0, BOOL_TRUE = 1 } bool_t;

#define TRUE                BOOL_TRUE
#define FALSE               BOOL_FALSE

#define XSIZE               80			                    // ȭ�� ���� ũ��		80	
#define	YSIZE               30			                    // ���� ũ��			�����: 45, ��Ʈ��: 25
#define SPAWN_Y             1                               // y = 1
#define EXP                 4                               // ������ ����ġ
#define ENEMY_MAX           999                             // ���� �ִ� ���� ��
#define SHIELD_COUNT        5                               // ���� ����
#define DEATH_COUNT         5                               // ��ī ��(���)
#define RANK_MAX            1000                            // ��Ŀ ���� �迭
#define FIGHTER             4                               // ������ ��

#define ITEM_X              4                               // ������ +
#define ITEM_EQUAL          2                               // ������ =
#define ITEM_MAX            6                               // ������ �� ��
#define LEVEL_COUNT         3                               // �Ѿ� ���� ��

#define BOSS_COUNT          2                               // ���� ��
#define BOSS_D_HP			50                              // ���� ����
#define BOSS_M_HP			100                             // ���� ����
#define BDINTERVAL			300UL                           // ����D �̵� �ӵ�
#define BMINTERVAL			350UL                           // ����B �̵� �ӵ�
#define BDSPAWN				15                              // D ���� Ÿ�̹�(����)
#define BMSPAWN				100							    // B ���� Ÿ�̹�(����)
#define BD_BULLET_INTERVAL			450UL					// �Ѿ� ���� �ֱ�
#define BM_BULLET_INTERVAL			500UL					// �Ѿ� ���� �ֱ�

#define MS_PER_SEC					1000UL                  // 1��
#define MOVE_INTERVAL_MS			50UL                    // 0.05��
#define SPAWN_INTERVAL_MS           1000UL                  // ��ȯ �ֱ� 
#define ENEMY_MOVE_INTERVAL_MS      500UL                   // �̵� �ֱ� 