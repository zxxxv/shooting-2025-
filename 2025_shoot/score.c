#include "score.h"

int rank_count = 0;
int node_count = 0;

int rank() {
	char answer;
	init_rank();
	//if (read_rankers()) return 1;
	while (1) {
		system("cls");
		printf(" *game over*\n");
		printf("\n 현재 점수: %d\n", score);
		printf(" 점수를 등록 하시겠습니까(y/n)?: ");
		scanf_s("%c%*c", &answer, 1);
		if (answer == 'y') {
			//add_ranker();
			//show_rank();
			break;
		}
		else if (answer == 'n') break;
		else continue;
	}
	return 0;
}

Node *make_node(char *nick, Node *next) {
	Node* rank = malloc(sizeof(Node));
	if (rank == NULL) return (Node *)NULL;
	strcpy_s(rank->name, strlen(nick), nick);
	if (next == (Node *)NULL) rank->next = NULL;
	else rank->next = next;
	return rank;
}

void add_ranker() {
	char nick[32];
	printf(" 등록할 이름을 적어주세요: ");
	scanf_s("%31s", nick, (unsigned)sizeof(nick));

	int score = get_score();
	int index = find_index(rankers, score, 0, RANK_MAX);

	//if (rank_count == 0) {
	//	rankers[0]->score = get_score();
	//	rankers[0]->first = make_node(nick, (Node *)NULL);
	//	rank_count++;
	//}
	//else {
	//	int i = 0;
	//	int score = get_score();
	//	// 삽입할 위치 찾기
	//	int mid = rank_count / 2;
	//	if (rankers[mid] == score) {
	//		Node *next = rankers[mid]->first;
	//		rankers[mid]->first = make_node(nick, next);
	//		rank_count++;
	//	}
	//	if (rankers[mid] > score) {

	//	}
	//		//todo
	//}
}

int find_index(Rankers *arr, int score, int start, int end) {
	int mid, count;
	count = end - start;
	if (count == 0) return start;
	else {
		mid = start + count / 2;
		if (arr[mid].score == score) return mid;
		else if (arr[mid].score > score) return find_index(arr, score, start, mid);
		else return find_index(arr, score, mid +1 , end);
	}
}

int read_rankers() {
	FILE* fp;
	fopen_s(&fp, "rank.txt", "r");
	if (fp == NULL) return 1;
	// TODO
	fclose(fp);
	return 0;
}

void init_rank() {
	for (int i = 0; i < RANK_MAX; i++) {
		rankers[i].score = i;
		rankers[i].first = (Node *)NULL;
	}
}

void show_rank() {
	system("cls");
	printf("\n *Rank*\n");
	// todo
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