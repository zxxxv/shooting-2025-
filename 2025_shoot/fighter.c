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

// 절대 좌표로 이동
int set_player_position(int new_x, int new_y) {
    player.x = new_x;
    player.y = new_y;
    //screen[player.y][player.x] = player.shape;
    return 0;
}

// 상대(dx, dy)만큼 이동
int move_player(int dx, int dy) {
    player.x += dx;
    player.y += dy;
    return 0;
}
