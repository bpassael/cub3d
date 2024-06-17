/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez-a <bperez-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:11:58 by bperez-a          #+#    #+#             */
/*   Updated: 2024/06/17 15:13:26 by bperez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


bool is_enclosed(char **map, int i, int j)
{
	if (i == 0 || j == 0 || map[i + 1] == NULL || map[i][j + 1] == '\0' || map[i][j + 1] == '\n' || map[i][j + 1] == ' ' || map[i + 1][j] == ' ')
		return false;
	return true;
}


bool check_map(char **map)
{
    int i, j;
    int player_count = 0;

    // Iterate through each line of the map
    for (i = 0; map[i] != NULL; i++)
    {
        // Check for an empty line
        if (ft_strlen(map[i]) == 0)
		{
			printf("Empty line\n");
            return false;
		}

        // Check each character in the line
        for (j = 0; map[i][j] != '\0'; j++)
        {
            char c = map[i][j];

            // Check for valid symbols
            if (c != '1' && c != '0' && c != ' ' && c != 'N' && c != 'S' && c != 'E' && c != 'W')
			{
				printf("Invalid symbol\n");
				return false;
			}

            // Count player positions
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
                player_count++;

            // Check surrounded by walls
			if (c == '0' && is_enclosed(map, i, j) == false)
			{
				printf("Not enclosed by walls\n");
				return false;
			}
        }
    }

    // Check for exactly one player position
    if (player_count != 1)
	{
		printf("Invalid number of player positions\n");
		return false;
	}

    return true;
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
	if (check_values(map_data) == false || check_map(map_data->map) == false)
		return (false);
	return (true);
}