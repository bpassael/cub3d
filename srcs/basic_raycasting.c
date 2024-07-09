#include "../cub3d.h"

//for now works only with North direction
//and don't include angles in computations
double compute_distance_to_wall(t_map *map)
{
    double distance;

    //hardcoded wall coordinates

    int x_wall = map->player_x;
    int y_wall = 0;

    distance = pow((map->player_x - x_wall), 2) + pow((map->player_y - y_wall), 2);
    distance = sqrt(distance);

    return distance;
};

