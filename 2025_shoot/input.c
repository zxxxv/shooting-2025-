#include "input.h"

int game_over = 0;
int quit = 0;
int ckey = 0;

int (*input[])() = { handle_input, handle_quit };

int handle_input() {
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
		if (c == 32) skill();
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

int handle_quit() {
	//char *one;
	//system("cls");
	printf("\n 종료(q) 재시작(r)\t:");
	//scanf("%c", one);
	//if (!_kbhit()) return 0;
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

void skill() {
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