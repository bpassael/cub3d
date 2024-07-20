#include "../cub3d.h"

// Function to check if the move is valid and does not cross walls
bool is_move_valid(t_map *map, double new_x_pos, double new_y_pos)
{
    // Check if the new position is within a wall
    if (map->map[(int)floorf(new_y_pos)][(int)floorf(new_x_pos)] == '1')
    {   
        ft_error("You hit the wall!");
        return false;
    }
    return true;
}

void move_player_forward(t_map *map, t_player *player)
{
    double new_x_pos;
    double new_y_pos;

    new_x_pos = player->x_pos + player->dir_x * MOVE_STEP;
    new_y_pos = player->y_pos + player->dir_y * MOVE_STEP;

    if (is_move_valid(map, new_x_pos, new_y_pos))
    {
        player->x_pos = new_x_pos;
        player->y_pos = new_y_pos;
    }
}

void move_player_backward(t_map *map, t_player *player)
{
    double new_x_pos;
    double new_y_pos;

    new_x_pos = player->x_pos - player->dir_x * MOVE_STEP;
    new_y_pos = player->y_pos - player->dir_y * MOVE_STEP;

    if (is_move_valid(map, new_x_pos, new_y_pos))
    {
        player->x_pos = new_x_pos;
        player->y_pos = new_y_pos;
    }
}

void move_player_left(t_map *map, t_player *player)
{
    double new_x_pos;
    double new_y_pos;

    new_x_pos = player->x_pos + player->dir_y * MOVE_STEP;
    new_y_pos = player->y_pos - player->dir_x * MOVE_STEP;

    if (is_move_valid(map, new_x_pos, new_y_pos))
    {
        player->x_pos = new_x_pos;
        player->y_pos = new_y_pos;
    }
}

void move_player_right(t_map *map, t_player *player)
{
    double new_x_pos;
    double new_y_pos;

    new_x_pos = player->x_pos - player->dir_y * MOVE_STEP;
    new_y_pos = player->y_pos + player->dir_x * MOVE_STEP;

    if (is_move_valid(map, new_x_pos, new_y_pos))
    {
        player->x_pos = new_x_pos;
        player->y_pos = new_y_pos;
    }
}

void rotate_player_right(t_player *player)
{
    double old_x;
    double old_y;

    old_x = player->dir_x;
    old_y = player->dir_y;

    player->dir_x = old_x * cos(ROTAT_STEP) - old_y * sin(ROTAT_STEP);
    player->dir_y = old_x * sin(ROTAT_STEP) + old_y * cos(ROTAT_STEP);

    old_x = player->plane_x;
    old_y = player->plane_y;

    player->plane_x = old_x * cos(ROTAT_STEP) - old_y * sin(ROTAT_STEP);
    player->plane_y = old_x * sin(ROTAT_STEP) + old_y * cos(ROTAT_STEP);

}

void rotate_player_left(t_player *player)
{
    double old_x;
    double old_y;

    old_x = player->dir_x;
    old_y = player->dir_y;

    player->dir_x = old_x * cos(-ROTAT_STEP) - old_y * sin(-ROTAT_STEP);
    player->dir_y = old_x * sin(-ROTAT_STEP) + old_y * cos(-ROTAT_STEP);

    old_x = player->plane_x;
    old_y = player->plane_y;

    player->plane_x = old_x * cos(-ROTAT_STEP) - old_y * sin(-ROTAT_STEP);
    player->plane_y = old_x * sin(-ROTAT_STEP) + old_y * cos(-ROTAT_STEP);

    //printf("Updated direction vec after (%f; %f)\n", player->dir_x, player->dir_y);
}
