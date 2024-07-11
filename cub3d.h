/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez-a <bperez-a@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:05:58 by bperez-a          #+#    #+#             */
/*   Updated: 2024/07/11 13:40:18 by bperez-a         ###   ########.fr       */
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
# include <math.h>

# define WIDTH 1200
# define HEIGHT 800
# define MOVE_STEP 0.2
# define ROTAT_STEP 0.02
# define PI 3.14159265



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
	int		width;
	int 	height;

	//need for raycast loop
	int		x_scr;
	int		y_scr;


}				t_screen_matrix;



typedef struct s_player
{
	double	x_pos;
	double	y_pos;

	double	move_step;
	double	rotat_step;
	double	angle_deg;
	double	angle_rad;


	/*RAYCASTING STUFF*/
	double	fow;
	double	camera_x; //camera X is single x coordinate along plane line
	double	plane_x; //2D version of of camera plane. (plane vector)
	double	plane_y; //plane vector is always orthogonal to dir vector

	//initial ray/player direction
	double	dir_x;
	double	dir_y;

	//raydir that we changer during raycast
	double	ray_dir_x;
	double	ray_dir_y;
	
	
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;

}			t_player;



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
	char		player_dir;
	t_player	*player;


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
t_screen_matrix *init_screen_matrix(int width, int height);
void    display_screen(t_screen_matrix *matrix, mlx_image_t *image);
void    update_screen(t_screen_matrix *matrix, t_map *map);
void    init_player_in_map(t_map *map);

//Movement
void    move_player_y_pos(t_player *player);
void    move_player_y_neg(t_player *player);



void    free_screen_matrix(t_screen_matrix *matrix);

//basic raycasting utils
double compute_distance_to_wall(t_map *map);




//Drawing
int	create_trgb(unsigned char t, unsigned char r,
				unsigned char g, unsigned char b);


void	ft_error(char *message);

char	*open_file(char *path);
t_map	*handle_input(char *path);

bool check_validity(t_map *map_data);


#endif
