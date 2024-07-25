/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_populate_values.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez-a <bperez-a@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:01:42 by bperez-a          #+#    #+#             */
/*   Updated: 2024/07/25 21:14:23 by bperez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_map_data(t_map *map_data)
{
	map_data->floor_color_r = -1;
	map_data->floor_color_g = -1;
	map_data->floor_color_b = -1;
	map_data->ceiling_color_r = -1;
	map_data->ceiling_color_g = -1;
	map_data->ceiling_color_b = -1;
	map_data->no_texture_path = NULL;
	map_data->so_texture_path = NULL;
	map_data->we_texture_path = NULL;
	map_data->ea_texture_path = NULL;
}

void	process_map_elements(t_map *map_data, char ***split_input)
{
	while (**split_input && !is_map_start(**split_input))
	{
		if (ft_strncmp(**split_input, "NO ", 3) == 0)
			map_data->no_texture_path = ft_strdup(**split_input + 3);
		else if (ft_strncmp(**split_input, "SO ", 3) == 0)
			map_data->so_texture_path = ft_strdup(**split_input + 3);
		else if (ft_strncmp(**split_input, "WE ", 3) == 0)
			map_data->we_texture_path = ft_strdup(**split_input + 3);
		else if (ft_strncmp(**split_input, "EA ", 3) == 0)
			map_data->ea_texture_path = ft_strdup(**split_input + 3);
		else if (ft_strncmp(**split_input, "F ", 2) == 0)
			process_color(map_data, **split_input + 2, 'F');
		else if (ft_strncmp(**split_input, "C ", 2) == 0)
			process_color(map_data, **split_input + 2, 'C');
		else if (**split_input[0] != '\0')
			ft_error("Invalid map element");
		(*split_input)++;
	}
}

void	process_color(t_map *map_data, char *color_str, char type)
{
	char	**split_color;

	split_color = ft_split(color_str, ',');
	if (ft_array_len(split_color) != 3)
		ft_error("Invalid color format");
	else if (type == 'F')
	{
		map_data->floor_color_r = ft_atoi(split_color[0]);
		map_data->floor_color_g = ft_atoi(split_color[1]);
		map_data->floor_color_b = ft_atoi(split_color[2]);
	}
	else if (type == 'C')
	{
		map_data->ceiling_color_r = ft_atoi(split_color[0]);
		map_data->ceiling_color_g = ft_atoi(split_color[1]);
		map_data->ceiling_color_b = ft_atoi(split_color[2]);
	}
	ft_free_array(split_color);
}

void	extract_map(t_map *map_data, char **split_input)
{
	size_t	map_lines_count;
	size_t	i;

	map_lines_count = 0;
	while (split_input[map_lines_count]
		&& ft_strlen(split_input[map_lines_count]) > 0)
	{
		if (!is_valid_map_line(split_input[map_lines_count]))
			ft_error("Invalid map line");
		map_lines_count++;
	}
	map_data->map = (char **)malloc(sizeof(char *) * (map_lines_count + 1));
	if (!map_data->map)
		ft_error("Malloc failed");
	i = 0;
	while (i < map_lines_count)
	{
		map_data->map[i] = ft_strdup(split_input[i]);
		i++;
	}
	map_data->map[map_lines_count] = NULL;
}

void	populate_values(t_map *map_data, char **split_input)
{
	init_map_data(map_data);
	process_map_elements(map_data, &split_input);
	if (*split_input)
		extract_map(map_data, split_input);
	else
		ft_error("No map data found after elements");
}
