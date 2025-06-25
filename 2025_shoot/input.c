#include "input.h"
#include "screen.h"

int game_over = 0;

int handle_input() {
	while (1) {
		if (!_kbhit()) {
			return 0;
		}
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

int skill() {
	active_skill();
	//add_score();
	//minus_death_count();
	return 0;
}

int pause() {
	//todo
	return 0;
}

int resume() {
	//todo
	return 0;
}