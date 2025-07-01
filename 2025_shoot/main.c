#include <stdlib.h>
#include <windows.h>
#include "fighter.h"
#include "screen.h"
#include "input.h"
#include "score.h"
#include "skill.h"

int main() {
	start_screen();
	while (!game_over) {
		handle_input();
		render_screen();
		Sleep(20);
	}
	//atexit(rank);
	if (rank()) return 1;
	return 0;
}
