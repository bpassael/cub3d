/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez-a <bperez-a@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:15:06 by bperez-a          #+#    #+#             */
/*   Updated: 2024/07/23 15:11:56 by bperez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_error(char *message)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	ft_putchar_fd('\n', 2);
}


void cleanup_textures(t_session *session)
{
    if (session->map->textures.north.texture) mlx_delete_texture(session->map->textures.north.texture);
    if (session->map->textures.south.texture) mlx_delete_texture(session->map->textures.south.texture);
    if (session->map->textures.west.texture) mlx_delete_texture(session->map->textures.west.texture);
    if (session->map->textures.east.texture) mlx_delete_texture(session->map->textures.east.texture);

    if (session->map->textures.north.image) mlx_delete_image(session->mlx, session->map->textures.north.image);
    if (session->map->textures.south.image) mlx_delete_image(session->mlx, session->map->textures.south.image);
    if (session->map->textures.west.image) mlx_delete_image(session->mlx, session->map->textures.west.image);
    if (session->map->textures.east.image) mlx_delete_image(session->mlx, session->map->textures.east.image);
}



void free_map(t_map *map)
{
	char **map_ptr;

	map_ptr = map->map;
	while (*map_ptr)
	{
		free(*map_ptr);
		map_ptr++;
	}
	free(map->map);
	free(map->player);
	free(map);
}

void free_session(t_session *session)
{
	if (session->map)
	{
		cleanup_textures(session);
		free_map(session->map);
	}
	if (session->mlx)
		mlx_terminate(session->mlx);
	free(session);
}