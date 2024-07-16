#include "../cub3d.h"

void	init_raycast_data(t_player *player, int x_scr)
{
	player->camera_x = 2 * x_scr /(double)WIDTH -1;
	player->dir_x = player->dir_x + player->plane_x * player->camera_x;
	player->dir_y = player->dir_y + player->plane_y * player->camera_x;
	player->map_x = (int)player->x_pos;
	player->map_y = (int)player->y_pos;
	player->delta_dist_x = fabs(1 / player->dir_x);
	player->delta_dist_y = fabs(1 / player->dir_y);

};

void	determine_dda_dir(t_player *player)
{
	if (player->ray_dir_x < 0)
	{
		player->step_x = -1;
		player->side_dist_x = (player->x_pos - player->map_x) * player->delta_dist_x;
	}
	else
	{
		player->step_x = -1;
		player->side_dist_x = (player->map_x + 1.0 - player->x_pos) * player->delta_dist_x;
	}
	if (player->dir_y < 0)
	{
		player->step_y = -1;
		player->side_dist_y = (player->y_pos - player->map_y) * player->delta_dist_y;
	}
	else
	{
		player->step_y = 1;
		player->side_dist_y = (player->map_y + 1.0 - player->y_pos) * player->delta_dist_y;
	}
};


//Finds where we hit the wall
void	perform_dda(t_player *player, t_map *map)
{
	int hitwall;

	hitwall = 0;

	while (!hitwall)
	{
		if (player->side_dist_x < player->delta_dist_y)
		{
			player->side_dist_x += player->delta_dist_x;
			player->map_x += player->step_x;
			player->side = 0;
		}
		else
		{
			player->side_dist_y += player->delta_dist_y;
			player->map_y += player->step_y;
			player->side = 1;
		}
		if (player->map_y < 0.2 
			|| player->map_x < 0.2
			|| player->map_y > HEIGHT - 1
			|| player->map_x > WIDTH - 1)
			break;
		else if (map->map[player->map_y][player->map_x] == '1')
			hitwall = 1;

	}
	
};

void	compute_wall_height(t_session *session, t_player *player)
{
	int	wall_height;

	if (player->side == 0)
		player->wall_dist = (player->side_dist_x - player->delta_dist_x);
	else
		player->wall_dist = (player->side_dist_y - player->delta_dist_y);
	
	wall_height = (int)(HEIGHT / player->wall_dist);
	session->matrix->start_draw = HEIGHT / 2  - wall_height / 2;
	session->matrix->end_draw = HEIGHT / 2  + wall_height / 2;
	if (session->matrix->end_draw >= HEIGHT)
		session->matrix->end_draw = HEIGHT - 1;
	if (player->side == 0)
		player->wall_x = player->y_pos + player->wall_dist * player->dir_y;
	else
		player->wall_x = player->x_pos + player->wall_dist * player->dir_x;
	player->wall_x -= floor(player->wall_x);
};


void	draw_stripe(t_session *session)
{
    int x_scr;
    int i;
	int draw_start;
	int draw_end;

	draw_start = session->matrix->start_draw;
	draw_end = session->matrix->end_draw;
	
    x_scr = session->matrix->x_scr;

    //draw sky first
    for (i = 0; i < draw_start; i++)
    {
        session->matrix->matrix[i][x_scr].x = x_scr;
        session->matrix->matrix[i][x_scr].y = i;
        session->matrix->matrix[i][x_scr].color = create_trgb(0, 100, 200, 100);
    }

    //draw wall
    for (i = draw_start; i < draw_end; i++)
    {
        session->matrix->matrix[i][x_scr].x = x_scr;
        session->matrix->matrix[i][x_scr].y = i;
		session->matrix->matrix[i][x_scr].color = create_trgb(100, 255 , 255, 0);
        //session->matrix->matrix[i][x_scr].color = create_trgb(100, 255 , 255, 0);
    }

    //draw ceiling
    for (i = draw_end; i < session->matrix->height; i++)
    {
        session->matrix->matrix[i][x_scr].x = x_scr;
        session->matrix->matrix[i][x_scr].y = i;
        session->matrix->matrix[i][x_scr].color = create_trgb(0, 250, 0, 40);
    }

};


void	raycast(t_session *session)
{
	session->matrix->x_scr = 0;

	while (session->matrix->x_scr < WIDTH)
	{
		init_raycast_data(session->map->player, session->matrix->x_scr);
		determine_dda_dir(session->map->player);
		perform_dda(session->map->player, session->map);

		compute_wall_height(session, session->map->player);
		draw_stripe(session);

		session->matrix->x_scr++;

	}
	

};