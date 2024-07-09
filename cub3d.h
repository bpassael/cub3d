/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez-a <bperez-a@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:05:58 by bperez-a          #+#    #+#             */
/*   Updated: 2024/07/09 12:42:08 by bperez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>

# define WIDTH 800
# define HEIGHT 600
//represents a single pixel on screen
typedef struct s_pixel
{
	int		x;
	int		y;
	int		color;

}			   t_pixel;


//matrix composed of pixels
//used to draw the field of view of a player
typedef	struct s_screen_matrix
{
	t_pixel	**matrix;
	int		widht;
	int 	height;


}				t_screen_matrix;



typedef struct s_map
{
	char		**map;
	char		*no_texture_path;
	char		*so_texture_path;
	char		*we_texture_path;
	char		*ea_texture_path;
	int			floor_color_r;
	int			floor_color_g;
	int			floor_color_b;
	int			ceiling_color_r;
	int			ceiling_color_g;
	int			ceiling_color_b;
	int			player_x;
	int			player_y;

	
}				t_map;

typedef struct s_session
{
	t_map			*map;
	mlx_t 			*mlx;
	mlx_image_t 	*mlx_window;
	t_screen_matrix	*matrix;

}				t_session;



//Screen matrix
t_pixel     **init_pixel_matrix(int width, int height);
void free_pixel_matrix(t_pixel **matrix, int height);
t_screen_matrix *init_screen_matrix(int widht, int height);

void    free_screen_matrix(t_screen_matrix *matrix);




//Drawing
int	create_trgb(unsigned char t, unsigned char r,
				unsigned char g, unsigned char b);


void	ft_error(char *message);

char	*open_file(char *path);
t_map	*handle_input(char *path);

bool check_validity(t_map *map_data);


#endif
