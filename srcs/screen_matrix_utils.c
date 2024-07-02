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
}