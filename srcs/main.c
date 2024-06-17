/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez-a <bperez-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:45:25 by bperez-a          #+#    #+#             */
/*   Updated: 2024/06/17 13:41:47 by bperez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


int main(int argc, char **argv)
{
	t_map	*map;
	if (argc != 2)
		ft_error("Invalid number of arguments");
	map = handle_input(argv[1]);


	printf("NO: %s\n", map->no_texture_path);
	printf("SO: %s\n", map->so_texture_path);
	printf("WE: %s\n", map->we_texture_path);
	printf("EA: %s\n", map->ea_texture_path);
	printf("F: %d, %d, %d\n", map->floor_color_r, map->floor_color_g, map->floor_color_b);
	printf("C: %d, %d, %d\n", map->ceiling_color_r, map->ceiling_color_g, map->ceiling_color_b);
	printf("Map:\n");
	while (*map->map)
	{
		printf("%s\n", *map->map);
		map->map++;
	}
	return (0);
}