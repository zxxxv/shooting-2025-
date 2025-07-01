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

// Á¡¼ö
int rank();
int add_score();
void init_score();
int get_score();

// ·©Å©
void init_rank();
int add_ranker();
void show_rank();
int find_index(Rankers* arr, int score, int start, int end);
int read_rankers();
int write_rankers();
Rankers* make_node(char* nick, int index);