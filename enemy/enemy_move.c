#include "../cub3d.h"


int enemy_left(t_var *data, t_sprite *sp)
{
    if (is_cell_valid(data, sp->spx_left, sp->y))
    {
        if (!is_cell_valid(data, sp->spx_left, sp->spy_up) && is_cell_valid(data, sp->x, sp->spy_up))
        {
            sp->y += sp->speed;
            return (0);
        }
        if (!is_cell_valid(data, sp->spx_left, sp->spy_down) && is_cell_valid(data, sp->x, sp->spy_down))
        {
            sp->y -= sp->speed;
            return (0);
        }
        sp->x -= sp->speed;
        return (0);
    }
    return (1);
}

int enemy_right(t_var *data, t_sprite *sp)
{
    if (is_cell_valid(data, sp->spx_right, sp->y))
    {
        if (!is_cell_valid(data, sp->spx_right, sp->spy_up) && is_cell_valid(data, sp->x, sp->spy_up))
        {
            sp->y += sp->speed;
            return (0);
        }
        if (!is_cell_valid(data, sp->spx_right, sp->spy_down) && is_cell_valid(data, sp->x, sp->spy_down))
        {
            sp->y -= sp->speed;
            return (0);
        }
        sp->x += sp->speed;
        return (0);
    }
    return (1);
}

int enemy_up(t_var *data, t_sprite *sp)
{
    if (is_cell_valid(data, sp->x, sp->spy_up))
    {
        if (!is_cell_valid(data, sp->spx_left, sp->spy_up) && is_cell_valid(data, sp->spx_left, sp->y))
        {
            sp->x += sp->speed;
            return (0);
        }
        if (!is_cell_valid(data, sp->spx_right, sp->spy_up) && is_cell_valid(data, sp->spx_right, sp->y))
        {
            sp->x -= sp->speed;
            return (0);
        }
        sp->y -= sp->speed;
        return (0);
    }
    return (1);
}

int enemy_down(t_var *data, t_sprite *sp)
{
    if (is_cell_valid(data, sp->x, sp->spy_down))
    {
        if (!is_cell_valid(data, sp->spx_left, sp->spy_down) && is_cell_valid(data, sp->spx_left, sp->y))
        {
            sp->x += sp->speed;
            return (0);
        }
        if (!is_cell_valid(data, sp->spx_right, sp->spy_down) && is_cell_valid(data, sp->spx_right, sp->y))
        {
            sp->x -= sp->speed;
            return (0);
        }
        sp->y += sp->speed;
        return (0);
    }
    return (1);
}
