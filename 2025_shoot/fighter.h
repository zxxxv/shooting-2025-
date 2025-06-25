#pragma once
#include <stdbool.h>
#include "screen.h"

typedef struct fighterA {
	int x, y;
	char shape;		// '^'
} fighterA;

typedef struct {
	int x, y;
	char shape;		// 'V'
	bool alive;
} Entity;

extern fighterA player;
extern Entity	enemy;

int set_player_position(int new_x, int new_y);
int move_player(int dx, int dy);

//static fighterA* player = &player;
//Entity* enemy = &enemy;