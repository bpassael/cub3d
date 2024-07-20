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

# define WIDTH 800
# define HEIGHT 600
# define MOVE_STEP 0.1
# define ROTAT_STEP 0.04
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
	//raydir that we changer during raycast
	double	ray_dir_x;
	double	ray_dir_y;

	//initial ray/player direction
	double	dir_x;
	double	dir_y;

	
	
	//DDA stuff
	int		step_x;
	int		step_y;
	int		side;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	
	int	map_x; //which square  ray is in
	int	map_y; // for now

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
void    init_player_in_map(t_map *map);
void	rotate_player_left(t_player *player);
void	rotate_player_right(t_player *player);


//Movement
void    move_player_forward(t_map *map, t_player *player);
void    move_player_backward(t_map *map,t_player *player);
void    move_player_left(t_map *map, t_player *player);
void    move_player_right(t_map *map, t_player *player);


void    free_screen_matrix(t_screen_matrix *matrix);

void    raycast(t_map *map, t_screen_matrix *matrix, t_session *session);




//Drawing
int	create_trgb(unsigned char t, unsigned char r,
				unsigned char g, unsigned char b);


void	ft_error(char *message);

char	*open_file(char *path);
t_map	*handle_input(char *path);

bool check_validity(t_map *map_data);


#endif
