#include "../cub3d.h"

void draw_one_winning_tile(t_var *data, int draw_x, int draw_y)
{
    int px;
    int py;

    px = 0;
    py = 0;
    while (py < MINIMAP_TILE_SIZE)
    {
        px = 0;
        while (px < MINIMAP_TILE_SIZE)
        {
            if (draw_x + px >= 0 && draw_x + px < MINIMAP_SIZE &&
                draw_y + py >= 0 && draw_y + py < MINIMAP_SIZE)
                my_mlx_pixel_put(&data->image, draw_x + px, draw_y + py, WIN_COLOR);
            px++;
        }
        py++;
    }
}

void draw_winning_tile(t_var *data)
{
    int x;
    int y;
    int draw_x;
    int draw_y;

    y = 0;
    while (y < data->map.height)
    {
        x = 0;
        while (x < data->map.width)
        {
            if (data->map.arr[y][x] == '8')
            {
                draw_x = (x - data->minimap_offset_x) * MINIMAP_TILE_SIZE;
                draw_y = (y - data->minimap_offset_y) * MINIMAP_TILE_SIZE;
                if (draw_x + MINIMAP_TILE_SIZE > 0 && draw_x < MINIMAP_SIZE &&
                    draw_y + MINIMAP_TILE_SIZE > 0 && draw_y < MINIMAP_SIZE)
                    draw_one_winning_tile(data, draw_x, draw_y);
                return;
            }
            x++;
        }
        y++;
    }
}