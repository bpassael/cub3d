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