#include "item.h"

Item item[ITEM_MAX] = { 0 };

int item_count = 0;
int eatX = 0;
int eatE = 0;
static int itemX = ITEM_X;
static int itemE = ITEM_EQUAL;
static bool_t spawn_requested = 0;
static char item_shape[] = {'x', '='};

static void plus_eat(char shape);
static void eat_item();

char get_item_shape(int n) {
	return item_shape[n];
}

void init_item() {
    reset_item();
    item_count = 0;
}

void reset_item() {
    itemX = ITEM_X;
    itemE = ITEM_EQUAL;
    spawn_requested = 0;
    eatX = 0;
    eatE = 0;
}

bool_t get_item_flag() {
	return spawn_requested;
}

bool_t set_item_flag() {
    spawn_requested = !spawn_requested;
	return spawn_requested;
}

void spawn_item(int it) {
    if (item_count >= ITEM_MAX) return;
    if (itemX + itemE <= 0) return;
    if (it == 0 && itemX == 0) it = 1;
    else if (it == 1 && itemE == 0) it = 0;
    int x_spawn = (rand() % (XSIZE - 2)) + 1;
    Item i;
    i.x = x_spawn;
    i.y = SPAWN_Y;
    i.shape = get_item_shape(it);
    item[item_count++] = i;
    set_item_flag();
}

void check_exp() {
    int exp = get_score();
    bool_t is_first0 = (bool_t)!(exp / EXP);
    int ex = exp % EXP;
    if (is_first0 == FALSE && ex == 0 && eatX + eatE < 6 && item_count < ITEM_MAX) set_item_flag();
}

void draw_item() {
    eat_item();
    for (int i = 0; i < item_count; i++) {
        screen[item[i].y][item[i].x] = item[i].shape;
    }
}

void plus_item(char shape) {
    switch (shape) {
        case 'x': ++itemX; break;
        case '=': ++itemE; break;
    }
}

void minus_item(char shape) {
    switch (shape) {
        case 'x': --itemX; break;
        case '=': --itemE; break;
    }
}

static void plus_eat(char shape) {
    switch (shape) {
    case 'x': ++eatX; break;
    case '=': ++eatE; break;
    }
}

static void eat_item() {
    if (item_count == 0) return;
    for (int i = 0; i < item_count; ) {
        if (player.x == item[i].x && player.y == item[i].y) {
            plus_eat(item[i].shape);
            minus_item(item[i].shape);
            item[i] = item[--item_count];
        }
        else i++;
    }
}