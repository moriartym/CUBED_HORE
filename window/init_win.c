#include "../cub3d.h"

void load_win_gifs(t_var *data)
{
    load_single_image(data, &data->win_gif.zero, "textures/win/sayuri-1.xpm");
    load_single_image(data, &data->win_gif.one, "textures/win/sayuri-2.xpm");
    load_single_image(data, &data->win_gif.two, "textures/win/sayuri-3.xpm");
    load_single_image(data, &data->win_gif.three, "textures/win/sayuri-4.xpm");
}

void win(t_var *data)
{
    int px;
    int py;

    px = (int)(data->player.px / TILE_SIZE);
    py = (int)(data->player.py / TILE_SIZE);
    if (data->map.arr[py][px] == WIN_BLOCK)
    {
        printf("🎉 You win!\nPress R to play again\n");
        data->state.state = WIN;
    }
}

void change_to_win(t_var *data, t_bfs *bfs, int index)
{
    int i;
    int x;
    int y;

    i = 0;
    y = 0;
    while (y < data->map.height)
    {
        x = 0;
        while (x < data->map.width)
        {
            if (bfs->reachable[y][x] == true &&
                data->map.arr[y][x] == EMPTY_SPACE &&
                !(y == bfs->ipy && x == bfs->ipx))
            {
                if (i == index)
                {
                    data->map.arr[y][x] = WIN_BLOCK;
                    data->win_sprite.x = x * TILE_SIZE + 0.5 * TILE_SIZE;
                    data->win_sprite.y = y * TILE_SIZE + 0.5 * TILE_SIZE;
                    return ;
                }
                i++;
            }
            x++;
        }
        y++;
    }
}

void place_winning_tiles(t_var *data)
{
    t_bfs bfs;
    int y;
    int index;

    bfs = (t_bfs){0};
    do_bfs(data, &bfs);
    if (bfs.empty_spaces > 1)
    {
        index = rand() % bfs.empty_spaces;
        change_to_win(data, &bfs, index);
    } 
    else
        printf("Sorry, no winning tiles for this game.\n");
    free_enemy_bfs(data, &bfs);
}



void draw_win(t_var *data)
{
    t_edraw draw;

    draw = (t_edraw){0};
    init_enemy_draw(data, &draw);
    if (enemy_size(data, &draw, &data->win_sprite))
        return ;
    draw.frame = draw.anim_sequence[data->current_anim_index];
    draw.cur_img = NULL;
    if (draw.frame % 4 ==  0)
        draw.cur_img = &data->win_gif.zero;
    if (draw.frame % 4 ==  1)
        draw.cur_img = &data->win_gif.one;
    if (draw.frame % 4 ==  2)
        draw.cur_img = &data->win_gif.two;
    if (draw.frame % 4 ==  3)
        draw.cur_img = &data->win_gif.three;  
    screen_draw(data, &draw);
}