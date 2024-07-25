/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez-a <bperez-a@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:05:58 by bperez-a          #+#    #+#             */
/*   Updated: 2024/07/25 21:33:26 by bperez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 1400
# define HEIGHT 1000
# define MOVE_STEP 0.1
# define ROTAT_STEP 0.04
# define PI 3.14159265

# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64

typedef struct s_tex_info
{
	int				height;
	int				width;
	double			step;
	double			pos;
	mlx_texture_t	*texture;
}					t_tex_info;

typedef struct s_texture
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;
}					t_texture;

typedef struct s_textures
{
	t_texture		north;
	t_texture		south;
	t_texture		west;
	t_texture		east;
}					t_textures;

typedef struct s_ray
{
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	double			wall_x;
	int				tex_x;
	int				tex_num;
}					t_ray;

typedef struct s_player
{
	double			x_pos;
	double			y_pos;

	double			move_step;
	double			rotat_step;
	double			angle_deg;
	double			angle_rad;
	double			plane_x;
	double			plane_y;
	double			dir_x;
	double			dir_y;
	int				map_x;
	int				map_y;
}					t_player;

typedef struct s_map
{
	char			**map;
	char			*no_texture_path;
	char			*so_texture_path;
	char			*we_texture_path;
	char			*ea_texture_path;
	int				floor_color_r;
	int				floor_color_g;
	int				floor_color_b;
	int				ceiling_color_r;
	int				ceiling_color_g;
	int				ceiling_color_b;
	int				player_x;
	int				player_y;
	char			player_dir;
	t_player		*player;
	t_textures		textures;

}					t_map;

typedef struct s_session
{
	t_map			*map;
	mlx_t			*mlx;
	mlx_image_t		*mlx_window;

}					t_session;

// CHECKING

// check.c

bool				check_validity(t_map *map_data);
bool				check_values(t_map *map_data);

// check_map.c

bool				check_map(t_map *map_data);
bool				check_map_content(t_map *map_data, int *player_count);
bool				check_map_line(t_map *map_data, int i, int *player_count);
bool				is_enclosed(char **map, int i, int j);
bool				handle_player_char(t_map *map_data, int i, int j,
						int *player_count);

// check_utils.c

bool				is_enclosed(char **map, int i, int j);
bool				is_valid_map_char(char c);
bool				is_player_char(char c);

// PARSING

// parse_replace_spaces.c

void				replace_spaces(t_map *map_data);
void				pad_lines_to_max_width(char **map, size_t max_width);
void				replace_spaces_with_walls(char **map);
size_t				find_max_width(char **map);

// parse_populate_values.c

void				populate_values(t_map *map_data, char **split_input);
void				init_map_data(t_map *map_data);
void				process_map_elements(t_map *map_data, char ***split_input);
void				process_color(t_map *map_data, char *color_str, char type);
void				extract_map(t_map *map_data, char **split_input);

// parse_utils.c

int					is_map_start(char *line);
int					is_valid_map_line(char *line);

// parse.c

t_map				*handle_input(char *path);
char				*open_file(char *path);
t_map				*parse_map(char *input);

// INIT

// init_player.c

void				init_player_in_map(t_map *map);
void				init_player_plane(t_player *player_data);
void				init_player_direction(t_map *map, t_player *player_data);
void				init_player_position(t_map *map, t_player *player_data);

// init_textures.c

void				load_textures(mlx_t *mlx, t_map *map);

// DRAWING

// draw_line.c

void				draw_ceiling(t_session *session, int x, int draw_start);
void				draw_floor(t_session *session, int x, int draw_end);
void				draw_vertical_line(t_session *session, t_ray *ray, int x);

// draw_wall.c

void				draw_textured_wall(t_session *session, int x, t_ray *ray);
void				draw_wall_slice(t_session *session, int x, t_ray *ray,
						t_tex_info *tex_info);
void				init_tex_info(t_tex_info *tex_info, t_texture *texture,
						t_ray *ray);
t_texture			*select_texture(t_session *session, t_ray *ray);
uint32_t			get_texture_color(mlx_texture_t *texture, int tex_x,
						int tex_y);

// draw_utils.c

uint32_t			create_rgb(uint8_t r, uint8_t g, uint8_t b);

// RAYCASTING

// raycasting1.c

void				raycast(t_map *map, t_session *session);
void				init_ray(t_map *map, t_ray *ray, int x);
void				init_ray_step(t_map *map, t_ray *ray);
void				perform_dda(t_map *map, t_ray *ray);

// raycasting2.c

void				calc_wall_specs(t_ray *ray, int *draw_start, int *draw_end,
						t_player *player);
void				calc_perp_wall_dist(t_map *map, t_ray *ray);
void				calc_wall_x(t_ray *ray, t_player *player);
void				determine_texture(t_ray *ray);

// MOVEMENT

// mov_hook.c

void				handle_lateral_movement(t_session *session);
void				handle_movement(t_session *session);
void				handle_rotation(t_session *session);
void				handle_exit(t_session *session);
void				ft_hook(void *param);

// mov_move.c

void				move_player_forward(t_map *map, t_player *player);
void				move_player_backward(t_map *map, t_player *player);
void				move_player_left(t_map *map, t_player *player);
void				move_player_right(t_map *map, t_player *player);

// mov_rotate.c

void				rotate_player_left(t_player *player);
void				rotate_player_right(t_player *player);

// mov_utils.c

bool				is_move_valid(t_map *map, double x, double y);

// ERROR AND FREE

// error_free.c

void				ft_error(char *message);
void				cleanup_textures(t_session *session);
void				free_map(t_map *map);
void				free_session(t_session *session);
void				ft_close_hook(void *param);

#endif
