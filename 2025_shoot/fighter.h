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

extern fighterA player;
extern Entity enemies[ENEMY_MAX];

// 플레이어 전투기
int set_player_position(int new_x, int new_y);
int update_player(int dx, int dy);
void draw_player();
void set_player(int n);

// 적 전투기
void init_enemy();
void spawn_enemy();
void update_enemy();
void draw_enemy();
int get_enemy_count();

// 데카
void init_death_count();
int minus_death_count();
int get_death_count();