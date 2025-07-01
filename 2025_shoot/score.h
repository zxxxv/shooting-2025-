#pragma once
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include "constant.h"

typedef struct Node {
	char name[32];
	//int final_score;
	struct Node* next;
} Node;

typedef struct Rankers {
	int score;
	struct Node* first;
} Rankers;

static Rankers rankers[RANK_MAX];
static int score = 0;

int rank();
void add_ranker();
Node *make_node(char* nick, Node *next);
int add_score();
void init_score();
void show_rank();
int get_score();
int find_index(Rankers* arr[], int score, int start, int end);
int read_rankers();
void init_rank();