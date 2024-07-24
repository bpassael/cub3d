/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez-a <bperez-a@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:15:06 by bperez-a          #+#    #+#             */
/*   Updated: 2024/07/24 08:02:53 by bperez-a         ###   ########.fr       */
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
	ft_free_array(map->map);
	free(map->player);
	free(map->no_texture_path);
	free(map->so_texture_path);
	free(map->we_texture_path);
	free(map->ea_texture_path);
	free(map);
}

void free_session(t_session *session)
{
	if (session->map)
	{
		cleanup_textures(session);
		free_map(session->map);
	}
	if (session->mlx_window)
		mlx_delete_image(session->mlx, session->mlx_window);
	if (session->mlx)
		mlx_terminate(session->mlx);
	free(session);
}


void	ft_close_hook(void *param)
{
	t_session	*session;

	session = (t_session *)param;
	free_session(session);
	exit(0);
}