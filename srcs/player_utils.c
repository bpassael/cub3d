#include "../cub3d.h"

void    init_player_in_map(t_map *map)
{
    t_player    *player_data;

    //allocate memory 
    player_data = (t_player *) malloc(sizeof(t_player));

    if (player_data == NULL)
    {
        ft_error("Malloc failed in player init");
        return ;
    }

    player_data->x_pos = map->player_x;
    player_data->y_pos = map->player_y;
    player_data->move_step = MOVE_STEP;

    player_data->angle_deg = 90;
    player_data->angle_rad = (player_data->angle_deg * PI) / 180;
    player_data->move_step = ROTAT_STEP;

    map->player = player_data;

};