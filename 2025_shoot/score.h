#pragma once
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include "constant.h"
#include "screen.h"

// ����
int add_score();
void init_score();
int get_score();

// ��ũ
int rank();
int read_rankers();		//rank.txt ���� ��Ŀ ���� �о����
int write_rankers();	//rank.txt ���� ��Ŀ ���� �����ϱ�