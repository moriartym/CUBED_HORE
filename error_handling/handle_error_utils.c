#include "../cub3d.h"

void free_state_images(t_var *data)
{
	free_single_img((void **)&data->state.win.img, data);
	free_single_img((void **)&data->state.lose.img, data);
}

void safe_close(int *fd)
{
	if (*fd >= 0)
	{
		close(*fd);
		*fd = -1;
	}
}

void free_single_img(void **img_ptr, t_var *data)
{
	if (img_ptr && *img_ptr)
	{
		mlx_destroy_image(data->mlx, *img_ptr);
		*img_ptr = NULL;
	}
}
