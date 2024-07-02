#include "cub3d.h"

// Function to draw a vertical line with texture on the screen
static void	put_texture_line(t_game *game, int wall_top, int wall_bottom)
{
	int color;
	int	side;
	int temp_y;
	int wall_size;
	double y_pos_fixed;

	temp_y = 0;
	wall_size = 0;
	
	// Calculate the size of the wall to be drawn
	if (wall_top < 0)
		wall_size = wall_bottom + abs(wall_top);
	else
		wall_size = wall_bottom - wall_top;

	// Draw the wall line by line from top to bottom
	while (wall_top++ < wall_bottom)
	{
		temp_y++;
		y_pos_fixed = (double)temp_y / (double)wall_size; // Calculate the y position in the texture
		side = define_texture_side(game); // Determine which texture to use based on the wall side
		color = extract_texture_color(game, y_pos_fixed, side); // Get the color from the texture

		// If a valid color is retrieved, draw the pixel on the screen
		if (color != -1)
			pixel_put(game->mlx_data, game->line_num, wall_top, color);
	}
}

// Function to draw a solid color line on the screen
static void	put_line(t_game *game, int wall_top, int wall_bottom, int color)
{
	// Draw the line from top to bottom
	while (wall_top < wall_bottom)
	{
		pixel_put(game->mlx_data, game->line_num, wall_top, color);
		wall_top++;
	}
}

// Function to draw the ceiling, wall, and floor for the current column
static void	draw_line(t_game *game)
{
	int	wall_top;
	int	wall_bottom;

	// Calculate the top and bottom positions of the wall
	wall_top = game->values->half_src_height - game->wall_height;
	wall_bottom = game->values->half_src_height + game->wall_height;

	// Draw the ceiling from the top of the screen to the top of the wall
	put_line(game, 0, wall_top, game->map->hex_ceilling);
	
	// Draw the wall with texture from top to bottom
	put_texture_line(game, wall_top, wall_bottom);

	// Draw the floor from the bottom of the wall to the bottom of the screen
	put_line(game, wall_bottom, HEIGHT, game->map->hex_floor);
}

// Function to find the position where the ray intersects a wall
static void	define_wall_position(t_game *game)
{
	// Move the ray step by step until it hits a wall
	while (true)
	{
		game->ray_x += game->ray_cos; // Update the ray's x position
		game->ray_y += game->ray_sin; // Update the ray's y position
		game->x = round(game->ray_x); // Round to the nearest grid cell
		game->y = round(game->ray_y);

		// Ensure the position is within the map boundaries
		if (game->x < 0)
			game->x = 0;
		else if (game->x >= game->map->width)
			game->x = game->map->width - 1;
		if (game->y < 0)
			game->y = 0;
		else if (game->y >= game->map->height)
			game->y = game->map->height - 1;

		// Check if the current position is a wall
		if (is_wall(game, game->x, game->y))
			break;

		// Save the previous position of the ray
		game->prev_x = game->x;
		game->prev_y = game->y;
	}
}

// Main raycasting function
int	raycast(t_game *game)
{
	// Initialize the ray angle to the leftmost side of the player's FOV
	game->ray_angle = game->map->player_orient - game->values->half_fov;
	game->line_num = 0;

	// Loop through each column of the screen
	while (game->line_num < WIDTH)
	{
		// Initialize the ray position to the player's position
		game->ray_x = game->map->player_x;
		game->ray_y = game->map->player_y;

		// Calculate the ray direction (cosine and sine of the angle) with precision adjustment
		game->ray_cos = cos(degree_to_radians(game->ray_angle)) / game->values->precision;
		game->ray_sin = sin(degree_to_radians(game->ray_angle)) / game->values->precision;

		// Find the wall position where the ray intersects
		define_wall_position(game);

		// Calculate the distance from the player to the wall using the Pythagorean theorem
		game->distance = sqrt(pow(game->map->player_x - game->ray_x, 2)
				+ pow(game->map->player_y - game->ray_y, 2));

		// Correct the distance for the fisheye effect
		game->distance = game->distance * cos(degree_to_radians(game->ray_angle - game->map->player_orient));

		// Calculate the wall height to be drawn based on the distance
		game->wall_height = floor(game->values->half_src_height / game->distance);

		// Draw the line (ceiling, wall with texture, and floor) for the current column
		draw_line(game);

		// Increment the ray angle for the next column
		game->ray_angle += game->values->inc_angle;
		game->line_num++;
	}

	// Clear the previous image from the window
	mlx_clear_window(game->mlx_data->mlx_ptr, game->mlx_data->win_ptr);

	// Put the newly rendered image to the window
	mlx_put_image_to_window(game->mlx_data->mlx_ptr, game->mlx_data->win_ptr,
		game->mlx_data->img, 0, 0);

	return (0);
}
