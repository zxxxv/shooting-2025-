#pragma once
#include "constant.h"
#include "score.h"
//#include "fighter.h"

typedef struct Item {
	int x, y;
	char shape;
}Item;

extern item_count;
extern Item item[ITEM_MAX];
extern eatX;
extern eatE;

void init_item();
void reset_item();
void spawn_item(int it);
bool_t get_item_flag();
bool_t set_item_flag();
char get_item_shape(int n);
void check_exp();
void draw_item();
void plus_item(char it);
void minus_item(char it);