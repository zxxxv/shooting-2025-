#pragma once
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include "constant.h"
#include "screen.h"

// 점수
int add_score();
void init_score();
int get_score();

// 랭크
int rank();
int read_rankers();		//rank.txt 에서 랭커 정보 읽어오기
int write_rankers();	//rank.txt 에서 랭커 정보 저장하기