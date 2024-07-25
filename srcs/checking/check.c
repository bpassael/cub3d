/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez-a <bperez-a@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:11:58 by bperez-a          #+#    #+#             */
/*   Updated: 2024/07/25 16:35:21 by bperez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	check_values(t_map *map_data)
{
	if (map_data->no_texture_path == NULL || map_data->so_texture_path == NULL
		|| map_data->we_texture_path == NULL
		|| map_data->ea_texture_path == NULL)
		return (false);
	if (map_data->floor_color_r == -1 || map_data->floor_color_g == -1
		|| map_data->floor_color_b == -1)
		return (false);
	if (map_data->ceiling_color_r == -1 || map_data->ceiling_color_g == -1
		|| map_data->ceiling_color_b == -1)
		return (false);
	return (true);
}

bool	check_validity(t_map *map_data)
{
	if (check_values(map_data) == false || check_map(map_data) == false)
		return (false);
	return (true);
}
