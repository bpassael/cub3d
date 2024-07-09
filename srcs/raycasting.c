#include "../cub3d.h"

//for now works only with North direction
//and don't include angles in computations
double compute_distance_to_wall(t_map *map)
{
    double distance;
    
    double x_wall = map->player->x_pos;
    //hardcoded for now
    double y_wall = 0.0;
    
    distance = pow((map->player->x_pos - x_wall), 2) + pow((map->player->y_pos - y_wall), 2);
    distance = sqrt(distance);

    return distance;
};

void    compute_ray_direction(t_map *map, t_screen_matrix *matrix)
{
    map->player->camera_x = (2 * map->player->x_pos) / matrix->x_scr;
    map->player->ray_dir_x = map->player->dir_x + map->player->plane_x * map->player->camera_x;
    map->player->ray_dir_y = map->player->dir_y + map->player->plane_y * map->player->camera_x;

};


void    raycast(t_map *map, t_screen_matrix *matrix)
{   
    matrix->x_scr = 0;
    while (matrix->x_scr < WIDTH)
    {
        /* raycast */
        matrix->x_scr++;
    }
    
};

