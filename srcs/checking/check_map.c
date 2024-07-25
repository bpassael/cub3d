/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez-a <bperez-a@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:35:32 by bperez-a          #+#    #+#             */
/*   Updated: 2024/07/25 16:40:40 by bperez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	check_map(t_map *map_data)
{
	int	player_count;

	player_count = 0;
	if (!check_map_content(map_data, &player_count))
		return (false);
	if (player_count != 1)
	{
		printf("Invalid number of player positions\n");
		return (false);
	}
	return (true);
}

bool	check_map_content(t_map *map_data, int *player_count)
{
	int	i;
	int	j;

	i = 0;
	while (map_data->map[i] != NULL)
	{
		if (ft_strlen(map_data->map[i]) == 0)
		{
			printf("Empty line\n");
			return (false);
		}
		if (!check_map_line(map_data, i, player_count))
			return (false);
		i++;
	}
	return (true);
}

bool	check_map_line(t_map *map_data, int i, int *player_count)
{
	int		j;
	char	c;

	j = 0;
	while (map_data->map[i][j] != '\0')
	{
		c = map_data->map[i][j];
		if (!is_valid_map_char(c))
		{
			printf("Invalid symbol\n");
			return (false);
		}
		if (is_player_char(c))
		{
			if (!handle_player_char(map_data, i, j, player_count))
				return (false);
		}
		if (c == '0' && !is_enclosed(map_data->map, i, j))
		{
			printf("Not enclosed by walls\n");
			return (false);
		}
		j++;
	}
	return (true);
}

bool	handle_player_char(t_map *map_data, int i, int j, int *player_count)
{
	map_data->player_x = j;
	map_data->player_y = i;
	map_data->player_dir = map_data->map[i][j];
	(*player_count)++;
	return (true);
}
