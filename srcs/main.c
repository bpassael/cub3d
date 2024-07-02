/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez-a <bperez-a@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:45:25 by bperez-a          #+#    #+#             */
/*   Updated: 2024/06/17 17:05:03 by bperez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int main()
{
	mlx_t	*mlx;
	mlx_image_t *mlx_image;

	mlx = mlx_init(500, 500, "MLX42", true);
	mlx_image = mlx_new_image(mlx, 300, 300);
	mlx_image_to_window(mlx, mlx_image, 0, 0);

	mlx_terminate(mlx);

	return 0;
};


// int main(int argc, char **argv)
// {
// 	t_map	*map_data;
// 	if (argc != 2)
// 		ft_error("Invalid number of arguments");
// 	map_data = handle_input(argv[1]);
	


// 	printf("NO: %s\n", map_data->no_texture_path);
// 	printf("SO: %s\n", map_data->so_texture_path);
// 	printf("WE: %s\n", map_data->we_texture_path);
// 	printf("EA: %s\n", map_data->ea_texture_path);
// 	printf("F: %d, %d, %d\n", map_data->floor_color_r, map_data->floor_color_g, map_data->floor_color_b);
// 	printf("C: %d, %d, %d\n", map_data->ceiling_color_r, map_data->ceiling_color_g, map_data->ceiling_color_b);
// 	printf("Map:\n");
// 	while (*map_data->map)
// 	{
// 		printf("%s\n", *map_data->map);
// 		map_data->map++;
// 	}
// 	return (0);
// }