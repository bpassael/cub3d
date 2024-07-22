/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez-a <bperez-a@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:05:58 by bperez-a          #+#    #+#             */
/*   Updated: 2024/07/22 13:46:59 by bperez-a         ###   ########.fr       */
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

# define WIDTH 1400
# define HEIGHT 1000
# define MOVE_STEP 0.1
# define ROTAT_STEP 0.04
# define PI 3.14159265

#define TEXTURE_WIDTH 64
#define TEXTURE_HEIGHT 64

typedef struct s_texture {
    mlx_texture_t *texture;
    mlx_image_t   *image;
} t_texture;

typedef struct s_textures {
    t_texture   north;
    t_texture   south;
    t_texture   west;
    t_texture   east;
} t_textures;






//represents a single pixel on screen
typedef struct s_pixel
{
	int		x;
	int		y;
	int		color;

}			   t_pixel;




typedef struct s_ray
{
    double cameraX;
    double rayDirX;
    double rayDirY;
    int mapX;
    int mapY;
    double sideDistX;
    double sideDistY;
    double deltaDistX;
    double deltaDistY;
    double perpWallDist;
    int stepX;
    int stepY;
    int hit;
    int side;
    int lineHeight;
    int drawStart;
    int drawEnd;
    double wallX;
    int texX;
    int texNum;
} t_ray;





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
	t_textures  textures;



}				t_map;



typedef struct s_session
{
	t_map			*map;
	mlx_t 			*mlx;
	mlx_image_t 	*mlx_window;

}				t_session;




void	ft_hook(void *param);


void    init_player_in_map(t_map *map);


void	rotate_player_left(t_player *player);
void	rotate_player_right(t_player *player);
void    move_player_forward(t_map *map, t_player *player);
void    move_player_backward(t_map *map,t_player *player);
void    move_player_left(t_map *map, t_player *player);
void    move_player_right(t_map *map, t_player *player);
bool	is_move_valid(t_map *map, double new_x_pos, double new_y_pos);




void    raycast(t_map *map, t_session *session);
void    init_ray(t_map *map, t_ray *ray, int x);
void    init_ray_step(t_map *map, t_ray *ray);
void    perform_dda(t_map *map, t_ray *ray);
void    calc_perp_wall_dist(t_map *map, t_ray *ray);
void calc_wall_specs(t_ray *ray, int *drawStart, int *drawEnd, t_player *player);
void    calc_wall_x(t_ray *ray, t_player *player);
void    determine_texture(t_ray *ray);


void    draw_vertical_line(t_session *session, t_ray *ray, int x);
void    draw_ceiling(t_session *session, int x, int drawStart);
void    draw_floor(t_session *session, int x, int drawEnd);
void    draw_textured_wall(t_session *session, int x, int drawStart, int drawEnd, t_ray *ray);




//Textures
void    load_textures(mlx_t *mlx, t_map *map);



//Drawing
int	create_trgb(unsigned char t, unsigned char r,
				unsigned char g, unsigned char b);

uint32_t create_rgb(uint8_t r, uint8_t g, uint8_t b);

void	ft_error(char *message);

char	*open_file(char *path);
t_map	*handle_input(char *path);

bool check_validity(t_map *map_data);


#endif
