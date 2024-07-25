/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez-a <bperez-a@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:24:08 by bperez-a          #+#    #+#             */
/*   Updated: 2024/07/22 13:24:57 by bperez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	load_textures(mlx_t *mlx, t_map *map)
{
	map->textures.north.texture = mlx_load_png(map->no_texture_path);
	map->textures.south.texture = mlx_load_png(map->so_texture_path);
	map->textures.west.texture = mlx_load_png(map->we_texture_path);
	map->textures.east.texture = mlx_load_png(map->ea_texture_path);
	if (!map->textures.north.texture || !map->textures.south.texture
		|| !map->textures.west.texture || !map->textures.east.texture)
	{
		ft_error("Failed to load one or more texture files");
		exit(1);
	}
	map->textures.north.image = mlx_texture_to_image(mlx,
			map->textures.north.texture);
	map->textures.south.image = mlx_texture_to_image(mlx,
			map->textures.south.texture);
	map->textures.west.image = mlx_texture_to_image(mlx,
			map->textures.west.texture);
	map->textures.east.image = mlx_texture_to_image(mlx,
			map->textures.east.texture);
	if (!map->textures.north.image || !map->textures.south.image
		|| !map->textures.west.image || !map->textures.east.image)
	{
		ft_error("Failed to create texture images");
		exit(1);
	}
}
