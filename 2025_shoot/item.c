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

// ������ ������ ����
// '+' ������ �߻� �ӵ� up
// '=' �߻�ü ����

void spawn_item() {

}