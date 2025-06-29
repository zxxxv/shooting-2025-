#include "score.h"

int score = 0;

int rank() {
	char answer;
	while (1) {
		system("cls");
		printf(" *game over*\n");
		printf("\n 현재 점수: %d\n", score);
		printf(" 점수를 등록 하시겠습니까(y/n)?: ");
		scanf_s("%c%*c", &answer, 1);
		if (answer == 'y') {
			add_rank();
			break;
		}
		else if (answer == 'n') break;
		else continue;
	}
	return 0;
}

int add_rank() {
	char nick[20] = { 0 };
	printf(" 등록할 이름을 적어주세요: ");
	scanf_s("%s", nick, (unsigned)sizeof(nick));
	system("cls");
	show_rank();
	return 0;
}

void show_rank() {
	printf("\n *High Scores*\n");
	//todo
}

int add_score() {
	return ++score;
}

int get_score() {
	return score;
}

void init_score() {
	score = 0;
}