#include <stdio.h>
#include <conio.h>
#include "fighter.h"
#include "screen.h"


int handle_input();
int update_entities();
static int game_over = 0;

int main() {
	start_screen();
	while (!game_over) {
		handle_input();
		//update_entities();
	}
}

int handle_input() {
 	while (1) {
		int c = _getch();
		if (c == 'q' || c == 'Q') {
			game_over = 1;
			break;
		}
		if (c == 224) {
			c = _getch();
			switch (c) {
				case 72:
					move_player(0, -1);	//����
					//printf("���� ȭ��ǥ\n");
					break;
				case 80:
					move_player(0, 1);	//�Ʒ���
					//printf("�Ʒ��� ȭ��ǥ\n");
					break;
				case 77:
					move_player(1, 0);	//������
					//printf("������ ȭ��ǥ\n");
					break;
				case 75:
					move_player(-1, 0);	//����
					//printf("���� ȭ��ǥ\n");
					break;
				}
		}
		render_screen();
	}
	return 0;
}

int update_entities() {

	return 0;
}