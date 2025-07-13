#include <stdlib.h>
#include "fighter.h"
#include "screen.h"
#include "input.h"
#include "score.h"
#include "skill.h"

int main() {
	init();
	while (!quit) {
		start_screen();
		while (!game_over) {
			input[quit | game_over]();
			render_screen();
		}
		if (rank()) return 1;
		input[quit | game_over]();
	}
	end();
	return 0;
}

