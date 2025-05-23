#include "../cub3d.h"



//UPDATE
bool is_it_door(t_var *data, float x, float y)
{
    t_door *cur;
    int ix;
    int iy;
    char tile;

    ix = (int)x / TILE_SIZE;
    iy = (int)y / TILE_SIZE;
    if (ix < 0 || ix >= data->map.width || iy < 0 || iy >= data->map.height)
        return true;
    tile = data->map.arr[iy][ix];
    cur = data->map.doors;
    while (cur)
    {
        if (*cur->status == tile)
        {
            if (x  > cur->xStart && x < cur->xEnd &&
                y > cur->yStart && y < cur->yEnd)
                return (true);
        }
        cur = cur->next;
    }
    return (false);
}

int enemy_left(t_var *data, t_sprite *sp)
{
    if ((sp->is_unstucking || sp->x > data->player.px))
    {
        if (is_cell_valid(data, sp->spx_left, sp->y))
        {
            if (!is_cell_valid(data, sp->spx_left, sp->spy_up) && is_cell_valid(data, sp->x, sp->spy_up))
            {
                sp->y += sp->speed;
                return (sp->is_unstucking = 1,0);
            }
            if (!is_cell_valid(data, sp->spx_left, sp->spy_down) && is_cell_valid(data, sp->x, sp->spy_down))
            {
                sp->y -= sp->speed;
                return (sp->is_unstucking = 1,0);
            }
            sp->x -= sp->speed;
            return (0);
        }
        sp->is_unstucking = 1;
    } 
    return (1);
}

int enemy_right(t_var *data, t_sprite *sp)
{
    if ((sp->is_unstucking || sp->x < data->player.px))
    {
        if (is_cell_valid(data, sp->spx_right, sp->y))
        {
            if (!is_cell_valid(data, sp->spx_right, sp->spy_up) && is_cell_valid(data, sp->x, sp->spy_up))
            {
                sp->y += sp->speed;
                return (sp->is_unstucking = 1,0);
            }
            if (!is_cell_valid(data, sp->spx_right, sp->spy_down) && is_cell_valid(data, sp->x, sp->spy_down))
            {
                sp->y -= sp->speed;
                return (sp->is_unstucking = 1,0);
            }
            sp->x += sp->speed;
            return (0);
        }
        sp->is_unstucking = 1;
    }
    return (1);
}

int enemy_up(t_var *data, t_sprite *sp)
{
    if ((sp->is_unstucking || sp->y > data->player.py))
    {
        if (is_cell_valid(data, sp->x, sp->spy_up))
        {
            if (!is_cell_valid(data, sp->spx_left, sp->spy_up) && is_cell_valid(data, sp->spx_left, sp->y))
            {
                sp->x += sp->speed;
                return (sp->is_unstucking = 1,0);
            }
            if (!is_cell_valid(data, sp->spx_right, sp->spy_up) && is_cell_valid(data, sp->spx_right, sp->y))
            {
                sp->x -= sp->speed;
                return (sp->is_unstucking = 1,0);
            }
            sp->y -= sp->speed;
            return (0);
        }
        sp->is_unstucking = 1;
    }
    return (1);
}

int enemy_down(t_var *data, t_sprite *sp)
{
    if ((sp->is_unstucking || sp->y < data->player.py))
    {
        if (is_cell_valid(data, sp->x, sp->spy_down))
        {
            if (!is_cell_valid(data, sp->spx_left, sp->spy_down) && is_cell_valid(data, sp->spx_left, sp->y))
            {
                sp->x += sp->speed;
                return (sp->is_unstucking = 1,0);
            }
            if (!is_cell_valid(data, sp->spx_right, sp->spy_down) && is_cell_valid(data, sp->spx_right, sp->y))
            {
                sp->x -= sp->speed;
                return (sp->is_unstucking = 1,0);
            }
            sp->y += sp->speed;
            return (0);
        }
        sp->is_unstucking = 1;
    }
    return (1);
}
