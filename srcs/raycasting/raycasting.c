#include "../cub3d.h"

void raycast(t_map *map, t_session *session)
{
    t_ray ray;
    int x;

    x = 0;
    while (x < WIDTH)
    {
        init_ray(map, &ray, x);
        perform_dda(map, &ray);
        calc_perp_wall_dist(map, &ray);
        calc_wall_specs(&ray, &ray.drawStart, &ray.drawEnd, map->player);
        draw_vertical_line(session, &ray, x);
        x++;
    }
}


void init_ray(t_map *map, t_ray *ray, int x)
{
    ray->cameraX = 2 * x / (double)WIDTH - 1;
    ray->rayDirX = map->player->dir_x + map->player->plane_x * ray->cameraX;
    ray->rayDirY = map->player->dir_y + map->player->plane_y * ray->cameraX;
    ray->mapX = (int)map->player->x_pos;
    ray->mapY = (int)map->player->y_pos;
    ray->deltaDistX = fabs(1 / ray->rayDirX);
    ray->deltaDistY = fabs(1 / ray->rayDirY);
    ray->hit = 0;
    init_ray_step(map, ray);
}

void init_ray_step(t_map *map, t_ray *ray)
{
    if (ray->rayDirX < 0)
    {
        ray->stepX = -1;
        ray->sideDistX = (map->player->x_pos - ray->mapX) * ray->deltaDistX;
    }
    else
    {
        ray->stepX = 1;
        ray->sideDistX = (ray->mapX + 1.0 - map->player->x_pos) * ray->deltaDistX;
    }
    if (ray->rayDirY < 0)
    {
        ray->stepY = -1;
        ray->sideDistY = (map->player->y_pos - ray->mapY) * ray->deltaDistY;
    }
    else
    {
        ray->stepY = 1;
        ray->sideDistY = (ray->mapY + 1.0 - map->player->y_pos) * ray->deltaDistY;
    }
}

void perform_dda(t_map *map, t_ray *ray)
{
    while (ray->hit == 0)
    {
        if (ray->sideDistX < ray->sideDistY)
        {
            ray->sideDistX += ray->deltaDistX;
            ray->mapX += ray->stepX;
            ray->side = 0;
        }
        else
        {
            ray->sideDistY += ray->deltaDistY;
            ray->mapY += ray->stepY;
            ray->side = 1;
        }
        if (map->map[ray->mapY][ray->mapX] == '1')
            ray->hit = 1;
    }
    calc_perp_wall_dist(map, ray);
}

void calc_perp_wall_dist(t_map *map, t_ray *ray)
{
    if (ray->side == 0)
        ray->perpWallDist = (ray->mapX - map->player->x_pos + 
                            (1 - ray->stepX) / 2) / ray->rayDirX;
    else
        ray->perpWallDist = (ray->mapY - map->player->y_pos + 
                            (1 - ray->stepY) / 2) / ray->rayDirY;
}

void calc_wall_specs(t_ray *ray, int *drawStart, int *drawEnd, t_player *player)
{
    ray->lineHeight = (int)(HEIGHT / ray->perpWallDist);
    *drawStart = -ray->lineHeight / 2 + HEIGHT / 2;
    if (*drawStart < 0)
        *drawStart = 0;
    *drawEnd = ray->lineHeight / 2 + HEIGHT / 2;
    if (*drawEnd >= HEIGHT)
        *drawEnd = HEIGHT - 1;
    calc_wall_x(ray, player);
}

void calc_wall_x(t_ray *ray, t_player *player)
{
    if (ray->side == 0)
        ray->wallX = player->y_pos + ray->perpWallDist * ray->rayDirY;
    else
        ray->wallX = player->x_pos + ray->perpWallDist * ray->rayDirX;
    ray->wallX -= floor(ray->wallX);

    ray->texX = (int)(ray->wallX * (double)TEXTURE_WIDTH);
    if (ray->side == 0 && ray->rayDirX > 0)
        ray->texX = TEXTURE_WIDTH - ray->texX - 1;
    if (ray->side == 1 && ray->rayDirY < 0)
        ray->texX = TEXTURE_WIDTH - ray->texX - 1;

    determine_texture(ray);
}


void determine_texture(t_ray *ray)
{
    if (ray->side == 0)
    {
        ray->texNum = (ray->rayDirX > 0) ? 2 : 3; // 2 = East, 3 = West
    }
    else
    {
        ray->texNum = (ray->rayDirY > 0) ? 1 : 0; // 1 = South, 0 = North
    }
}



