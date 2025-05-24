#include "../cub3d.h"

void create_door_big_map(t_var *data, int y, int x)
{
    int i;
    int base_y;
    int base_x;

    base_y = y * 4;
    base_x = x * 4;
    delete_door_big_map(data, y, x);
    if (data->map.arr[y][x] == DOORV_CLOSE)
    {
        i = 0;
        while (i < 4)
        {
            data->big_map[base_y + i][base_x + 1] = DOORV_CLOSE;
            i++;
        }
    }
    else if (data->map.arr[y][x] == DOORH_CLOSE)
    {
        while (i < 4)
        {
            data->big_map[base_y + 1][base_x + i] = DOORH_CLOSE;
            i++;
        }
    }
    print_map_and_enemies(data);
}

void delete_door_big_map(t_var *data, int y, int x)
{
    int i;
    int j;
    int base_y;
    int base_x;

    base_y = y * 4;
    base_x = x *4;
    i = 0;
    while (i < 4)
    {
        j = 0;
        while (j < 4)
        {
            data->big_map[base_y + i][base_x + j] = EMPTY_SPACE;
            j++;
        }
        i++;
    }
}


void update_door_big_map(t_var *data, int y, int x)
{
    int i;
    int j;
    int base_y;
    int base_x;

    base_y = y * 4;
    base_x = x *4;
    char type = data->map.arr[y][x];
    i = 0;
    if (type == DOORV_OPEN)
    {
        delete_door_big_map(data, y, x);
        data->big_map[base_y + 0][base_x + 1] = DOORV_OPEN;
        data->big_map[base_y + 3][base_x + 1] = DOORV_OPEN;
    }
    else if (type == DOORH_OPEN)
    {
        delete_door_big_map(data, y, x);
        data->big_map[base_y + 1][base_x + 0] = DOORH_OPEN;
        data->big_map[base_y + 1][base_x + 3] = DOORH_OPEN;
    }
    print_map_and_enemies(data);
}