/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez-a <bperez-a@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:45:25 by bperez-a          #+#    #+#             */
/*   Updated: 2024/07/22 13:50:09 by bperez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	main(int argc, char **argv)
{
	mlx_t *mlx;
	mlx_image_t *image;
	t_map *map_data;
	t_session *session;

	mlx = mlx_init(WIDTH, HEIGHT, "WINDOW", true);
	image = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx, image, 0, 0);
	map_data = handle_input(argv[1]);
	init_player_in_map(map_data);
	session = malloc(sizeof(t_session));
	session->mlx = mlx;
	session->map = map_data;
	session->mlx_window = image;
	load_textures(mlx, map_data);
	raycast(session->map, session);
	mlx_loop_hook(mlx, ft_hook, session);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
};
