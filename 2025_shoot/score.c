#include "score.h"

typedef struct Ranker {
	char name[32];
	struct Ranker* next;
} Ranker;

typedef struct Rankers {
	int score;
	struct Ranker* first;
} Rankers;

static int score = 0, rc = 0;					// rc -> rank count : Rankers 배열에 채워진 수
static bool_t dirty = 0;						// 추가 랭커 있는지 표시
static Rankers rankers[RANK_MAX] = { 0 };

static int  add_ranker();
static void show_rank();
static Rankers* make_node(char* nick, int index);
static int  find_index(Rankers* arr, int score, int start, int end);
static int free_rankers();

static void insertion_sort(Rankers* arr, int start, int end);
static void quick_sort(Rankers* arr, int start, int end);
static int partition(Rankers* arr, int start, int end);
static void swap(Rankers* x, Rankers* y);

int rank() {
	char answer;
	show_console_cursor();
	system("cls");
	game_clear ?
		printf("\n\033[1;34m * game clear *\033[0m\n") :
		printf("\n\033[1;34m * game over *\033[0m\n");
	printf("\n\033[1;36m score: %d\033[0m\n", score);
	while (1) {
		printf("\n\033[1;33m 점수를 등록 하시겠습니까(y/n)?: \033[0m");
		scanf_s("%1c%*c", &answer, 1);
		if (answer == 'y') {
			if (add_ranker()) return 1;
			dirty = 1;
			show_rank();
			break;
		}
		else if (answer == 'n') break;
		else continue;
	}
	return 0;
}

static Rankers* make_node(char* nick, int index) {
	Ranker* rank = malloc(sizeof(Ranker));
	if (rank == NULL) return (Rankers*)NULL;
	strcpy_s(rank->name, strlen(nick)+1, nick);
	rank->next = NULL;
	if (!rankers[index].first) rankers[index].first = rank;
	else {
		Ranker* next = rankers[index].first;
		rankers[index].first = rank;
		rankers[index].first->next = next;
	}
	return rankers;
}

static int add_ranker() {
	char nick[32];
	int is_sorted = 1;
	printf("\n\033[1;33m 등록할 이름을 적어주세요: \033[0m");
	scanf_s("%31s%*c", nick, (unsigned)sizeof(nick));
	int score = get_score();
	int index = find_index(rankers, score, 0, rc);
	if (index == -1) {
		index = rc;
		rankers[rc++].score = score;
		is_sorted = 0;
	}
	if (!make_node(nick, index)) return 1;
	if (!is_sorted) insertion_sort(rankers, 0, rc);
	return 0;
}

static int find_index(Rankers *arr, int score, int start, int end) {
	int mid, count;
	count = end - start;
	if (count == 0) return -1;
	else {
		mid = start + count / 2;
		if (arr[mid].score == score) return mid;
		else if (arr[mid].score > score) return find_index(arr, score, start, mid);
		else return find_index(arr, score, mid +1 , end);
	}
}

static void insertion_sort(Rankers* arr, int start, int end) {
	for (int i = start + 1; i < end; i++) {
		Rankers key = arr[i];
		int j = i - 1;
		// key.score 보다 큰 요소들을 한 칸씩 뒤로 이동
		while (j >= start && arr[j].score > key.score) {
			arr[j + 1] = arr[j];
			j--;
		}
		// 알맞은 위치에 key 삽입
		arr[j + 1] = key;
	}
}

static void quick_sort(Rankers *arr, int start, int end) {
	if (end - start > 0) {
		int q = partition(arr, start, end);
		quick_sort(arr, start, q);
		quick_sort(arr, q + 1, end);
	}
}

static int partition(Rankers* arr, int start, int end) {
	int p = arr[end - 1].score;
	int i = start - 1;
	for (int j = start; j < end - 1; j++)
		if (arr[j].score < p) swap(&arr[++i], &arr[j]);
	swap(&arr[i + 1], &arr[end - 1]);
	return i + 1;
}

static void swap(Rankers* x, Rankers* y) {
	Rankers temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

int read_rankers() {
	FILE* fp;
	char name_buf[1024];
	int scoreR, dcount = 0, same = 0;
	char* name, * next_name;
	fopen_s(&fp, "rank.txt", "r");
	if (!fp) return 1;
	while (fscanf_s(fp, "$%d$", &scoreR) == 1) {
		if (fscanf_s(fp, "%1023[^\r\n$]", name_buf, (unsigned)sizeof(name_buf)) != 1) {
			break;
		}
		// 같은 점수가 있는지 찾기
		int idx = -1;
		for (int i = 0; i < rc; i++) {
			if (rankers[i].score == scoreR) {
				idx = i;
				break;
			}
		}
		// 중복이면 기존 idx에, 아니면 새 n에
		if (idx < 0) {
			if (rc >= RANK_MAX) {
				fprintf(stderr, "랭킹 최대치(%d) 초과\n", RANK_MAX);
				break;
			}
			idx = rc;
			rankers[idx].score = scoreR;
			rc++;
		}
		name = strtok_s(name_buf, ":", &next_name);
		while (name) {
			if (*name) make_node(name, idx);
			name = strtok_s(NULL, ":", &next_name);
		}
	}
	fclose(fp);
	quick_sort(rankers, 0, rc);
	return 0;
}

int write_rankers() {
	if (!dirty) return 0;
	FILE* fp;
	fopen_s(&fp, "rank.txt", "w");
	if (fp == NULL) return 1;
	for (int i = 0; i < rc; i++) {
		fprintf(fp, "$%d$", rankers[i].score);
		Ranker* cur = rankers[i].first;
		while (cur) {
			fprintf(fp, "%s:", cur->name);
			cur = cur->next;
		}
	}
	fputc('\n', fp);
	fclose(fp);
	free_rankers();
	return 0;
}

static int free_rankers() {
	Ranker* cur, * next;
	for (int i = 0; i < rc; i++) {
		cur = rankers[i].first;
		while (cur) {
			next = cur->next;
			free(cur);
			cur = next;
		}
		rankers[i].first = NULL;
	}
	return 0;
}

static void show_rank() {
	system("cls");
	printf("\n\033[1;35m *Rank*\033[0m\n");
	int seq = 1;
	for (int i = 1; i <= RANK_MAX; i++) {
		if (!rankers[RANK_MAX - i].first) continue;
		else {
			Ranker* head, *next;
			head = rankers[RANK_MAX - i].first;
			next = head->next;
			printf("\n\033[1;36m == Score: %d ==\033[0m\n", rankers[RANK_MAX - i].score);
			while (head != NULL) {
				printf("\033[1;33m * %s *\033[0m\n", head->name);
				if (!next) break;
				head = next;
				next = head->next;
			}
			putchar('\n');
		}
	}
}

int add_score(int number) {
	score += number;
	return score;
}

int get_score() {
	return score;
}

void init_score() {
	score = 0;
}