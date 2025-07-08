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
	// 내부 텍스트 최대 너비 계산
	int content_w = (int)strlen(header);
	if ((int)strlen(title) > content_w) content_w = (int)strlen(title);
	if ((int)strlen(options) > content_w) content_w = (int)strlen(options);
	// 프레임 전체 너비/높이, 화면 중앙 좌표
	int win_w = content_w + 10;   // 좌우 여백 5칸씩
	int win_h = 9;                // 윗줄·아랫줄 + 내·외 7줄
	int x0 = (XSIZE - win_w) / 2;
	int y0 = (YSIZE - win_h) / 2;
	enum { BUF_SIZE = 8192 };
	static char buf[BUF_SIZE];
	char* p = buf;
	// 1) 윈도우 위쪽 여백 (빈 줄)
	for (int i = 0; i < y0; i++) {
		*p++ = '\n';
	}
	// 2) 프레임 본체
	for (int row = 0; row < win_h; row++) {
		// 좌측 여백
		for (int i = 0; i < x0; i++) {
			*p++ = ' ';
		}
		if (row == 0 || row == win_h - 1) {
			// ─── 상·하단 테두리
			for (int i = 0; i < win_w; i++) {
				*p++ = '=';
			}
		}
		else {
			// │   내용   │ 형태
			*p++ = '|';
			int inner_w = win_w - 2;
			// 특정 행에만 텍스트 삽입
			if (row == 2) {
				int indent = (inner_w - (int)strlen(header)) / 2;
				memset(p, ' ', indent);      p += indent;
				memcpy(p, header, strlen(header)); p += strlen(header);
				memset(p, ' ', inner_w - indent - strlen(header)); p += inner_w - indent - strlen(header);
			}
			else if (row == 4) {
				int indent = (inner_w - (int)strlen(title)) / 2;
				memset(p, ' ', indent);     p += indent;
				memcpy(p, title, strlen(title));   p += strlen(title);
				memset(p, ' ', inner_w - indent - strlen(title)); p += inner_w - indent - strlen(title);
			}
			else if (row == 6) {
				int indent = (inner_w - (int)strlen(options)) / 2;
				memset(p, ' ', indent);       p += indent;
				memcpy(p, options, strlen(options)); p += strlen(options);
				memset(p, ' ', inner_w - indent - strlen(options)); p += inner_w - indent - strlen(options);
			}
			else {
				memset(p, ' ', inner_w); p += inner_w;
			}
			*p++ = '|';
		}
		*p++ = '\n';
	}
	fwrite(buf, 1, p - buf, stdout);
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
	system("cls");
	//printf("\033[2J\033[H");
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