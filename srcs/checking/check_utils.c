/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez-a <bperez-a@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:33:03 by bperez-a          #+#    #+#             */
/*   Updated: 2024/07/25 16:33:48 by bperez-a         ###   ########.fr       */
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

bool	is_valid_map_char(char c)
{
	return (c == '1' || c == '0' || c == ' ' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W');
}

bool	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}
