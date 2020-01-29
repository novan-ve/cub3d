/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_run.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/29 12:50:42 by novan-ve       #+#    #+#                */
/*   Updated: 2020/01/29 18:34:03 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_set_keys(int keycode, t_data *data)
{
	if (keycode == 53)
		ft_exit("Escape pressed");
	if (keycode == 126)
	{
		printf("Entered key_up\n");
		if (data->p->map[(int)(data->run->posY)][(int)(data->run->posX + data->run->dirX * 0.1)] == 0)
			data->run->posX += data->run->dirX * 0.1;
		if (data->p->map[(int)(data->run->posY + data->run->dirY * 0.1)][(int)(data->run->posX)] == 0)
			data->run->posY += data->run->dirY * 0.1;
		printf("Entered key_up\n");
		ft_loop(data);
	}
	return (0);
}

int		ft_run_game(t_data *data)
{
	data->run->mlx = mlx_init();
	data->run->win = mlx_new_window(data->run->mlx, data->p->width, data->p->height, "cub3d");
	mlx_hook(data->run->win, 2, 1L<<0, ft_set_keys, data);
	ft_loop(data);
	mlx_hook(data->run->win, 17, 0, ft_exit, "Window closed");
	mlx_loop(data->run->mlx);
	return (0);
}
