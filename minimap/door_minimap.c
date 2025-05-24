#include "../cub3d.h"

void draw_horizontal_door_open(t_img *img, int x, int y, int door_color)
{
    int by;
    int bx;
    int door_start_y;

    door_start_y = TILE_SIZE / 4;

    by = 0;
    while (by < TILE_SIZE)
    {
        bx = 0;
        while (bx < TILE_SIZE)
        {
            if (by >= door_start_y && by < door_start_y + DOORWIDTH &&
                (bx < DOORWIDTH || bx >= TILE_SIZE - DOORWIDTH))
                my_mlx_pixel_put(img, x + bx, y + by, door_color);
            else
                my_mlx_pixel_put(img, x + bx, y + by, EMPTY_COLOR);
            bx++;
        }
        by++;
    }
}


void draw_vertical_door_open(t_img *img, int x, int y, int door_color)
{
    int by;
    int bx;
    int door_start_x;

    door_start_x = TILE_SIZE / 4;

    by = 0;
    while (by < TILE_SIZE)
    {
        bx = 0;
        while (bx < TILE_SIZE)
        {
            if (bx >= door_start_x && bx < door_start_x + DOORWIDTH &&
                (by < DOORWIDTH || by >= TILE_SIZE - DOORWIDTH))
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
            if (by >= TILE_SIZE / 4 && by < TILE_SIZE / 4 + DOORWIDTH)
                my_mlx_pixel_put(img, x + bx, y + by, door_color);
            else
                my_mlx_pixel_put(img, x + bx, y + by, EMPTY_COLOR);
            bx++;
        }
        by++;
    }
}

void draw_vertical_door(t_img *img, int x, int y, int door_color)
{
    int by;
    int bx;
    int door_column;

    door_column = TILE_SIZE/4;
    by = 0;
    while (by < TILE_SIZE)
    {
        bx = 0;
        while (bx < TILE_SIZE)
        {
            if (bx >= door_column && bx < door_column + DOORWIDTH)
                my_mlx_pixel_put(img, x + bx, y + by, door_color);
            else
                my_mlx_pixel_put(img, x + bx, y + by, EMPTY_COLOR);
            bx++;
        }
        by++;
    }
}


void check_map_door(t_var *data, int x, int y, int draw_x, int draw_y)
{
    char tile;

    tile = data->map.arr[y][x];
    if (tile == DOORH_CLOSE)
        draw_horizontal_door(&data->image, draw_x, draw_y, DOOR_COLOR);
    else if (tile == DOORV_CLOSE)
        draw_vertical_door(&data->image, draw_x, draw_y, DOOR_COLOR);
    else if (tile == DOORH_OPEN)
        draw_horizontal_door_open(&data->image, draw_x, draw_y, DOOR_OPEN_COLOR);
    else if (tile == DOORV_OPEN)
        draw_vertical_door_open(&data->image, draw_x, draw_y, DOOR_OPEN_COLOR);
}
