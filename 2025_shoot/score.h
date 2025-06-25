#pragma once
#include <stdio.h>
#include <windows.h>

typedef struct Node {
	char name[20];
	int final_score;
	struct Node* next;
} Node;

static Node ranker[100];
static int score;

int rank();
int add_rank();
int add_score();
void init_score();
void show_rank();
int get_score();