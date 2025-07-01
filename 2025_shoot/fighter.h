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

// �÷��̾� ������
int set_player_position(int new_x, int new_y);
int update_player(int dx, int dy);
void draw_player();

// �� ������
void init_enemy();
void spawn_enemy();
void update_enemy();
void draw_enemy();
//int kill_enemy();

// ��ī
void init_death_count();
int minus_death_count();
int get_death_count();