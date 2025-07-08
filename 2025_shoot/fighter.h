#pragma once
#include <stdlib.h>
#include <time.h>
#include "screen.h"
#include "constant.h"
#include "bullet.h"
#include "item.h"

typedef struct fighterA {
	int x, y;
	char shape;		// '^'
} fighterA;

typedef struct Entity {
	int x, y;
	char shape;		// 'V'
	bool_t alive;		
	//char attack;	// '#'
} Entity;

extern fighterA player;
extern Entity enemies[ENEMY_MAX];
extern enemy_count;

// �÷��̾� ������
int set_player_position(int new_x, int new_y);
int update_player(int dx, int dy);
void draw_player();
void set_player(int n);

// �� ������
void init_enemy();
void spawn_enemy();
void draw_enemy();
int get_enemy_count();

// ���� ī��Ʈ(���)
void init_death_count();
int minus_death_count();
int get_death_count();
