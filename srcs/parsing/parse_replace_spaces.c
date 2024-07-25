/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_replace_spaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez-a <bperez-a@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:54:55 by bperez-a          #+#    #+#             */
/*   Updated: 2024/07/25 17:55:46 by bperez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

size_t	find_max_width(char **map)
{
	size_t	max_width;
	size_t	current_width;

	max_width = 0;
	while (*map)
	{
		current_width = ft_strlen(*map);
		if (current_width > max_width)
			max_width = current_width;
		map++;
	}
	return (max_width);
}

void	replace_spaces_with_walls(char **map)
{
	char	*line;

	while (*map)
	{
		line = *map;
		while (*line)
		{
			if (*line == ' ')
				*line = '1';
			line++;
		}
		map++;
	}
}

void	pad_lines_to_max_width(char **map, size_t max_width)
{
	char	*line;
	size_t	line_len;

	while (*map)
	{
		line = *map;
		line_len = ft_strlen(line);
		while (line_len < max_width)
		{
			*map = ft_strjoin(*map, "1");
			line_len++;
		}
		map++;
	}
}

void	replace_spaces(t_map *map_data)
{
	size_t	max_width;

	max_width = find_max_width(map_data->map);
	replace_spaces_with_walls(map_data->map);
	pad_lines_to_max_width(map_data->map, max_width);
}
