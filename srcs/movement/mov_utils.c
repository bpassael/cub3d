/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mov_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez-a <bperez-a@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:30:53 by bperez-a          #+#    #+#             */
/*   Updated: 2024/07/22 13:50:27 by bperez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	is_move_valid(t_map *map, double new_x_pos, double new_y_pos)
{
	if (map->map[(int)floorf(new_y_pos)][(int)floorf(new_x_pos)] == '1')
	{
		ft_error("You hit the wall!");
		return (false);
	}
	return (true);
}
