#include "input.h"

static void key_skill();
static int handle_input();
static int handle_quit();
static int handle_start();

int game_over = 0;
int quit = 0;

int (*input[])() = { handle_input, handle_quit, handle_start };

static int handle_input() {
	while (1) {
		if (!_kbhit()) return 0;
		int c = _getch();
		int r = 0;
		if (c == 'q' || c == 'Q') {
			game_over = 1;
			break;
		}
		if (c == 'r' || c == 'R') {
			start_screen();
		}
		if (c == 32) key_skill();
		if (c == 224) {
			c = _getch();
			switch (c) {
			case 72:
				r = update_player(0, -1);	//위쪽
				break;
			case 80:
				r = update_player(0, 1);	//아래쪽
				break;
			case 77:
				r = update_player(1, 0);	//오른쪽
				break;
			case 75:
				r = update_player(-1, 0);	//왼쪽
				break;
			}
		}
		if (!r) render_screen();
		else continue;
	}
	return 0;
}

static int handle_quit() {
	printf("\n 종료(q)  재시작(r)\n");
	int c = _getch();
	int r = 0;
	if (c == 'q' || c == 'Q') {
		quit_game();
	}
	if (c == 'r' || c == 'R') {
		system("cls");
		init_game();
		start_screen();
	}
	return 0;
}

static int handle_start() {
	show_screen[0]();
	/*printf("\n * choose you fighter to play*\n");
	printf("\n1. ^  2. @  3. #  4. w  5. A  6. O  7. o\n");
	printf("\ninput number: ");*/
	// 선택 하면 실행
	char c;
	do c = _getch();
	while (c < 49 || c > 49 + FIGHTER);
	set_player(c-49);
	return 0;
}

static void key_skill() {
	int shCount = get_shield_count();
	if (!shCount && !shield_status()) return;
	shield_status() ? deactive_shield() : active_shield();
}

void init_game() {
	quit = 0;
	game_over = 0;
}

void quit_game() {
	quit = 1;
}