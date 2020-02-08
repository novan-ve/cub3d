/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_move.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/08 13:57:33 by novan-ve       #+#    #+#                */
/*   Updated: 2020/02/08 14:31:48 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_move3(t_data *d)
{
	double	old_dir_x;
	double	old_plane_x;

	if (d->keys->key_left == 1)
	{
		old_dir_x = d->r->dirx;
		d->r->dirx = d->r->dirx * cos(-0.03) - d->r->diry * sin(-0.03);
		d->r->diry = old_dir_x * sin(-0.03) + d->r->diry * cos(-0.03);
		old_plane_x = d->r->planex;
		d->r->planex = d->r->planex * cos(-0.03) - d->r->planey * sin(-0.03);
		d->r->planey = old_plane_x * sin(-0.03) + d->r->planey * cos(-0.03);
	}
	if (d->keys->key_right == 1)
	{
		old_dir_x = d->r->dirx;
		d->r->dirx = d->r->dirx * cos(0.03) - d->r->diry * sin(0.03);
		d->r->diry = old_dir_x * sin(0.03) + d->r->diry * cos(0.03);
		old_plane_x = d->r->planex;
		d->r->planex = d->r->planex * cos(0.03) - d->r->planey * sin(0.03);
		d->r->planey = old_plane_x * sin(0.03) + d->r->planey * cos(0.03);
	}
}

void	ft_move2(t_data *d)
{
	double		tmp;

	if (d->keys->key_d == 1)
	{
		tmp = d->r->posx - d->r->diry * (0.1);
		if (d->p->map[(int)(d->r->posy)][(int)(tmp)] == 0)
			d->r->posx -= d->r->diry * (0.09);
		tmp = d->r->posy - d->r->dirx * -(0.1);
		if (d->p->map[(int)(tmp)][(int)(d->r->posx)] == 0)
			d->r->posy -= d->r->dirx * -(0.09);
	}
	if (d->keys->key_a == 1)
	{
		tmp = d->r->posx + d->r->diry * (0.1);
		if (d->p->map[(int)(d->r->posy)][(int)(tmp)] == 0)
			d->r->posx += d->r->diry * (0.09);
		tmp = d->r->posy + d->r->dirx * -(0.1);
		if (d->p->map[(int)(tmp)][(int)(d->r->posx)] == 0)
			d->r->posy += d->r->dirx * -(0.09);
	}
}

void	ft_move(t_data *d)
{
	double		tmp;

	if (d->keys->key_w == 1)
	{
		tmp = d->r->posx + d->r->dirx * (0.1);
		if (d->p->map[(int)(d->r->posy)][(int)(tmp)] == 0)
			d->r->posx += d->r->dirx * (0.09);
		tmp = d->r->posy + d->r->diry * (0.1);
		if (d->p->map[(int)(tmp)][(int)(d->r->posx)] == 0)
			d->r->posy += d->r->diry * (0.09);
	}
	if (d->keys->key_s == 1)
	{
		tmp = d->r->posx - d->r->dirx * (0.1);
		if (d->p->map[(int)(d->r->posy)][(int)(tmp)] == 0)
			d->r->posx -= d->r->dirx * (0.09);
		tmp = d->r->posy - d->r->diry * (0.1);
		if (d->p->map[(int)(tmp)][(int)(d->r->posx)] == 0)
			d->r->posy -= d->r->diry * (0.09);
	}
}

int		ft_key_search(t_data *d)
{
	if (!d->keys->key_w && !d->keys->key_s && !d->keys->key_left)
	{
		if (!d->keys->key_a && !d->keys->key_d && !d->keys->key_right)
			return (0);
	}
	ft_move(d);
	ft_move2(d);
	ft_move3(d);
	ft_raycast(d);
	return (0);
}
