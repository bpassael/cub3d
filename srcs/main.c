/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez-a <bperez-a@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:45:25 by bperez-a          #+#    #+#             */
/*   Updated: 2024/07/02 18:28:28 by bperez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


int main()
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
	
	mlx_loop(mlx);
	mlx_terminate(mlx);
	free_screen_matrix(matrix);
	return (0);
}