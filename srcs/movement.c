#include "../cub3d.h"


void    move_player_x_pos(t_player *player)
{
    if ((player->x_pos + player->move_step) >= WIDTH || (player->x_pos + player->move_step) <= 0)
    {
        ft_error("Can't move anymore; You hit the wall!");
        return ;
    }

    player->x_pos += player->move_step;
    
};

void    move_player_x_neg(t_player *player)
{
    if ((player->x_pos - player->move_step) >= WIDTH || (player->x_pos - player->move_step) <= 0)
    {
        ft_error("Can't move anymore; You hit the wall!");
        return ;
    }

    player->x_pos -= player->move_step;
    
};


void    move_player_y_pos(t_player *player)
{
    if ((player->y_pos + player->move_step) >= HEIGHT)
    {
        ft_error("Can't move anymore; You hit the wall!");
        return ;
    }
    player->y_pos += player->move_step;
}

void    move_player_y_neg(t_player *player)
{
    if ((player->y_pos - player->move_step) <= 0)
    {
        ft_error("Can't move anymore; You hit the wall!");
        return ;
    }
    player->y_pos -= player->move_step;
}

void	rotate_player_left(t_player *player)
{
	double	old_x;
	double	old_y;

	printf("Updated direction vec before (%f; %f)\n", player->dir_x, player->dir_y);
	old_x = player->dir_x;
	old_y = player->dir_y;

	player->dir_x = old_x * cos(ROTAT_STEP) - old_y * sin(ROTAT_STEP);
	player->dir_y = old_x * sin(ROTAT_STEP) + old_y * cos(ROTAT_STEP);


	printf("COS = %f; SIN=%f\n", cos(ROTAT_STEP), sin(ROTAT_STEP));

	old_x = player->plane_x;
	old_y = player->plane_y;

	player->plane_x = old_x * cos(ROTAT_STEP) - old_y * sin(ROTAT_STEP);
	player->plane_y = old_x * sin(ROTAT_STEP) + old_y * cos(ROTAT_STEP);

	printf("Updated direction vec  after (%f; %f)\n", player->dir_x, player->dir_y);

};