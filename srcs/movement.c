#include "../cub3d.h"

bool	is_move_valid()
{

};


void    move_player_forward(t_player *player)
{
	double new_x_pos;
	double new_y_pos;

	new_x_pos = player->x_pos + player->dir_x * MOVE_STEP;
	new_y_pos = player->y_pos + player->dir_y * MOVE_STEP;

	player->x_pos = new_x_pos;
	player->y_pos = new_y_pos;
};

void    move_player_backward(t_player *player)
{
    double new_x_pos;
	double new_y_pos;

	new_x_pos = player->x_pos - player->dir_x * MOVE_STEP;
	new_y_pos = player->y_pos - player->dir_y * MOVE_STEP;

	player->x_pos = new_x_pos;
	player->y_pos = new_y_pos;
    
};

void    move_player_left(t_player *player)
{
    double new_x_pos;
	double new_y_pos;

	new_x_pos = player->x_pos + player->dir_y * MOVE_STEP;
	new_y_pos = player->y_pos - player->dir_x * MOVE_STEP;
    
	player->x_pos = new_x_pos;
	player->y_pos = new_y_pos;
};

void    move_player_right(t_player *player)
{
    double new_x_pos;
	double new_y_pos;

	new_x_pos = player->x_pos - player->dir_y * MOVE_STEP;
	new_y_pos = player->y_pos + player->dir_x * MOVE_STEP;
    
	player->x_pos = new_x_pos;
	player->y_pos = new_y_pos;
    
};

void	rotate_player_right(t_player *player)
{
	double	old_x;
	double	old_y;

	//printf("Updated direction vec before (%f; %f)\n", player->dir_x, player->dir_y);
	old_x = player->dir_x;
	old_y = player->dir_y;

	player->dir_x = old_x * cos(ROTAT_STEP) - old_y * sin(ROTAT_STEP);
	player->dir_y = old_x * sin(ROTAT_STEP) + old_y * cos(ROTAT_STEP);


	//printf("COS = %f; SIN=%f\n", cos(ROTAT_STEP), sin(ROTAT_STEP));

	old_x = player->plane_x;
	old_y = player->plane_y;

	player->plane_x = old_x * cos(ROTAT_STEP) - old_y * sin(ROTAT_STEP);
	player->plane_y = old_x * sin(ROTAT_STEP) + old_y * cos(ROTAT_STEP);

	printf("Updated direction vec  after (%f; %f)\n", player->dir_x, player->dir_y);

};


void	rotate_player_left(t_player *player)
{
	double	old_x;
	double	old_y;

	//printf("Updated direction vec before (%f; %f)\n", player->dir_x, player->dir_y);
	old_x = player->dir_x;
	old_y = player->dir_y;

	player->dir_x = old_x * cos(-ROTAT_STEP) - old_y * sin(-ROTAT_STEP);
	player->dir_y = old_x * sin(-ROTAT_STEP) + old_y * cos(-ROTAT_STEP);


	//printf("COS = %f; SIN=%f\n", cos(-ROTAT_STEP), sin(-ROTAT_STEP));

	old_x = player->plane_x;
	old_y = player->plane_y;

	player->plane_x = old_x * cos(-ROTAT_STEP) - old_y * sin(-ROTAT_STEP);
	player->plane_y = old_x * sin(-ROTAT_STEP) + old_y * cos(-ROTAT_STEP);

	printf("Updated direction vec  after (%f; %f)\n", player->dir_x, player->dir_y);

};