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
void spawn_item(int it);
bool_t get_item_flag();
bool_t set_item_flag();
char get_item_shape(int n);
void check_exp();
void draw_item();
void plus_item(char it);
void minus_item(char it);

//아이템 - 총알 2줄이나 3줄 발사, 발사 속도 up
//score EXP 만큼 채우면 아이템 둘 중 하나 랜덤으로 발생
//적기 출현 대신 아이템이 출현
//못 먹으면 skip
//먹으면 아이템에 따라 효과 적용