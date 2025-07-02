#pragma once
#include <stdbool.h>
#include  "constant.h"
#include  "fighter.h"

typedef struct Shield {
	bool active;
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
bool shield_status();
void off_shield();
