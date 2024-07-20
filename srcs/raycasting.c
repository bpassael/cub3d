#include "../cub3d.h"

void compute_ray_direction(t_map *map, t_screen_matrix *matrix) 
{  
    // Compute x coordinate for the camera vector
    map->player->camera_x = 2.0 * matrix->x_scr / (double)WIDTH - 1.0;

    // Compute direction vector
    map->player->ray_dir_x = map->player->dir_x + map->player->plane_x * map->player->camera_x;
    map->player->ray_dir_y = map->player->dir_y + map->player->plane_y * map->player->camera_x;
}

void dda_compute_steps(t_map *map, t_screen_matrix *matrix)
{   
    double delta_dist_x;
    double delta_dist_y;

    delta_dist_x = fabs(1 / map->player->ray_dir_x);
    delta_dist_y = fabs(1 / map->player->ray_dir_y);

    map->player->delta_dist_x = delta_dist_x;
    map->player->delta_dist_y = delta_dist_y;

    // Set map_x and map_y (which block our player is)
    map->player->map_x = (int)map->player->x_pos;
    map->player->map_y = (int)map->player->y_pos;

    // Which direction on x axis to choose
    if (map->player->ray_dir_x < 0)
    {
        map->player->step_x = -1;
        map->player->side_dist_x = (map->player->x_pos - map->player->map_x) * delta_dist_x;
    }
    else
    {
        map->player->step_x = 1;
        map->player->side_dist_x = (map->player->map_x + 1.0 - map->player->x_pos) * delta_dist_x;
    }

    // Which direction on y axis to choose
    if (map->player->ray_dir_y < 0)
    {
        map->player->step_y = -1;
        map->player->side_dist_y = (map->player->y_pos - map->player->map_y) * delta_dist_y;
    }
    else
    {  
        map->player->step_y = 1;
        map->player->side_dist_y = (map->player->map_y + 1.0 - map->player->y_pos) * delta_dist_y;
    }
}

int dda_find_wall(t_map *map, t_screen_matrix *matrix) // Returns side = 0 or side = 1
{   
    int side;

    while (1)
    {
        if (map->player->side_dist_x < map->player->side_dist_y)
        {
            map->player->side_dist_x += map->player->delta_dist_x;
            map->player->map_x += map->player->step_x;
            side = 0;
        }
        else
        {
            map->player->side_dist_y += map->player->delta_dist_y;
            map->player->map_y += map->player->step_y;
            side = 1;
        }
        if (map->map[map->player->map_y][map->player->map_x] == '1')
            break;
    }
    return (side);
}

void draw_vert_stripe(t_session *session, int draw_start, int draw_end, int color)
{   
    int x_scr;
    int i;

    x_scr = session->matrix->x_scr;

    // Draw sky first
    for (i = 0; i < draw_start; i++)
    {
        session->matrix->matrix[i][x_scr].x = x_scr;
        session->matrix->matrix[i][x_scr].y = i;
        session->matrix->matrix[i][x_scr].color = create_trgb(0, 100, 200, 100);
    }

    // Draw wall
    for (i = draw_start; i < draw_end; i++)
    {
        session->matrix->matrix[i][x_scr].x = x_scr;
        session->matrix->matrix[i][x_scr].y = i;
        session->matrix->matrix[i][x_scr].color = color;
    }

    // Draw ceiling
    for (i = draw_end; i < session->matrix->height; i++)
    {
        session->matrix->matrix[i][x_scr].x = x_scr;
        session->matrix->matrix[i][x_scr].y = i;
        session->matrix->matrix[i][x_scr].color = create_trgb(0, 250, 0, 40);
    }
}

void raycast(t_map *map, t_screen_matrix *matrix, t_session *session)
{   
    int side;
    double wall_dist;
    int line_height;
    int draw_start;
    int draw_end;

    int color;

    matrix->x_scr = 0;
    while (matrix->x_scr < WIDTH)
    {
        /* Raycast loop */
        compute_ray_direction(map, matrix);
        dda_compute_steps(map, matrix);
        side = dda_find_wall(map, matrix);

        // Calculate wall height
        if (side == 0)
            wall_dist = (map->player->map_x - map->player->x_pos + (1 - map->player->step_x) / 2) / map->player->ray_dir_x;
        else
            wall_dist = (map->player->map_y - map->player->y_pos + (1 - map->player->step_y) / 2) / map->player->ray_dir_y;

        // Don't allow distance to go to zero
        if (wall_dist < 0.1)
            wall_dist = 0.1;

        color = create_trgb(0, 20, 150, 40);

        line_height = (int)(matrix->height / wall_dist);

        draw_start = -line_height / 2 + matrix->height / 2;
        draw_end = line_height / 2 + matrix->height / 2;

        // Avoid drawing beyond the screen
        if (draw_start < 0)
            draw_start = 0;
        if (draw_end >= matrix->height)
            draw_end = matrix->height - 1;

        draw_vert_stripe(session, draw_start, draw_end, color);
        matrix->x_scr++;
    }
}
