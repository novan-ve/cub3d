/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_run.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/29 12:50:42 by novan-ve       #+#    #+#                */
/*   Updated: 2020/01/30 17:52:48 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_key_search(t_data *data)
{
	if (data->keys->key_up == 1 || data->keys->key_down == 1 || data->keys->key_right == 1 || data->keys->key_left == 1)
	{
		if (data->keys->key_up == 1)
		{
			printf("Entered key_up\n");
			if (data->p->map[(int)(data->run->posY)][(int)(data->run->posX + data->run->dirX * 0.1)] == 0 && data->p->map[(int)(data->run->posY + data->run->dirY * 0.1)][(int)(data->run->posX)] == 0)
			{
				data->run->posX += data->run->dirX * 0.1;
				data->run->posY += data->run->dirY * 0.1;
			}
		}
		if (data->keys->key_down == 1)
		{
			printf("Entered key_down\n");
			if (data->p->map[(int)(data->run->posY)][(int)(data->run->posX - data->run->dirX * 0.1)] == 0)
				data->run->posX -= data->run->dirX * 0.1;
			if (data->p->map[(int)(data->run->posY - data->run->dirY * 0.1)][(int)(data->run->posX)] == 0)
				data->run->posY -= data->run->dirY * 0.1;
		}
		if (data->keys->key_right == 1)
		{
			printf("Entered key_right\n");
			double oldDirX = data->run->dirX;
			data->run->dirX = data->run->dirX * cos(-0.033) - data->run->dirY * sin(-0.033);
			data->run->dirY = oldDirX * sin(-0.033) + data->run->dirY * cos(-0.033);
			double oldPlaneX = data->run->planeX;
			data->run->planeX = data->run->planeX * cos(-0.033) - data->run->planeY * sin(-0.033);
			data->run->planeY = oldPlaneX * sin(-0.033) + data->run->planeY * cos(-0.033);
		}
		if (data->keys->key_left == 1)
		{
			printf("Entered key_left\n");
			double oldDirX = data->run->dirX;
			data->run->dirX = data->run->dirX * cos(0.033) - data->run->dirY * sin(0.033);
			data->run->dirY = oldDirX * sin(0.033) + data->run->dirY * cos(0.033);
			double oldPlaneX = data->run->planeX;
			data->run->planeX = data->run->planeX * cos(0.033) - data->run->planeY * sin(0.033);
			data->run->planeY = oldPlaneX * sin(0.033) + data->run->planeY * cos(0.033);
		}
		ft_loop(data);
	}
	return (0);
}

int		ft_key_press(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		ft_exit("Escape pressed");
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

int		ft_run_game(t_data *data)
{
	data->run->mlx = mlx_init();
	data->run->win = mlx_new_window(data->run->mlx, data->p->width, data->p->height, "cub3d");
	ft_loop(data);
	//mlx_do_key_autorepeatoff(data->run->mlx);
	mlx_hook(data->run->win, 2, 1L<<0, ft_key_press, data);
	mlx_hook(data->run->win, 3, 1L<<0, ft_key_release, data);
	mlx_hook(data->run->win, 17, 0, ft_exit, "Window closed");
	mlx_loop_hook(data->run->mlx, &ft_key_search, data);
	mlx_loop(data->run->mlx);
	return (0);
}
