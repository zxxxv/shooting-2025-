#pragma once
#include <time.h>
#include "constant.h"
#include "bullet.h"
#include "skill.h"
#include "item.h"

typedef unsigned long Timestamp;
typedef size_t       Index;

typedef struct Boss {
	int			x, y;
	int			dx, dy;
	char		shape;
	char		outline;
} Boss;

typedef struct BossClass {
	Boss*		name;
	bool_t		alive;
	int			life;
	Timestamp	spawn;
	Timestamp	last_move_ms;
	void		(*update)(struct BossClass* self);
} BossClass;

void draw_boss();
void init_boss();