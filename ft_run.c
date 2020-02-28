/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_run.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/08 12:27:14 by novan-ve       #+#    #+#                */
/*   Updated: 2020/02/10 13:54:36 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_key_press(int keycode, t_data *d)
{
	if (keycode == KEY_ESC)
		ft_free_img(d, 0);
	if (keycode == KEY_RIGHT)
		d->keys->key_right = 1;
	if (keycode == KEY_LEFT)
		d->keys->key_left = 1;
	if (keycode == KEY_A)
		d->keys->key_a = 1;
	if (keycode == KEY_S)
		d->keys->key_s = 1;
	if (keycode == KEY_D)
		d->keys->key_d = 1;
	if (keycode == KEY_W)
		d->keys->key_w = 1;
	return (0);
}

int		ft_key_release(int keycode, t_data *d)
{
	if (keycode == KEY_RIGHT)
		d->keys->key_right = 0;
	if (keycode == KEY_LEFT)
		d->keys->key_left = 0;
	if (keycode == KEY_A)
		d->keys->key_a = 0;
	if (keycode == KEY_S)
		d->keys->key_s = 0;
	if (keycode == KEY_D)
		d->keys->key_d = 0;
	if (keycode == KEY_W)
		d->keys->key_w = 0;
	return (0);
}

t_img	ft_init_img(t_data *d, char *file)
{
	t_img	t;

	t.img = mlx_xpm_file_to_image(d->r->mlx, file, &t.texwidth, &t.texheight);
	t.addr = mlx_get_data_addr(t.img, &t.bpp, &t.ls, &t.end);
	return (t);
}

int		ft_run_game(t_data *d)
{
	t_img	n;
	t_img	s;
	t_img	e;
	t_img	w;
	t_img	sp;

	d->r->mlx = mlx_init();
	n = ft_init_img(d, d->p->no);
	d->n = &n;
	s = ft_init_img(d, d->p->so);
	d->s = &s;
	w = ft_init_img(d, d->p->we);
	d->w = &w;
	e = ft_init_img(d, d->p->ea);
	d->e = &e;
	sp = ft_init_img(d, d->p->sprite);
	d->sp = &sp;
	d->r->win = mlx_new_window(d->r->mlx, d->p->width, d->p->height, "CUB3D");
	ft_raycast(d);
	mlx_hook(d->r->win, 2, 1L << 0, ft_key_press, d);
	mlx_hook(d->r->win, 3, 1L << 1, ft_key_release, d);
	mlx_hook(d->r->win, 17, 0L, ft_free_img, d);
	mlx_loop_hook(d->r->mlx, &ft_key_search, d);
	mlx_loop(d->r->mlx);
	return (0);
}
