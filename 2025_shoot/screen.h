#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "fighter.h"

#define XSIZE	80
#define	YSIZE	25

extern char screen[YSIZE][XSIZE];

static void clear_buffer();
int show_screen_whole();
int start_screen();			// 
int render_screen();		//
int show_screen();			//