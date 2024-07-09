#include "../cub3d.h"

t_pixel     **init_pixel_matrix(int width, int height)
{
    t_pixel **matrix;
    int     i;

    matrix = (t_pixel **) malloc(sizeof(t_pixel *) * height);
    if (matrix == NULL)
    {
        ft_error("Malloc failed when allocating matrix\n");
        return NULL;
    }

    i = 0;
    while (i < height)
    {
        matrix[i] = (t_pixel *) malloc(sizeof(t_pixel) * width);
        if (matrix[i] == NULL)
        {
            ft_error("Malloc failed when allocating matrix\n");
            return NULL;
        }
        i++;
    }
    return (matrix);
};

t_screen_matrix *init_screen_matrix(int width, int height)
{
    t_screen_matrix *screen_matrix;

    screen_matrix = (t_screen_matrix *) malloc(sizeof(t_screen_matrix));
    
    screen_matrix->matrix = init_pixel_matrix(width, height);
    screen_matrix->width = width;
    screen_matrix->height = height;

    return (screen_matrix);
};

void free_pixel_matrix(t_pixel **matrix, int height)
{
    int i = 0;

    if (matrix == NULL)
        return;

    while (i < height)
    {
        if (matrix[i] != NULL)
        {
            free(matrix[i]);
        }
        i++;
    }
    free(matrix);
};

void    free_screen_matrix(t_screen_matrix *matrix)
{
    free_pixel_matrix(matrix->matrix, matrix->height);
    free(matrix);
};


void    display_screen(t_screen_matrix *matrix, mlx_image_t *image)
{
    for (int i = 0; i < matrix->height; i++)
		for (int j = 0; j < matrix->width; j++)
			mlx_put_pixel(image, matrix->matrix[i][j].x,
								matrix->matrix[i][j].y,
								matrix->matrix[i][j].color);
};

void    update_screen(t_screen_matrix *matrix, t_map *map)
{
    int line_height;
    double wall_distance;

    int wall_start;
    int wall_end;

    int i;
    int j;

    wall_distance = compute_distance_to_wall(map);

    printf("Distance to wall: %f\n", wall_distance);


    line_height = matrix->height / wall_distance;

    printf("Line height: %d\n", line_height);
    wall_start = matrix->height / 2  - line_height / 2;
    wall_end = matrix->height / 2 + line_height / 2;

    printf("Wall start: %d\n", wall_start);
    printf("Wall end: %d\n", wall_end);

    //draw sky first
    for ( i = 0; i < wall_start; i++)
        for (j = 0; j < matrix->width; j++)
        {
            matrix->matrix[i][j].x = j;
            matrix->matrix[i][j].y = i;
            matrix->matrix[i][j].color = create_trgb(0, 100, 200, 100);
        }
    
    //draw wall
    for ( i = wall_start; i < wall_end; i++)
        for (j = 0; j < matrix->width; j++)
        {
            matrix->matrix[i][j].x = j;
            matrix->matrix[i][j].y = i;
            matrix->matrix[i][j].color = create_trgb(100, 255 , 255, 0);
        };

    //draw floor
    for ( i = wall_end; i < matrix->height; i++)
        for (j = 0; j < matrix->width; j++)
        {
            matrix->matrix[i][j].x = j;
            matrix->matrix[i][j].y = i;
            matrix->matrix[i][j].color = create_trgb(0, 250, 0, 40);
        };
    printf("DONE update\n");

}
