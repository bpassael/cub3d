/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez-a <bperez-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:17:24 by bperez-a          #+#    #+#             */
/*   Updated: 2024/07/30 11:54:01 by bperez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_map	*parse_map(char *input)
{
	t_map	*map_data;
	char	**split_input;

	map_data = malloc(sizeof(t_map));
	if (map_data == NULL)
	{
		ft_error("Malloc failed");
		return (NULL);
	}
	split_input = ft_split(input, '\n');
	if (split_input == NULL)
	{
		free(map_data);
		ft_error("Malloc failed");
		return (NULL);
	}
	populate_values(map_data, split_input);
	ft_free_array(split_input);
	return (map_data);
}

char	*open_file(char *path)
{
	char	*buffer;
	int		fd;
	int		read_bytes;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	buffer = malloc(100000);
	if (buffer == NULL)
		return (NULL);
	read_bytes = read(fd, buffer, 100000);
	buffer[read_bytes] = '\0';
	close(fd);
	return (buffer);
}

t_map	*handle_input(char *path)
{
	t_map	*map_data;
	char	*input;

	input = open_file(path);
	if (input == NULL)
	{
		ft_error("Could not open file");
		return (NULL);
	}
	map_data = parse_map(input);
	if (map_data == NULL)
	{
		ft_error("Could not parse map");
		return (NULL);
	}
	free(input);
	if (check_validity(map_data) == false)
	{
		ft_error("Invalid map");
		free_map(map_data);
		return (NULL);
	}
	replace_spaces(map_data);
	return (map_data);
}
