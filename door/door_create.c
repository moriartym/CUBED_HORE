#include "../cub3d.h"

t_door *new_door(t_var *data, int x, int y, char *tile)
{
    t_door *new;
    
    new = malloc(sizeof(t_door));
    if (!new)
        handle_error(NULL, "malloc error", &data->map, data);
    new->idX = x;
    new->idY = y;
    if (*tile == DOORH_CLOSE || *tile == DOORH_OPEN)
    {
        new->xStart = x * TILE_SIZE;
        new->xEnd = new->xStart + TILE_SIZE;
        new->yStart = y * TILE_SIZE + (TILE_SIZE - DOORWIDTH) / 2;
        new->yEnd = new->yStart + DOORWIDTH;
    }
    else
    {
        new->xStart = x * TILE_SIZE + (TILE_SIZE - DOORWIDTH) / 2;
        new->xEnd = new->xStart + DOORWIDTH;    
        new->yStart = y * TILE_SIZE;
        new->yEnd = new->yStart + TILE_SIZE;
    }
    new->next = NULL;
    new->status = tile;

    // Debug print
    if (new)
    {
        printf("Door created at tile (%d, %d)\n", x, y);
        printf("Door created at tile (%c)\n", *tile);
        printf("Position: xStart = %f, xEnd = %f, yStart = %f, yEnd = %f\n",
            new->xStart, new->xEnd, new->yStart, new->yEnd);
    }


    return (new);
}

void add_door(t_var *data, int x, int y, char *tile)
{
    t_door *new;
    t_door *cur;

    new = new_door(data, x, y, tile);
    if (data->map.doors == NULL)
    {
        data->map.doors = new;
        return ;
    }
    cur = data->map.doors;
    while (cur->next != NULL)
        cur = cur->next;
    cur->next = new;
}

void delete_door(t_var *data, int x, int y)
{
    t_door *cur;
    t_door *prev;

    prev = NULL;
    cur = data->map.doors;
    while (cur != NULL)
    {
        if (cur->idX == x && cur->idY == y)
        {
            if (prev == NULL)
                data->map.doors = cur->next;
            else
                prev->next = cur->next;
		    ft_free_ptr((void **)&cur);
            break ;
        }
        prev = cur;
        cur = cur->next;
    }
}

// new
void create_door_big_map(t_var *data, int y, int x)
{
    int i, j;
    char type = data->map.arr[y][x];
    int base_y = y * 4;
    int base_x = x * 4;

    if (type == DOORV_CLOSE)
    {
        i = 0;
        while (i < 4)
        {
            data->big_map[base_y + i][base_x + 0] = EMPTY_SPACE;
            data->big_map[base_y + i][base_x + 1] = DOORV_CLOSE;
            data->big_map[base_y + i][base_x + 2] = EMPTY_SPACE;
            data->big_map[base_y + i][base_x + 3] = EMPTY_SPACE;
            i++;
        }
    }
    else if (type == DOORH_CLOSE)
    {
        for (j = 0; j < 4; j++)
        {
            data->big_map[base_y + 0][base_x + j] = EMPTY_SPACE;
            data->big_map[base_y + 3][base_x + j] = EMPTY_SPACE;
        }
        for (j = 0; j < 4; j++)
        {
            data->big_map[base_y + 1][base_x + j] = DOORH_CLOSE;
            data->big_map[base_y + 2][base_x + j] =  EMPTY_SPACE;
        }
    }
    print_map_and_enemies(data);
}

void delete_door_big_map(t_var *data, int y, int x)
{
    int i, j;
    int base_y = y * 4;
    int base_x = x * 4;

    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            data->big_map[base_y + i][base_x + j] = EMPTY_SPACE;  // empty space pattern
    
    print_map_and_enemies(data);
}


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
            add_door(data, tile_in_front_x, tile_in_front_y, tile);
            create_door_big_map(data, tile_in_front_y, tile_in_front_x); // ← NEW
        }
        else if (*tile == DOORH_CLOSE || *tile == DOORH_OPEN || *tile == DOORV_CLOSE || *tile == DOORV_OPEN)
        {
            *tile = EMPTY_SPACE;
            delete_door(data, tile_in_front_x, tile_in_front_y);
            delete_door_big_map(data, tile_in_front_y, tile_in_front_x);
        }
    }
}

void update_door_big_map(t_var *data, int y, int x)
{
    int i, j;
    char type = data->map.arr[y][x];
    int base_y = y * 4;
    int base_x = x * 4;

    // DOORH_OPEN → 0330 pattern
    if (type == DOORV_OPEN)
    {
        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 4; j++)
                data->big_map[base_y + i][base_x + j] = EMPTY_SPACE;
        }
        for (j = 1; j <= 1; j++)
        {
            data->big_map[base_y + 0][base_x + j] = DOORV_OPEN;
            data->big_map[base_y + 3][base_x + j] = DOORV_OPEN;
        }
    }
    // DOORV_OPEN → 5005 pattern
    else if (type == DOORH_OPEN)
    {
        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 4; j++)
                data->big_map[base_y + i][base_x + j] = EMPTY_SPACE;
        }
        for (i = 1; i <= 1; i++)
        {
            data->big_map[base_y + i][base_x + 0] = DOORH_OPEN;
            data->big_map[base_y + i][base_x + 3] = DOORH_OPEN;
        }
    }
    print_map_and_enemies(data);
}

void open_door(t_var *data)
{
    int tile_in_front_x;
    int tile_in_front_y;

    tile_in_front_x = get_front_tile_x(data);
    tile_in_front_y = get_front_tile_y(data);
    if (tile_in_front_x >= 0 && tile_in_front_x < data->map.width &&
        tile_in_front_y >= 0 && tile_in_front_y < data->map.height)
    {
        char *tile = &data->map.arr[tile_in_front_y][tile_in_front_x];
        if (*tile == DOORH_CLOSE || *tile == DOORV_CLOSE)
        {
            *tile += 1;
            update_door_big_map(data, tile_in_front_y, tile_in_front_x);
            printf("%c: Door Opened\n", *tile);
        }
        else if (*tile == DOORH_OPEN || *tile == DOORV_OPEN)
        {
            *tile -= 1;
            create_door_big_map(data, tile_in_front_y, tile_in_front_x); // restore closed pattern
            printf("%c: Door Closed\n", *tile);
        }
    }
}
