#pragma once
#include <stdio.h>
#include <string.h>
#include "constant.h"
#include "screen.h"

// ����
int add_score();		// adder
void init_score();		// setter
int get_score();		// getter

// ��ũ
int rank();
int read_rankers();		//rank.txt ���� ��Ŀ ���� �о����
int write_rankers();	//rank.txt ���� ��Ŀ ���� �����ϱ�