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

