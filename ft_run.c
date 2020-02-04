/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_run.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/29 12:50:42 by novan-ve       #+#    #+#                */
/*   Updated: 2020/02/04 13:17:04 by anon          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_free_img(t_data *data)
{
	mlx_destroy_image(data->run->mlx, data->n->img);
	mlx_destroy_image(data->run->mlx, data->s->img);
	mlx_destroy_image(data->run->mlx, data->e->img);
	mlx_destroy_image(data->run->mlx, data->w->img);
	mlx_destroy_image(data->run->mlx, data->img->img);
	ft_free_sprite(data->p, "Exited cleanly", data->p->isprite - 1);
	return (0);
}

int		ft_key_search(t_data *data)
{
	if (data->keys->key_w == 1 || data->keys->key_s == 1 || data->keys->key_right == 1 || data->keys->key_left == 1 || data->keys->key_a == 1 || data->keys->key_d == 1)
	{
		if (data->keys->key_w == 1)
		{
			if (data->p->map[(int)(data->run->posY)][(int)(data->run->posX + data->run->dirX * ((double)data->p->height / 8000.0))] == 0)
				data->run->posX += data->run->dirX * ((double)data->p->height / 8000.0);
			if (data->p->map[(int)(data->run->posY + data->run->dirY * ((double)data->p->height / 8000.0))][(int)(data->run->posX)] == 0)
				data->run->posY += data->run->dirY * ((double)data->p->height / 8000.0);
		}
		if (data->keys->key_s == 1)
		{
			if (data->p->map[(int)(data->run->posY)][(int)(data->run->posX - data->run->dirX * ((double)data->p->height / 8000.0))] == 0)
				data->run->posX -= data->run->dirX * ((double)data->p->height / 8000.0);
			if (data->p->map[(int)(data->run->posY - data->run->dirY * ((double)data->p->height / 8000.0))][(int)(data->run->posX)] == 0)
				data->run->posY -= data->run->dirY * ((double)data->p->height / 8000.0);
		}
		if (data->keys->key_d == 1)
		{
			if (data->p->map[(int)(data->run->posY)][(int)(data->run->posX - data->run->dirY * ((double)data->p->height / 8000.0))] == 0)
				data->run->posX -= data->run->dirY * ((double)data->p->height / 8000.0);
			if (data->p->map[(int)(data->run->posY - data->run->dirX * -((double)data->p->height / 8000.0))][(int)(data->run->posX)] == 0)
				data->run->posY -= data->run->dirX * -((double)data->p->height / 8000.0);

		}
		if (data->keys->key_a == 1)
		{
			if (data->p->map[(int)(data->run->posY)][(int)(data->run->posX + data->run->dirY * ((double)data->p->height / 8000.0))] == 0)
				data->run->posX += data->run->dirY * ((double)data->p->height / 8000.0);
			if (data->p->map[(int)(data->run->posY + data->run->dirX * -((double)data->p->height / 8000.0))][(int)(data->run->posX)] == 0)
				data->run->posY += data->run->dirX * -((double)data->p->height / 8000.0);
		}
		if (data->keys->key_left == 1)
		{
			double oldDirX = data->run->dirX;
			data->run->dirX = data->run->dirX * cos(-((double)data->p->width / 32000.0)) - data->run->dirY * sin(-((double)data->p->width / 32000.0));
			data->run->dirY = oldDirX * sin(-((double)data->p->width / 32000.0)) + data->run->dirY * cos(-((double)data->p->width / 32000.0));
			double oldPlaneX = data->run->planeX;
			data->run->planeX = data->run->planeX * cos(-((double)data->p->width / 32000.0)) - data->run->planeY * sin(-((double)data->p->width / 32000.0));
			data->run->planeY = oldPlaneX * sin(-((double)data->p->width / 32000.0)) + data->run->planeY * cos(-((double)data->p->width / 32000.0));
		}
		if (data->keys->key_right == 1)
		{
			double oldDirX = data->run->dirX;
			data->run->dirX = data->run->dirX * cos(((double)data->p->width / 32000.0)) - data->run->dirY * sin(((double)data->p->width / 32000.0));
			data->run->dirY = oldDirX * sin(((double)data->p->width / 32000.0)) + data->run->dirY * cos(((double)data->p->width / 32000.0));
			double oldPlaneX = data->run->planeX;
			data->run->planeX = data->run->planeX * cos(((double)data->p->width / 32000.0)) - data->run->planeY * sin(((double)data->p->width / 32000.0));
			data->run->planeY = oldPlaneX * sin(((double)data->p->width / 32000.0)) + data->run->planeY * cos(((double)data->p->width / 32000.0));
		}
		ft_loop(data);
	}
	return (0);
}

int		ft_key_press(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		ft_free_img(data);
	if (keycode == KEY_RIGHT)
		data->keys->key_right = 1;
	if (keycode == KEY_LEFT)
		data->keys->key_left = 1;
	if (keycode == KEY_A)
		data->keys->key_a = 1;
	if (keycode == KEY_S)
		data->keys->key_s = 1;
	if (keycode == KEY_D)
		data->keys->key_d = 1;
	if (keycode == KEY_W)
		data->keys->key_w = 1;
	return (0);
}

int		ft_key_release(int keycode, t_data *data)
{
	if (keycode == KEY_RIGHT)
		data->keys->key_right = 0;
	if (keycode == KEY_LEFT)
		data->keys->key_left = 0;
	if (keycode == KEY_A)
		data->keys->key_a = 0;
	if (keycode == KEY_S)
		data->keys->key_s = 0;
	if (keycode == KEY_D)
		data->keys->key_d = 0;
	if (keycode == KEY_W)
		data->keys->key_w = 0;
	return (0);
}

t_img	init_img(t_data *data, char *file)
{
	t_img	tmp;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_free_parse(data->p, "Non existing file", data->p->map_y - 1);
	close (fd);
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