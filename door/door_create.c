#include "../cub3d.h"

void create_door(t_var *data)
{
    char *tile;
    int tile_in_front_x;
    int tile_in_front_y;
    float angle;

    tile_in_front_x = get_front_tile_x(data);
    tile_in_front_y = get_front_tile_y(data);
    if (tile_in_front_x >= 0 && tile_in_front_x < data->map.width &&
        tile_in_front_y >= 0 && tile_in_front_y < data->map.height)
    {
        tile = &data->map.arr[tile_in_front_y][tile_in_front_x];
        if (*tile == EMPTY_SPACE)
        {
            angle = normalize_radians(data->player.pa);
            if ((angle > PI / 4 && angle < 3 * PI / 4) || (angle > 5 * PI / 4 && angle < 7 * PI / 4))
                *tile = DOORH_CLOSE;
            else
                *tile = DOORV_CLOSE;
            create_door_big_map(data, tile_in_front_y, tile_in_front_x);
        }
        else if (*tile == DOORH_CLOSE || *tile == DOORH_OPEN || *tile == DOORV_CLOSE || *tile == DOORV_OPEN)
        {
            *tile = EMPTY_SPACE;
            delete_door_big_map(data, tile_in_front_y, tile_in_front_x);
        }
    }
}


void open_door(t_var *data)
{
    int tile_in_front_x;
    int tile_in_front_y;
    char *tile;

    tile_in_front_x = get_front_tile_x(data);
    tile_in_front_y = get_front_tile_y(data);
    if (tile_in_front_x >= 0 && tile_in_front_x < data->map.width &&
        tile_in_front_y >= 0 && tile_in_front_y < data->map.height)
    {
        tile = &data->map.arr[tile_in_front_y][tile_in_front_x];
        if (*tile == DOORH_CLOSE || *tile == DOORV_CLOSE)
        {
            *tile += 1;
            update_door_big_map(data, tile_in_front_y, tile_in_front_x);
            printf("%c: Door Opened\n", *tile);
        }
        else if (*tile == DOORH_OPEN || *tile == DOORV_OPEN)
        {
            *tile -= 1;
            create_door_big_map(data, tile_in_front_y, tile_in_front_x);
            printf("%c: Door Closed\n", *tile);
        }
    }
}
