#pragma once
#include  "constant.h"
#include  "fighter.h"

typedef struct Shield {
	bool_t active;
	char shape1;
	char shape2;
	unsigned int count;
	int areaX[3][3];
	int areaY[3][3];
} Shield;

extern Shield shield;

void (*skills[])();

// ½¯µå
void draw_skill();
void init_shield_count();
void active_shield();
void deactive_shield();
int get_shield_count();
bool_t shield_status();
void off_shield();
