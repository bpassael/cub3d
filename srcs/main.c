/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez-a <bperez-a@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:45:25 by bperez-a          #+#    #+#             */
/*   Updated: 2024/07/09 12:08:09 by bperez-a         ###   ########.fr       */
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

	for (int i = 0; i < HEIGHT / 4; i++)
		for (int j = 0; j < WIDTH; j++)
			mlx_put_pixel(image, j, i, create_trgb(0, 0 , 255, 100));

	for (int i = HEIGHT / 4; i <  HEIGHT / 2; i++)
		for (int j = 0; j < WIDTH; j++)
			mlx_put_pixel(image, j, i,create_trgb(0, 100, 100, 100) );

	
	for (int i = HEIGHT / 2; i <  HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
			mlx_put_pixel(image, j, i, create_trgb(0, 250, 0, 40));


	
	t_map *map = handle_input(argv[1]);
	printf("Map:\n");
	for (int i = 0; map->map[i] != NULL; i++)
		printf("%s\n", map->map[i]);



	mlx_loop(mlx);
	mlx_terminate(mlx);
	free_screen_matrix(matrix);
	return (0);
}