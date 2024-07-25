/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez-a <bperez-a@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:06:38 by bperez-a          #+#    #+#             */
/*   Updated: 2024/07/25 18:06:58 by bperez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_valid_map_line(char *line)
{
	while (*line)
	{
		if (*line != '0' && *line != '1' && *line != ' ' && *line != 'N'
			&& *line != 'S' && *line != 'E' && *line != 'W')
			return (0);
		line++;
	}
	return (1);
}

int	is_map_start(char *line)
{
	while (*line)
	{
		if (*line != '1' && *line != '0' && *line != ' ')
			return (0);
		line++;
	}
	return (1);
}
