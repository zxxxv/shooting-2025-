#pragma once
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "screen.h"

#define ENEMY_MAX 100

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
extern Entity	enemy;
static Shield	shield;
static int death_count;
static int enemy_count;

int set_player_position(int new_x, int new_y);
int update_player(int dx, int dy);
void draw_player();
void init_enemy();
void spawn_enemy();
void update_enemy();
void draw_enemy();
void init_death_count();
int minus_death_count();
int get_death_count();
int kill_enemy();
void active_skill();
void draw_skill();
void init_shield_count();
void deactive_skill();
int get_shield_count();