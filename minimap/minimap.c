#include "../cub3d.h"

void draw_tile(t_img *img, int x, int y, int color)
{
    int by;
    int bx;

    by = 0;
    while (by < TILE_SIZE)
    {
        bx = 0;
        while (bx < TILE_SIZE)
        {
            my_mlx_pixel_put(img, x + bx, y + by, color);
            bx++;
        }
        by++;
    }
}


void draw_map(t_var *data, int x, int y, int draw_x, int draw_y)
{
    int color;
    char tile;

    if (y < 0 || y >= data->map.height || x < 0 || x >= data->map.width)
    {
        draw_tile(&data->image, draw_x, draw_y, BLACK_COLOR);
        return;
    }
    tile = data->map.arr[y][x];
    if (tile == EMPTY_SPACE)
        color = EMPTY_COLOR;
    else if (tile == WALL)
        color = WALL_COLOR;
    else if (tile == DOORH_CLOSE || tile == DOORV_CLOSE 
        || tile == DOORH_OPEN || tile == DOORV_OPEN)
    {
        check_map_door(data , x,y, draw_x, draw_y);
        return ;
    }
    else
        color = BLACK_COLOR;
    draw_tile(&data->image, draw_x, draw_y, color);
}

void map_shift(t_var *data)
{
    int ipx;
    int ipy;
    int margin;
    int shift;

    ipx = (int)(data->player.px / TILE_SIZE);
    ipy = (int)(data->player.py / TILE_SIZE);
    margin = 2;
    shift = 4;
    if (ipx < data->minimap_offset_x + margin)
        data->minimap_offset_x -= shift;
    else if (ipx >= data->minimap_offset_x + MINIMAP_TILE - margin)
        data->minimap_offset_x += shift;
    if (ipy < data->minimap_offset_y + margin)
        data->minimap_offset_y -= shift;
    else if (ipy >= data->minimap_offset_y + MINIMAP_TILE - margin)
        data->minimap_offset_y += shift;
}

void clamp_map(t_var *data)
{
    if (data->minimap_offset_x + MINIMAP_TILE > data->map.max_length)
        data->minimap_offset_x = data->map.max_length - MINIMAP_TILE;
    if (data->minimap_offset_x < 0)
        data->minimap_offset_x = 0;
    if (data->minimap_offset_y + MINIMAP_TILE > data->map.height)
        data->minimap_offset_y = data->map.height - MINIMAP_TILE;
    if (data->minimap_offset_y < 0)
        data->minimap_offset_y = 0;
}



void create_minimap(t_var *data)
{
    int x;
    int y;

    y = 0;
    map_shift(data); 
    clamp_map(data);
    while (y < MINIMAP_TILE)
    {
        x = 0;
        while (x < MINIMAP_TILE)
        {
            draw_map(data, data->minimap_offset_x + x, data->minimap_offset_y + y,
                        x * MINIMAP_TILE_SIZE, y * MINIMAP_TILE_SIZE);
            x++;
        }
        y++;
    }
}
