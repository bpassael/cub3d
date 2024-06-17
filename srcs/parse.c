/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez-a <bperez-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:17:24 by bperez-a          #+#    #+#             */
/*   Updated: 2024/06/17 13:49:20 by bperez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


void populate_values(t_map *map_data, char **split_input)
{
	char **beg_map;
	char **split_color;
	
	while (*split_input)
	{
		if (ft_strncmp(*split_input, "NO ", 3) == 0)
			map_data->no_texture_path = ft_strdup(*split_input + 3);
		else if (ft_strncmp(*split_input, "SO ", 3) == 0)
			map_data->so_texture_path = ft_strdup(*split_input + 3);
		else if (ft_strncmp(*split_input, "WE ", 3) == 0)
			map_data->we_texture_path = ft_strdup(*split_input + 3);
		else if (ft_strncmp(*split_input, "EA ", 3) == 0)
			map_data->ea_texture_path = ft_strdup(*split_input + 3);
		else if (ft_strncmp(*split_input, "F ", 2) == 0)
		{
			split_color = ft_split(*split_input + 2, ',');
			map_data->floor_color_r = ft_atoi(split_color[0]);
			map_data->floor_color_g = ft_atoi(split_color[1]);
			map_data->floor_color_b = ft_atoi(split_color[2]);
		}
		else if (ft_strncmp(*split_input, "C ", 2) == 0)
		{
			split_color = ft_split(*split_input + 2, ',');
			map_data->ceiling_color_r = ft_atoi(split_color[0]);
			map_data->ceiling_color_g = ft_atoi(split_color[1]);
			map_data->ceiling_color_b = ft_atoi(split_color[2]);
		}
		else if (ft_strlen(*split_input) == 0)
		{
			split_input++;
			continue;
		}
		else
			break;
		split_input++;
	}
	beg_map = split_input;
	
    char **temp = beg_map;
	
    while (*temp && ft_strlen(*temp) > 0)
    {
        map_lines_count++;
        temp++;
    }

    map_data->map = (char **)malloc(sizeof(char *) * (map_lines_count + 1));
    if (!map_data->map)
        return; 

    for (size_t i = 0; i < map_lines_count; i++)
    {
        map_data->map[i] = ft_strdup(beg_map[i]);
    }
    map_data->map[map_lines_count] = NULL;
}

	

t_map *parse_map(char *input)
{
	t_map *map_data;
	char **split_input;
	
	map_data = malloc(sizeof(t_map));
	if (map_data == NULL)
		ft_error("Malloc failed");
	
	split_input = ft_split(input, '\n');
	if (split_input == NULL)
		ft_error("Malloc failed");

	populate_values(map_data, split_input);

	
	
}

char *open_file(char *path)
{
	char	*buffer;
	int		fd;
	int		read_bytes;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_error("Failed to open file");
	buffer = malloc(100000);
	if (buffer == NULL)
		ft_error("Malloc failed");
	read_bytes = read(fd, buffer, 100000);
	buffer[read_bytes] = '\0';
	close(fd);
	return (buffer);
}


t_map	*handle_input(char *path)
{
	t_map	*map_data;
	char *input;

	input = open_file(path);
	map_data = parse_map(input);
		
	return (map);
}