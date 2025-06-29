#pragma once
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <stdbool.h>
#include "screen.h"
#include "constant.h"
#include "bullet.h"

typedef struct fighterA {
	int x, y;
	char shape;		// '^'
} fighterA;

typedef struct Entity {
	int x, y;
	char shape;		// 'V'
	bool alive;		
	//char attack;	// '#'
} Entity;

typedef struct Shield {
	bool active;
	char shape1;
	char shape2;
	unsigned int count;
} Shield;

extern fighterA player;
static Shield	shield;
static int death_count;
static int enemy_count;

// 플레이어 전투기
int set_player_position(int new_x, int new_y);
int update_player(int dx, int dy);
void draw_player();
void kill_player();

// 적 전투기
void init_enemy();
void spawn_enemy();
void update_enemy();
void draw_enemy();
int kill_enemy();

// 데카
void init_death_count();
int minus_death_count();
int get_death_count();

// 스킬 (쉴드)
void draw_skill();
void init_shield_count();
void active_shield();
void deactive_shield();
int get_shield_count();
bool shield_status();