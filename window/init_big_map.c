#include "../cub3d.h"


void init_big_map(t_var *data)
{
    int y;
    int new_height;
    int new_width;

    new_height = data->big_height;
    new_width = data->big_width;
    data->big_map = malloc(sizeof(char *) * (new_height + 1));
    if (!data->big_map)
        handle_error(NULL, "malloc error", &data->map, data);
    y = 0;
    while (y < new_height)
    {
        data->big_map[y] = malloc(sizeof(char) * (new_width + 2));
        if (!data->big_map[y])
            handle_error(NULL, "malloc error", &data->map, data);
        data->big_map[y][new_width] = '\n';
        data->big_map[y][new_width + 1] = '\0';
        y++;
    }
}

void create_big_map_helper(t_var *data, int y, int x)
{
    int dy;
    int dx;
    char c;

    c = data->map.arr[y][x];
    dy = 0;
    while (dy < 4)
    {
        dx = 0;
        while (dx < 4)
        {
            data->big_map[y * 4 + dy][x * 4 + dx] = c;
            dx++;
        }
        dy++;
    }
}

void create_big_map(t_var *data)
{
    int y;
    int x;

    init_big_map(data);
    y = 0;
    while (y < data->map.height)
    {
        x = 0;
        while (x < data->map.width)
        {
            create_big_map_helper(data, y, x);
            x++;
        }
        y++;
    }
    data->big_map[data->big_height] = NULL;
}
