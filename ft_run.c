/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_run.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/29 12:50:42 by novan-ve       #+#    #+#                */
/*   Updated: 2020/02/02 20:51:10 by anon          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

int		ft_free_img(t_data *data)
{
	mlx_destroy_image(data->run->mlx, data->n->img);
	mlx_destroy_image(data->run->mlx, data->s->img);
	mlx_destroy_image(data->run->mlx, data->e->img);
	mlx_destroy_image(data->run->mlx, data->w->img);
	ft_free_parse(data->p, "Exited cleanly", data->p->map_y - 1);
	return (0);
}

int		ft_key_search(t_data *data)
{
	if (data->keys->key_up == 1 || data->keys->key_down == 1 || data->keys->key_right == 1 || data->keys->key_left == 1)
	{
		if (data->keys->key_up == 1)
		{
			if (data->p->map[(int)(data->run->posY)][(int)(data->run->posX + data->run->dirX * ((double)data->p->height / 8000))] == 0)
				data->run->posX += data->run->dirX * ((double)data->p->height / 8000);
			if (data->p->map[(int)(data->run->posY + data->run->dirY * ((double)data->p->height / 8000))][(int)(data->run->posX)] == 0)
				data->run->posY += data->run->dirY * ((double)data->p->height / 8000);
		}
		if (data->keys->key_down == 1)
		{
			if (data->p->map[(int)(data->run->posY)][(int)(data->run->posX - data->run->dirX * ((double)data->p->height / 8000))] == 0)
				data->run->posX -= data->run->dirX * ((double)data->p->height / 8000);
			if (data->p->map[(int)(data->run->posY - data->run->dirY * ((double)data->p->height / 8000))][(int)(data->run->posX)] == 0)
				data->run->posY -= data->run->dirY * ((double)data->p->height / 8000);
		}
		if (data->keys->key_right == 1)
		{
			double oldDirX = data->run->dirX;
			data->run->dirX = data->run->dirX * cos(((double)data->p->width / 38787)) - data->run->dirY * sin(((double)data->p->width / 38787));
			data->run->dirY = oldDirX * sin(((double)data->p->width / 38787)) + data->run->dirY * cos(((double)data->p->width / 38787));
			double oldPlaneX = data->run->planeX;
			data->run->planeX = data->run->planeX * cos(((double)data->p->width / 38787)) - data->run->planeY * sin(((double)data->p->width / 38787));
			data->run->planeY = oldPlaneX * sin(((double)data->p->width / 38787)) + data->run->planeY * cos(((double)data->p->width / 38787));
		}
		if (data->keys->key_left == 1)
		{
			double oldDirX = data->run->dirX;
			data->run->dirX = data->run->dirX * cos(-((double)data->p->width / 38787)) - data->run->dirY * sin(-((double)data->p->width / 38787));
			data->run->dirY = oldDirX * sin(-((double)data->p->width / 38787)) + data->run->dirY * cos(-((double)data->p->width / 38787));
			double oldPlaneX = data->run->planeX;
			data->run->planeX = data->run->planeX * cos(-((double)data->p->width / 38787)) - data->run->planeY * sin(-((double)data->p->width / 38787));
			data->run->planeY = oldPlaneX * sin(-((double)data->p->width / 38787)) + data->run->planeY * cos(-((double)data->p->width / 38787));
		}
		ft_loop(data);
	}
	return (0);
}

int		ft_key_press(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		ft_free_img(data);
	if (keycode == KEY_UP)
		data->keys->key_up = 1;
	if (keycode == KEY_DOWN)
		data->keys->key_down = 1;
	if (keycode == KEY_RIGHT)
		data->keys->key_right = 1;
	if (keycode == KEY_LEFT)
		data->keys->key_left = 1;
	return (0);
}

int		ft_key_release(int keycode, t_data *data)
{
	if (keycode == KEY_UP)
		data->keys->key_up = 0;
	if (keycode == KEY_DOWN)
		data->keys->key_down = 0;
	if (keycode == KEY_RIGHT)
		data->keys->key_right = 0;
	if (keycode == KEY_LEFT)
		data->keys->key_left = 0;
	return (0);
}

t_img	init_img(t_data *data, char *file)
{
	t_img	tmp;

	tmp.img = mlx_xpm_file_to_image(data->run->mlx, file, &tmp.texWidth, &tmp.texHeight);
	tmp.addr = mlx_get_data_addr(tmp.img, &tmp.bits_per_pixel, &tmp.line_size, &tmp.endian);
	return (tmp);
}

int		ft_run_game(t_data *data)
{
	t_img	n;
	t_img	s;
	t_img	e;
	t_img	w;
	t_img	sp;

	data->run->mlx = mlx_init();
	data->run->win = mlx_new_window(data->run->mlx, data->p->width, data->p->height, "cub3d");
	n = init_img(data, data->p->no);
	data->n = &n;
	s = init_img(data, data->p->so);
	data->s = &s;
	w = init_img(data, data->p->we);
	data->w = &w;
	e = init_img(data, data->p->ea);
	data->e = &e;
	sp = init_img(data, data->p->sprite);
	data->sp = &sp;
	ft_loop(data);
	mlx_do_key_autorepeaton(data->run->mlx);
	mlx_hook(data->run->win, 2, 1L<<0, ft_key_press, data);
	mlx_hook(data->run->win, 3, 1L<<1, ft_key_release, data);
	mlx_hook(data->run->win, 17, 0L, ft_free_img, data);
	mlx_loop_hook(data->run->mlx, &ft_key_search, data);
	mlx_loop(data->run->mlx);
	return (0);
}
