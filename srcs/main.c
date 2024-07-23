/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez-a <bperez-a@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:45:25 by bperez-a          #+#    #+#             */
/*   Updated: 2024/07/23 16:04:48 by bperez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	main(int argc, char **argv)
{
	t_session *session;

	if (argc != 2)
	{
		ft_error("Invalid number of arguments");
		return (1);
	}
	session = malloc(sizeof(t_session));
	
	if (!session)
	{
		ft_error("Malloc failed");
		return (1);
	}
	
	session->map = handle_input(argv[1]);
	if (!session->map)
	{
		free_session(session);
		return (1);
	}
	init_player_in_map(session->map);
	session->mlx = mlx_init(WIDTH, HEIGHT, "WINDOW", true);
	session->mlx_window = mlx_new_image(session->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(session->mlx, session->mlx_window, 0, 0);
	load_textures(session->mlx, session->map);
	raycast(session->map, session);
	mlx_loop_hook(session->mlx, ft_hook, session);
	mlx_loop(session->mlx);
	//free_session(session);
	
	return (0);
};
