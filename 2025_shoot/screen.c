#include "screen.h"

char screen[YSIZE][XSIZE];

static void clear_buffer() {
	for (int y = 0; y < YSIZE; y++) {
		for (int x = 0; x < XSIZE; x++) {
			if (y == 0 || y == YSIZE - 1)
				screen[y][x] = '-';
			else
				screen[y][x] = ' ';
			if (x == 0)
				screen[y][x] = '[';
			else if (x == XSIZE - 1)
				screen[y][x] = ']';
		}
	}
}

int show_screen() {
	for (int y = 0; y < YSIZE; y++) {
		for (int x = 0; x < XSIZE; x++)
			putchar(screen[y][x]);
		putchar('\n');
	}
	printf(" exit: q\n");
	return 0;
}

int show_screen_whole() {
	enum { MSG_LEN = sizeof(" exit: q\n") - 1 };
	static char buf[(XSIZE + 1) * YSIZE + MSG_LEN];
	char* p = buf;

	for (int y = 0; y < YSIZE; y++) {
		memcpy(p, screen[y], XSIZE);
		p += XSIZE;
		*p++ = '\n';
	}

	memcpy(p, " exit: q\n", MSG_LEN);
	p += 8;

	fwrite(buf, 1, p - buf, stdout);
	fflush(stdout);
	return 0;
}


int render_screen() {
	
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD home = { 0, 0 };
	SetConsoleCursorPosition(hOut, home);

	clear_buffer();
	screen[player.y][player.x] = player.shape;
	//if (enemy.alive) {
	//	screen[enemy.y][enemy.x] = enemy.shape;
	//}
	show_screen_whole();
	return 0;
}

int start_screen() {
	set_player_position(XSIZE / 2, YSIZE - 2);
	render_screen();
	return 0;
}
