#include "input.h"

static void key_skill();
static int handle_input();
static int handle_quit();
static int handle_start();

int game_over = 0;
int quit = 0;
int game_clear = 0;

int (*input[])() = { handle_input, handle_quit, handle_start };

static int handle_input() {
	while (1) {
		if (!_kbhit()) return 0;
		int c = _getch();
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
				update_player(0, -1);	//위쪽
				break;
			case 80:
				update_player(0, 1);	//아래쪽
				break;
			case 77:
				update_player(1, 0);	//오른쪽
				break;
			case 75:
				update_player(-1, 0);	//왼쪽
				break;
			}
		}
		else continue;
	}
	return 0;
}

static int handle_quit() {
	hide_console_cursor();
	printf("\n\033[1;35m 종료(q)  재시작(r)\033[0m\n");
	int c = 0;
	while (c = _getch()) {
		if (c != 113 && c != 114 && c != 81 && c != 82) continue;
		if (c == 'q' || c == 'Q') {
			quit_game();
			break;
		}
		if (c == 'r' || c == 'R') {
			system("cls");
			init_game();
			break;
		}
	}
	return 0;
}

static int handle_start() {
	system("cls");
	hide_console_cursor();
	show_screen[0]();
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