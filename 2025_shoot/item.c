#include "item.h"

Item item = {
	.x = 0,
	.y = 0,
	.shape = '+'
};

static char item_shape[] = {'+', '='};

void set_item_shape(int n) {
	item.shape = item_shape[n];
}

// 아이템 번갈아 생성
// '+' 먹으면 발사 속도 up
// '=' 발사체 증가

void spawn_item() {

}