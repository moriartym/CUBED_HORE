#include "../cub3d.h"

bool is_wall(t_var * data, int x, int y, int notWall)
{
    if (notWall)
        return (false);
    if (y < 0 || y >= data->big_height || data->big_map[y] == NULL)
        return false;
    if (x < 0 || x >= (int)ft_strlen(data->big_map[y]))
        return false;
    char c = data->big_map[y][x];
    return (c == WALL || c == DOORV_CLOSE || c == DOORV_OPEN || c == DOORH_CLOSE ||c ==  DOORH_OPEN);
}

void cast_vertical(t_var* data, t_ray* ray)
{
    ray->disV = 100000;
    ray->dof = 0;
    ray->tan = - tan(ray->ra);
    ray->cur_tile = 0;
    if (cos(ray->ra) > 0.001)
    {
        ray->rx = ((int)(data->player.px) / TILE_SIZE_BIG) * TILE_SIZE_BIG + TILE_SIZE_BIG;
        ray->ry = (data->player.px - ray->rx) * ray->tan + data->player.py;
        ray->xo = TILE_SIZE_BIG;
        ray->yo = -ray->xo * ray->tan;
    }
    else if (cos(ray->ra) < -0.001)
    {
        ray->rx = ((int)(data->player.px) / TILE_SIZE_BIG) * TILE_SIZE_BIG - 0.0001;
        ray->ry = (data->player.px - ray->rx) * ray->tan + data->player.py;
        ray->xo = -TILE_SIZE_BIG;
        ray->yo = -ray->xo * ray->tan;
    }
    else
    {
        ray->rx = data->player.px;
        ray->ry = data->player.py;
        ray->dof = data->big_width;
    }
    vertical_dof(data, ray);
}

void vertical_dof(t_var* data, t_ray* ray)
{
    while (ray->dof < data->big_width)
    {
        ray->mx = (int)(ray->rx) / TILE_SIZE_BIG;
        ray->my = (int)(ray->ry) / TILE_SIZE_BIG;
        ray->oriX = ray->rx;
        ray->oriY = ray->ry;
        ray->sideV = 0;
        if (is_wall(data, ray->mx, ray->my, ray->cur_tile))
        {
            if (ray->hitTypeV != 'S')
                ray->hitTypeV = data->big_map[ray->my][ray->mx];
            ray->dof = data->big_width;
            ray->vx = ray->rx;
            ray->vy = ray->ry;
            ray->disV = sqrt(pow(ray->rx - data->player.px, 2) + pow(ray->ry - data->player.py, 2));
        }
        else
        {
            ray->rx = ray->oriX + ray->xo;
            ray->ry = ray->oriY + ray->yo;
            ray->dof += 1;
        }
        ray->cur_tile = 0;
    }
}

void cast_horizontal(t_var* data, t_ray* ray)
{
    ray->disH = 100000;
    ray->dof = 0;
    ray->tan =  1 / ray->tan;
    ray->cur_tile = 0;
    if (sin(ray->ra) < -0.001)
    {
        ray->ry = ((int)(data->player.py) / TILE_SIZE_BIG) * TILE_SIZE_BIG - 0.0001;
        ray->rx = (data->player.py - ray->ry) * ray->tan + data->player.px;
        ray->yo = -TILE_SIZE_BIG;
        ray->xo = -ray->yo * ray->tan;
    }
    else if (sin(ray->ra) > 0.001)
    {
        ray->ry = ((int)(data->player.py) / TILE_SIZE_BIG) * TILE_SIZE_BIG + TILE_SIZE_BIG;
        ray->rx = (data->player.py - ray->ry) * ray->tan + data->player.px;
        ray->yo = TILE_SIZE_BIG;
        ray->xo = -ray->yo * ray->tan;
    }
    else
    {
        ray->rx = data->player.px;
        ray->ry = data->player.py;
        ray->dof = data->big_width;
    }
    horizontal_dof(data, ray);
}

void horizontal_dof(t_var* data, t_ray* ray)
{
    while (ray->dof < data->big_height)
    {
        ray->mx = (int)(ray->rx) / TILE_SIZE_BIG;
        ray->my = (int)(ray->ry) / TILE_SIZE_BIG;
        ray->oriX = ray->rx;
        ray->oriY = ray->ry;
        ray->sideH = 1;
        if (is_wall(data, ray->mx, ray->my, ray->cur_tile))
        {
            if (ray->hitTypeH != 'S')
                ray->hitTypeH = data->big_map[ray->my][ray->mx];
            ray->dof = data->big_height;
            ray->disH = sqrt(pow(ray->rx - data->player.px, 2) + pow(ray->ry - data->player.py, 2));
        }
        else
        {
            ray->rx = ray->oriX + ray->xo;
            ray->ry = ray->oriY + ray->yo;
            ray->dof += 1;
        }
        ray->cur_tile = 0;
    }
}