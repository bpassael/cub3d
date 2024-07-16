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
void	perform_dda(t_player *player, t_map *map, int side)
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

void	raycast(t_session *session)
{
	session->matrix->x_scr = 0;

	while (session->matrix->x_scr < WIDTH)
	{
		
	}
	

};