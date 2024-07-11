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
    //compute x coord for camera vector
    map->player->camera_x = ((2 * map->player->x_pos) / matrix->width) - 1;

    //compute direction vector
    map->player->ray_dir_x = map->player->dir_x + map->player->plane_x * map->player->camera_x;
    map->player->ray_dir_y = map->player->dir_y + map->player->plane_y * map->player->camera_x;

};


void    dda_compute_steps(t_map *map, t_screen_matrix *matrix)
{
    double  delta_dist_x;
    double  delta_dist_y;

    delta_dist_x = fabs(1 / map->player->ray_dir_x);
    delta_dist_y = fabs(1 / map->player->ray_dir_y);

    map->player->map_x = (int)map->player->x_pos;
    map->player->map_y = (int)map->player->y_pos;
    

    //which direction on x axis to choose
    if (map->player->ray_dir_x < 0)
    {
        map->player->step_x = -1;
        map->player->side_dist_x = (map->player->x_pos - map->player->map_x) * delta_dist_x;
    }
    else
    {
        map->player->step_x = 1;
        map->player->side_dist_x = (map->player->map_x + 1 - map->player->x_pos) * delta_dist_x;
    }
    //which direction on y axis to choose
    if (map->player->ray_dir_y < 0)
    {
        map->player->step_y = -1;
        map->player->side_dist_y = (map->player->y_pos - map->player->map_y) * delta_dist_y;
    }
    else
    {  
        map->player->step_y = 1;
        map->player->side_dist_y = (map->player->map_y + 1 - map->player->y_pos) * delta_dist_y;
    }



};

void    raycast(t_map *map, t_screen_matrix *matrix)
{   
    matrix->x_scr = 0;
    while (matrix->x_scr < WIDTH)
    {
        /* raycast loop */
        compute_ray_direction(map, matrix);
        dda_compute_steps(map, matrix);

        matrix->x_scr++;
    }
    
};

