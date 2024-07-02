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


	mlx = mlx_init(400, 400,"WINDW", true);
	image = mlx_new_image(mlx, 400, 400);
	mlx_image_to_window(mlx, image, 0, 0);

	for (int i = 0; i < 200; i++)
		for (int j = 0; j < 200; j++)
			mlx_put_pixel(image, i, j, create_trgb(0, 100, 100, 100));

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}