#include "fighter.h"

fighterA player = {
    .x = 0,
    .y = 0,
    .shape = '^'
};

Entity enemy = {
    .x = 0,
    .y = 0,
    .shape = 'V',
    .alive = true
};

// ���� ��ǥ�� �̵�
int set_player_position(int new_x, int new_y) {
    player.x = new_x;
    player.y = new_y;
    //screen[player.y][player.x] = player.shape;
    return 0;
}

// ���(dx, dy)��ŭ �̵�
int move_player(int dx, int dy) {
    player.x += dx;
    player.y += dy;
    return 0;
}
