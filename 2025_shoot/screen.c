#include "screen.h"

static int show_screen_whole();			// 스크린 전체 출력
static void clear_buffer();				// 화면 버퍼 초기화

char screen[YSIZE][XSIZE];

static void clear_buffer() {
	for (int y = 0; y < YSIZE; y++) {
		for (int x = 0; x < XSIZE; x++) {
			if (y == 0)
				screen[y][x] = '_';
			else if (y == YSIZE - 1)
				screen[y][x] = '=';
			else
				screen[y][x] = ' ';
			if (x == 0 && y != 0 && y != YSIZE - 1)
				screen[y][x] = '|';
			else if (x == XSIZE - 1 && y != 0 && y != YSIZE - 1)
				screen[y][x] = '|';
		}
	}
}

static int show_screen_whole() {
	enum {
		EXIT_LEN = sizeof(" exit: q\n") - 1,
		RESTART_LEN = sizeof("\t restart: r\n") - 1,
		SHIELD_LEN = sizeof("\n shield:999") - 1,							// 최대 3자리 수
		DEATH_LEN = sizeof("\t\t\t    death_count:999") - 1,				// 최대 3자리 수
		SCORE_LEN = sizeof("\t\t      score:999\n") - 1,					// 최대 3자리 수
		LEVEL_LEN = sizeof("\t\t\t\t\t       level:III")					
	};
	static char buf[
		SHIELD_LEN +
			(XSIZE + 1) * YSIZE +
			EXIT_LEN +
			RESTART_LEN +
			DEATH_LEN +
			SCORE_LEN +
			LEVEL_LEN
	];

	char* p = buf;

	// shield_cout
	int k = sprintf(p, "\n shield: %3d", get_shield_count());
	p += k;

	// death_cout
	int d = sprintf(p, "\t\t\t    death_count: %3d", get_death_count());
	p += d;

	// score
	int s = sprintf(p, "\t\t      score: %3d\n", get_score());
	p += s;

	for (int y = 0; y < YSIZE; y++) {
		memcpy(p, screen[y], XSIZE);
		p += XSIZE;
		*p++ = '\n';
	}
	
	// exit
	memcpy(p, " exit: q", EXIT_LEN);
	p += EXIT_LEN;

	// restart
	memcpy(p, "\t restart: r", RESTART_LEN);
	p += RESTART_LEN;

	// bullet speed
	int b = sprintf(p, "\t\t\t\t\t       level:%3s\n", get_bullet_lev());
	p += b;

	fwrite(buf, 1, p - buf, stdout);
	fflush(stdout);
	return 0;
}

int render_screen() {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD home = { 0, 0 };
	SetConsoleCursorPosition(hOut, home);
	clear_buffer();
	draw_bullets();
	draw_enemy();
	draw_skill();
	draw_player();
	show_screen_whole();
	return 0;
}

int start_screen() {
	set_player_position(XSIZE / 2, YSIZE - 2);
	init_enemy();
	init_death_count();
	init_shield_count();
	init_score();
	deactive_shield();
	init_bullet();
	render_screen();
	return 0;
}
