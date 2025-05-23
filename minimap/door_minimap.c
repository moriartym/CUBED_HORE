#include "../cub3d.h"

void draw_vertical_door(t_img *img, int x, int y, int door_color)
{
    int by;
    int bx;

    by = 0;
    while (by < TILE_SIZE)
    {
        bx = 0;
        while (bx < TILE_SIZE)
        {
            if (bx >= (TILE_SIZE - DOORWIDTH) / 2 && bx < (TILE_SIZE + DOORWIDTH) / 2)
                my_mlx_pixel_put(img, x + bx, y + by, door_color);
            else
                my_mlx_pixel_put(img, x + bx, y + by, EMPTY_COLOR);
            bx++;
        }
        by++;
    }
}

void draw_horizontal_door(t_img *img, int x, int y, int door_color)
{
    int by;
    int bx;

    by = 0;
    while (by < TILE_SIZE)
    {
        bx = 0;
        while (bx < TILE_SIZE)
        {
            if (by >= (TILE_SIZE - DOORWIDTH) / 2 && by < (TILE_SIZE + DOORWIDTH) / 2)
                my_mlx_pixel_put(img, x + bx, y + by, door_color);
            else
                my_mlx_pixel_put(img, x + bx, y + by, EMPTY_COLOR);
            bx++;
        }
        by++;
    }
}