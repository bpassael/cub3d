/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez-a <bperez-a@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:11:58 by bperez-a          #+#    #+#             */
/*   Updated: 2024/07/22 13:08:11 by bperez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	is_enclosed(char **map, int i, int j)
{
	if (i == 0 || j == 0 || map[i + 1] == NULL || map[i][j + 1] == '\0'
		|| map[i][j + 1] == '\n' || map[i][j + 1] == ' ' || map[i
		+ 1][j] == ' ')
		return (false);
	return (true);
}

bool	check_map(t_map *map_data)
{
	int		player_count;
	char	c;
	int		i;
	int		j;

	player_count = 0;
	for (i = 0; map_data->map[i] != NULL; i++)
	{
		if (ft_strlen(map_data->map[i]) == 0)
		{
			printf("Empty line\n");
			return (false);
		}
		for (j = 0; map_data->map[i][j] != '\0'; j++)
		{
			c = map_data->map[i][j];
			if (c != '1' && c != '0' && c != ' ' && c != 'N' && c != 'S'
				&& c != 'E' && c != 'W')
			{
				printf("Invalid symbol\n");
				return (false);
			}
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				map_data->player_x = j;
				map_data->player_y = i;
				map_data->player_dir = c;
				player_count++;
			}
			if (c == '0' && is_enclosed(map_data->map, i, j) == false)
			{
				printf("Not enclosed by walls\n");
				return (false);
			}
		}
	}
	if (player_count != 1)
	{
		printf("Invalid number of player positions\n");
		return (false);
	}
	return (true);
}

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
