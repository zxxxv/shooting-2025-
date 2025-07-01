#include "score.h"

typedef struct Node {
	char name[32];
	//int final_score;
	struct Node* next;
} Node;

typedef struct Rankers {
	int score;
	struct Node* first;
} Rankers;

static int score = 0;
static Rankers rankers[RANK_MAX];

static int  add_ranker(void);
static void show_rank(void);
static Rankers* make_node(char* nick, int index);
static int  find_index(Rankers* arr, int score, int start, int end);
static int  read_rankers(void);
static int  write_rankers(void);

int rank() {
	char answer;
	//if (read_rankers()) return 1;
	while (1) {
		system("cls");
		printf(" *game over*\n");
		printf("\n 현재 점수: %d\n", score);
		printf("\n 점수를 등록 하시겠습니까(y/n)?: ");
		scanf_s("%1c%*c", &answer, 1);
		if (answer == 'y') {
			if (add_ranker()) return 1;
			show_rank();
			break;
		}
		else if (answer == 'n') break;
		else continue;
	}
	return 0;
}

static Rankers* make_node(char* nick, int index) {
	Node* rank = malloc(sizeof(Node));
	if (rank == NULL) return (Rankers*)NULL;
	strcpy_s(rank->name, strlen(nick)+1, nick);
	rank->next = NULL;
	if (!rankers[index].first) rankers[index].first = rank;
	else {
		Node* next = rankers[index].first;
		rankers[index].first = rank;
		rankers[index].first->next = next;
	}
	return rankers;
}

static int add_ranker() {
	char nick[32];
	printf("\n 등록할 이름을 적어주세요: ");
	scanf_s("%31s%*c", nick, (unsigned)sizeof(nick));
	int score = get_score();
	//int index = find_index(rankers, score, 0, RANK_MAX);
	if (!make_node(nick, score)) return 1;
	//if (write_rankers()) return 2;
	return 0;
}

static int find_index(Rankers *arr, int score, int start, int end) {
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

static int read_rankers() {
	FILE* fp;
	fopen_s(&fp, "rank.txt", "r");
	if (fp == NULL) return 1;
	// TODO
	fclose(fp);
	return 0;
}

static int write_rankers() {
	FILE* fp;
	fopen_s(&fp, "rank.txt", "w");
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

static void show_rank() {
	system("cls");
	printf("\n *Rank*\n");
	int seq = 1;
	for (int i = 1; i <= RANK_MAX; i++) {
		if (!rankers[RANK_MAX - i].first) continue;
		else {
			Node* head, *next;
			head = rankers[RANK_MAX - i].first;
			next = head->next;
			printf("\n %d. [%d] ", seq++, rankers[RANK_MAX - i].score);
			while (head != NULL) {
				printf("*%s* ", head->name);
				if (!next) break;
				head = next;
				next = head->next;
			}
			putchar('\n');
		}
	}
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