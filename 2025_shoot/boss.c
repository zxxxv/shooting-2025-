#include "boss.h"

Boss Daddy = {
	.x = 3,
	.y = 2,
	.dx = 1,
	.dy = 1,
	.shape = 'D',
	.outline = '#'
};

Boss Mommy = {
	.x = 3,
	.y = 2,
	.dx = 1,
	.dy = 1,
	.shape = 'M',
	.outline = '@',
};

Bullet bullets_Daddy[3 * YSIZE];
Bullet bullets_Mommy[8 * YSIZE];
static int currentBoss = -1;

static void updateDaddy(BossClass* self);
static void updateMommy(BossClass* self);
static int spawn_boss();
static void render_boss(BossClass* self);
static void check_boss_collision();
static void damage_boss(int idx, int amount);
static void updateBossBullets(struct BulletClass* self, BULLET_SPEED sp);
static void fire_bullet(int x, int y, int dx, int dy);
static void init_boss_bullets();
static void check_boss_collision();
static void check_boss_bullet_collision();

BulletClass BossBulletManagers[BOSS_COUNT] = {
	{ bullets_Daddy, sizeof(bullets_Daddy) / sizeof(Bullet), 0, 0, 0, updateBossBullets },
	{ bullets_Mommy, sizeof(bullets_Mommy) / sizeof(Bullet), 0, 0, 0, updateBossBullets }
};

static BossClass BossManagers[BOSS_COUNT] = {
	{&Daddy, TRUE, BOSS_D_HP, 0, 0, updateDaddy},
	{&Mommy, TRUE, BOSS_M_HP, 0, 0, updateMommy}
};

static void updateDaddy(BossClass* self) {
	Timestamp now = get_time_ms();
	Boss* b = self->name;
	if (!self->alive || self->life <= 0) return;
	// 이동
	if (now - self->last_move_ms >= BDINTERVAL) {
		int newX = b->x + b->dx;
		int newY = b->y + b->dy;
		if (newX < 3 || newX > XSIZE - 4) b->dx = -b->dx;
		if (newY < 2 || newY > YSIZE / 3) b->dy = -b->dy;
		b->x += b->dx;
		b->y += b->dy;
		self->last_move_ms = now;
	}
	// 3방향 공격
	if (now - self->spawn >= BD_BULLET_INTERVAL) {
        for (int dx0 = -1; dx0 <= 1; ++dx0) {
            fire_bullet(b->x + dx0, b->y + 1, dx0, 1);
        }
        self->spawn = now;
    }
	render_boss(self);
}

static void updateMommy(BossClass* self) {
	Timestamp now = get_time_ms();
	Boss* b = self->name;
	if (!self->alive || self->life <= 0) return;
	// 이동
	if (now - self->last_move_ms >= BMINTERVAL) {
		int newX = b->x + b->dx;
		int newY = b->y + b->dy;
		if (newX < 3 || newX > XSIZE - 4) b->dx = -b->dx;
		if (newY < 2 || newY > YSIZE - 3) b->dy = -b->dy;
		b->x += b->dx;
		b->y += b->dy;
		self->last_move_ms = now;
	}
	// 8방향 공격
	if (now - self->spawn >= BM_BULLET_INTERVAL) {
		// 방향 벡터과 스폰 위치 오프셋
		int offset[8][2] = { {0,2},{1,2},{2,1},{1,0},{0,-1},{-1,0},{-2,1},{-1,2} };
		for (int i = 0; i < 8; ++i) {
			int ox = offset[i][0];
			int oy = offset[i][1] - 1; // center y + dy
			int vx = (ox > 0) ? 1 : (ox < 0) ? -1 : 0;
			int vy = (oy > 0) ? 1 : (oy < 0) ? -1 : 0;
			fire_bullet(b->x + ox, b->y + oy, vx, vy);
		}
		self->spawn = now;
	}
	render_boss(self);
}

static void fire_bullet(int x, int y, int dx, int dy) {
	if (currentBoss < 0 || currentBoss >= BOSS_COUNT) return;
	BulletClass* mgr = &BossBulletManagers[currentBoss];
	if (mgr->count >= mgr->capacity) return;
	Bullet* b = &mgr->buf[mgr->count++];
	b->x = x; b->y = y; b->dx = dx; b->dy = dy; b->shape = '*';
}

static void updateBossBullets(BulletClass* self, BULLET_SPEED sp) {
	Timestamp now = get_time_ms();
	// 이동 처리
	if (now - self->last_move_ms >= (unsigned)sp) {
		for (int i = 0; i < self->count; ) {
			Bullet* b = &self->buf[i];
			b->x += b->dx;
			b->y += b->dy;
			if (b->x < 1 || b->x >= XSIZE -1 || b->y < 1 || b->y >= YSIZE -1) {
				self->buf[i] = self->buf[--self->count];
			}
			else {
				++i;
			}
		}
		self->last_move_ms = now;
	}
	// 렌더링 처리
	for (int i = 0; i < self->count; ++i) {
		Bullet* b = &self->buf[i];
		screen[b->y][b->x] = b->shape;
	}
}

void draw_boss() {
	int idx = spawn_boss();
	if (idx >= 0 && idx < 2) currentBoss = idx;
	else if (idx == 2) {
		game_over = 1;
		game_clear = 1;
	}
	for (int i = 0; i < BOSS_COUNT; ++i) {
		BossBulletManagers[i].update(&BossBulletManagers[i], BULLET_SPEED_HIGH);
	}
	if (currentBoss >= 0 && BossManagers[currentBoss].alive)
		BossManagers[currentBoss].update(&BossManagers[currentBoss]);
	check_boss_collision();
	check_boss_bullet_collision();
}

static int spawn_boss() {
	if (currentBoss >= 0 && BossManagers[currentBoss].alive) return currentBoss;
	int score = get_score();
	if (score >= BDSPAWN && BossManagers[0].alive && currentBoss < 0) {
		BossManagers[0].spawn = get_time_ms();
		return 0;
	}
	if (score >= BMSPAWN && !BossManagers[0].alive && BossManagers[1].alive && currentBoss < 1) {
		BossManagers[1].spawn = get_time_ms();
		return 1;
	}
	if (!BossManagers[0].alive && !BossManagers[1].alive) return 2;
	return -1;
}

static void damage_boss(int idx, int amount) {
	if (idx < 0 || idx >= BOSS_COUNT) return;
	BossClass* bc = &BossManagers[idx];
	if (!bc->alive) return;
	bc->life -= amount;
	if (bc->life <= 0) {
		bc->life = 0;
		bc->alive = FALSE;
		currentBoss = -1;
	}
}

static void render_boss(BossClass* self) {
	Boss* b = self->name;
	for (int dy = -1; dy <= 1; ++dy) {
		for (int dx = -2; dx <= 2; ++dx) {
			int sx = b->x + dx;
			int sy = b->y + dy;
			if (sx < 0 || sx >= XSIZE || sy < 0 || sy >= YSIZE) continue;
			// 테두리는 outline, 내부는 shape
			if (dy == -1 || dy == 1 || dx == -2 || dx == 2) {
				screen[sy][sx] = b->outline;
			}
			else {
				screen[sy][sx] = b->shape;
			}
		}
	}
}

static void check_boss_collision() {
	int lvl = get_level();
	int bcount = (int)BulletManagers[lvl].count;
	Bullet* buf = BulletManagers[lvl].buf;
	int idx = currentBoss;
	if (idx < 0 || !BossManagers[idx].alive) return;
	Boss* b = BossManagers[idx].name;
	for (int j = 0; j < bcount; ++j) {
		if (buf[j].x >= b->x - 2 && buf[j].x <= b->x + 2 &&
			buf[j].y >= b->y - 1 && buf[j].y <= b->y + 1) {
			damage_boss(idx, 1);
			add_score(1);
			buf[j] = buf[--BulletManagers[lvl].count];
			break;
		}
	}
}

static void check_boss_bullet_collision() {
	for (int bi = 0; bi < BOSS_COUNT; ++bi) {
		BulletClass* mgr = &BossBulletManagers[bi];
		for (int j = 0; j < mgr->count; ++j) {
			Bullet* b = &mgr->buf[j];
			int dx = b->x - player.x;
			int dy = b->y - player.y;
			bool_t hit = FALSE;
			if (shield.active) {
				if (abs(dx) <= 1 && abs(dy) <= 1) hit = TRUE;
			}
			else {
				if (dx == 0 && dy == 0) hit = TRUE;
			}
			if (hit) {
				if (shield.active) {
					deactive_shield();
					add_score(1);
					check_exp();
				}
				else {
					minus_death_count();
					reset_item();
					set_player_position(XSIZE / 2, YSIZE - 2);
				}
				mgr->buf[j] = mgr->buf[--mgr->count];
				return;
			}
		}
	}
}

void init_boss() {
	currentBoss = -1;
	BossManagers[0].name->x = XSIZE / 2;
	BossManagers[0].name->y = 3;
	BossManagers[0].life = BOSS_D_HP;
	BossManagers[1].name->x = 2;
	BossManagers[1].name->y = 3;
	BossManagers[1].life = BOSS_M_HP;
	for (int i = 0; i < BOSS_COUNT; ++i) {
		BossManagers[i].alive = TRUE;
		BossManagers[i].spawn = 0;
		BossManagers[i].last_move_ms = 0;
	}
	init_boss_bullets();
}

static void init_boss_bullets() {
	Timestamp now = get_time_ms();
	for (int i = 0; i < BOSS_COUNT; ++i) {
		BossBulletManagers[i].count = 0;
		BossBulletManagers[i].last_spawn_ms = now;
		BossBulletManagers[i].last_move_ms = now;
	}
}