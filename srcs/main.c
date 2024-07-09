/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez-a <bperez-a@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:45:25 by bperez-a          #+#    #+#             */
/*   Updated: 2024/07/09 12:50:09 by bperez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


int main(int argc, char **argv)
{
	mlx_t *mlx;
	mlx_image_t *image;

	t_screen_matrix	*matrix;

	matrix = init_screen_matrix(WIDTH, HEIGHT);
	mlx = mlx_init(WIDTH, HEIGHT,"WINDW", true);
	image = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx, image, 0, 0);


	fill_screen_with_initial_view(matrix);
	display_screen(matrix, image);

	t_map *map_data = handle_input(argv[1]);

	printf("%f distance to wall\n", compute_distance_to_wall(map_data));
	printf("Map:\n");
	for (int i = 0; map_data->map[i] != NULL; i++)
		printf("%s\n", map_data->map[i]);
	printf("Player position: %d, %d\n", map_data->player_x, map_data->player_y);
	
	mlx_loop(mlx);
	mlx_terminate(mlx);
	free_screen_matrix(matrix);
	return (0);
}