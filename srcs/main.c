/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez-a <bperez-a@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:45:25 by bperez-a          #+#    #+#             */
/*   Updated: 2024/07/22 10:40:01 by bperez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_hook(void *param)
{
	t_session	*session;

	session = (t_session *)param;

	if (mlx_is_key_down(session->mlx, MLX_KEY_W))
	{
		printf("W is pressed\n");
		move_player_forward(session->map, session->map->player);
		raycast(session->map, session->matrix, session);
		//display_screen(session->matrix, session->mlx_window);

	}
	if (mlx_is_key_down(session->mlx, MLX_KEY_S))
	{
		printf("S is pressed\n");
		move_player_backward(session->map, session->map->player);
		raycast(session->map, session->matrix, session);
		//update_screen(session->matrix, session->map);
		//display_screen(session->matrix, session->mlx_window);
	}
	if (mlx_is_key_down(session->mlx, MLX_KEY_LEFT))
	{
		//printf("LEFT is pressed\n");
		
		// handle overflowing
		// update degrees as well
		rotate_player_left(session->map->player);
		raycast(session->map, session->matrix, session);
		//display_screen(session->matrix, session->mlx_window);
	}
	if (mlx_is_key_down(session->mlx, MLX_KEY_RIGHT))
	{
		//printf("RIGHT is pressed\n");
		session->map->player->angle_rad += session->map->player->rotat_step;
		// handle overflowing
		// update degrees as well
		rotate_player_right(session->map->player);
		raycast(session->map, session->matrix, session);
		//display_screen(session->matrix, session->mlx_window);
	}

	if (mlx_is_key_down(session->mlx, MLX_KEY_A))
	{
		//printf("A is pressed\n");
		move_player_left(session->map, session->map->player);
		raycast(session->map, session->matrix, session);
		//display_screen(session->matrix, session->mlx_window);
	}
	if (mlx_is_key_down(session->mlx, MLX_KEY_D))
	{
		//printf("D is pressed\n");
		move_player_right(session->map, session->map->player);
		raycast(session->map, session->matrix, session);
		//display_screen(session->matrix, session->mlx_window);
	}
}


int main(int argc, char **argv)
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_screen_matrix	*matrix;

	matrix = init_screen_matrix(WIDTH, HEIGHT);
	mlx = mlx_init(WIDTH, HEIGHT,"WINDW", true);
	image = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx, image, 0, 0);

	t_map *map_data = handle_input(argv[1]);
	
	init_player_in_map(map_data);
	t_session *session = malloc(sizeof(t_session));
	session->mlx = mlx;
	session->matrix = matrix;
	session->map = map_data;
	session->mlx_window = image;
	load_textures(mlx, map_data);





	mlx_loop_hook(mlx, ft_hook, session);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	//free_screen_matrix(matrix);
	return (0);
};


