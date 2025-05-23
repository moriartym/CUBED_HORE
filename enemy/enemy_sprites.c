#include "../cub3d.h"

int is_player_caught(t_sprite *sp, t_play *player, float radius)
{
    float dx;
    float dy;
    float dist;

    dx = sp->x - player->px;
    dy = sp->y - player->py;
    dist = sqrtf(dx * dx + dy * dy);
    return dist < radius;
}

bool is_cell_valid(t_var *data, float x, float y)
{
    int ix;
    int iy;
    char tile;

    ix = (int)x / TILE_SIZE_BIG;
    iy = (int)y / TILE_SIZE_BIG;
    if (ix < 0 || ix >= data->big_width|| iy < 0 || iy >= data->big_height)
        return false;
    tile = data->big_map[iy][ix];
    return (is_valid_movement(data, tile));
}

void resolve_enemy_dist(t_var *data, t_sprite *sp, t_sprite *other)
{
    float sp_new_x;
    float sp_new_y;
    float other_new_x;
    float other_new_y;
    
    if (sp->dist_sq < sp->min_dist * sp->min_dist && sp->dist_sq > 0)
    {
        sp->dist = sqrt(sp->dist_sq);
        sp->overlap = (sp->min_dist - sp->dist) / 2.0f;
        sp->adjust_x = (sp->dx / sp->dist) * sp->overlap;
        sp->adjust_y = (sp->dy / sp->dist) * sp->overlap;
        sp_new_x = sp->x - sp->adjust_x;
        sp_new_y = sp->y - sp->adjust_y;
        other_new_x = other->x + sp->adjust_x;
        other_new_y = other->y + sp->adjust_y;
        if (is_cell_valid(data, sp_new_x, sp->y))
            sp->x = sp_new_x;
        if (is_cell_valid(data, sp->x, sp_new_y))
            sp->y = sp_new_y;
        if (is_cell_valid(data, other_new_x, other->y))
            other->x = other_new_x;
        if (is_cell_valid(data, other->x, other_new_y))
            other->y = other_new_y;
    }
}

void resolve_enemy_collisions(t_var *data, t_sprite *sp)
{
    int i;
    t_sprite *other;

    i = 0;
    while (i < data->num_sprites)
    {
        other = &data->sprites[i];
        if (other == sp) 
        {
            i++;
            continue;
        }
        sp->dx = other->x - sp->x;
        sp->dy = other->y - sp->y;
        sp->dist_sq = sp->dx * sp->dx + sp->dy * sp->dy;
        sp->min_dist = 4.0f;
        resolve_enemy_dist(data,sp, other);
        i++;
    }
}

void move_enemy_towards_player(t_var *data, t_sprite *sp)
{
    sp->speed = ENEMY_SPEED;
    sp->margin = ENEMY_MARGIN;
    sp->spx = (int)(sp->x / TILE_SIZE_BIG);
    sp->spy = (int)(sp->y / TILE_SIZE_BIG);
    sp->spx_left = sp->x - sp->speed - sp->margin;
    sp->spx_right = sp->x + sp->speed + sp->margin;
    sp->spy_up = sp->y - sp->speed - sp->margin;
    sp->spy_down = sp->y + sp->speed + sp->margin;
    unstuck_move(data, sp);
    resolve_enemy_collisions(data, sp);
    if (is_player_caught(sp, &data->player, 10.0f))
    {
        printf("Player caught! 👻\nPress R to play again\n");
        data->state.state = LOSE;
    }
}
