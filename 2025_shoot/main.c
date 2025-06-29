#include <stdlib.h>
#include <windows.h>
#include "fighter.h"
#include "screen.h"
#include "input.h"
#include "score.h"

int main() {
	start_screen();
	while (!game_over) {
		handle_input();
		render_screen();
		Sleep(20);
	}
	//atexit(rank);
	rank();
	return 0;
}
