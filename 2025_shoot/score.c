#include "score.h"

int score = 0;

int rank() {
	char answer;
	while (1) {
		system("cls");
		printf(" *game over*\n");
		printf("\n ���� ����: %d\n", score);
		printf(" ������ ��� �Ͻðڽ��ϱ�(y/n)?: ");
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
	printf(" ����� �̸��� �����ּ���: ");
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