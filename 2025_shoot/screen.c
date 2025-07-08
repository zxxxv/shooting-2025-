#include "screen.h"

static int show_screen_whole();			// 스크린 전체 출력
static int show_choose_screen();
static void clear_buffer();				// 화면 버퍼 초기화
void (*show_screen[])() = {show_choose_screen , show_screen_whole};

char screen[YSIZE][XSIZE];

int init() {
	srand((unsigned)time(NULL));
	if (read_rankers()) return 1;
	input[2]();
	return 0;
}

int end() {
	if (write_rankers()) return 1;
	return 0;
}

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

static int show_choose_screen() {
	const char* header = "   SHOOT  2025   ";
	const char* title = " * choose your fighter to play * ";
	const char* options = " [1] ^  [2] #  [3] w  [4] A  ";
	int content_w = (int)strlen(header);
	if ((int)strlen(title) > content_w) content_w = (int)strlen(title);
	if ((int)strlen(options) > content_w) content_w = (int)strlen(options);
	int win_w = content_w + 10;
	int win_h = 9;
	int x0 = (XSIZE - win_w) / 2;
	int y0 = (YSIZE - win_h) / 2;
	// 테두리 그리기
	for (int y = 0; y < win_h; y++) {
		printf("\033[%d;%dH", y0 + y - 1, x0 + 1);
		if (y == 0 || y == win_h - 1) {
			for (int i = 0; i < win_w; i++) putchar('=');
		}
		else {
			putchar('|');
			for (int i = 0; i < win_w - 2; i++) putchar(' ');
			putchar('|');
		}
	}
	// 헤더 출력
	int hx = x0 + (win_w - (int)strlen(header)) / 2 + 1;
	int hy = y0 + 1;
	printf("\033[%d;%dH\033[1;35m%s\033[0m", hy, hx, header);
	// 제목 출력
	int tx = x0 + (win_w - (int)strlen(title)) / 2 + 1;
	int ty = y0 + 3;
	printf("\033[%d;%dH\033[1;33m%s\033[0m", ty, tx, title);
	// 옵션 출력
	int ox = x0 + (win_w - (int)strlen(options)) / 2 + 1;
	int oy = y0 + 5;
	printf("\033[%d;%dH\033[1;36m%s\033[0m", oy, ox, options);
	fflush(stdout);
	return 0;
}

static int show_screen_whole() {
	enum {
		EXIT_LEN = sizeof(" exit: q\n") - 1,
		RESTART_LEN = sizeof("\t restart: r\n") - 1,
		SHIELD_LEN = sizeof("\n shield:99") - 1,							// 최대 2자리 수
		DEATH_LEN = sizeof("\t\t\t    death_count:99") - 1,					// 최대 2자리 수
		SCORE_LEN = sizeof("\t\t      score:999\n") - 1,					// 최대 3자리 수
		SPEED_LEN = sizeof("\t\t       speed:III"),
		LEVEL_LEN = sizeof("\t\t      level:III\n")
	};
	static char buf[
		SHIELD_LEN +
		(XSIZE + 1) * YSIZE +
		EXIT_LEN +
		RESTART_LEN +
		DEATH_LEN +
		SCORE_LEN +
		SPEED_LEN +
		LEVEL_LEN
	];
	char* p = buf;
	// shield_cout
	int k = sprintf(p, "\n shield:%2d", get_shield_count());
	p += k;
	// death_cout
	int d = sprintf(p, "\t\t\t   death_count:%2d", get_death_count());
	p += d;
	// score
	int s = sprintf(p, "\t\t       score:%3d\n", get_score());
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
	int b = sprintf(p, "\t\t      speed:%3s", get_bullet_speed());
	p += b;

	int l = sprintf(p, "\t\t      level:%3s\n", get_bullet_level());
	p += l;
	fwrite(buf, 1, p - buf, stdout);
	fflush(stdout);
	return 0;
}

int render_screen() {
	printf("\033[H");
	clear_buffer();
	draw_bullets();
	draw_enemy();
	draw_skill();
	draw_player();
	show_screen_whole();
	fflush(stdout);
	return 0;
}

int start_screen() {
	printf("\033[2J\033[H");
	hide_console_cursor();
	set_player_position(XSIZE / 2, YSIZE - 2);
	init_enemy();
	init_death_count();
	init_shield_count();
	init_score();
	deactive_shield();
	init_bullets();
	init_item();
	render_screen();
	return 0;
}

void hide_console_cursor() {
	printf("\033[?25l");
	fflush(stdout);
}

void show_console_cursor() {
	printf("\033[?25h");
	fflush(stdout);
}