/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_raycast.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/29 14:53:17 by novan-ve       #+#    #+#                */
/*   Updated: 2020/02/08 16:52:52 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_raycast_set2(t_ray *r, t_data *data)
{
	if (r->side == 0 || r->side == 1)
		r->perp = (r->mapx - data->r->posx + (1 - r->stepx) / 2) / r->rdx;
	else if (r->side == 2 || r->side == 3)
		r->perp = (r->mapy - data->r->posy + (1 - r->stepy) / 2) / r->rdy;
	r->lheight = (int)(data->p->height / r->perp);
	r->draws = -r->lheight / 2 + data->p->height / 2;
	if (r->draws < 0)
		r->draws = 0;
	r->drawe = r->lheight / 2 + data->p->height / 2;
	if (r->drawe >= data->p->height)
		r->drawe = data->p->height - 1;
	r->wallx = 0;
	if (r->side == 0 || r->side == 1)
		r->wallx = data->r->posy + r->perp * r->rdy;
	else if (r->side == 2 || r->side == 3)
		r->wallx = data->r->posx + r->perp * r->rdx;
	r->wallx -= floor((r->wallx));
}

void	ft_raycast_set(t_ray *r, t_data *data, int x)
{
	r->cam = 2 * x / (double)data->p->width - 1;
	r->rdx = data->r->dirx + data->r->planex * r->cam;
	r->rdy = data->r->diry + data->r->planey * r->cam;
	r->mapx = (int)data->r->posx;
	r->mapy = (int)data->r->posy;
	r->ddx = fabs(1 / r->rdx);
	r->ddy = fabs(1 / r->rdy);
	r->perp = 0;
	r->hit = 0;
	r->stepx = (r->rdx < 0) ? -1 : 1;
	r->stepy = (r->rdy < 0) ? -1 : 1;
	if (r->rdx < 0)
		r->sdx = (data->r->posx - r->mapx) * r->ddx;
	else
		r->sdx = (r->mapx + 1.0 - data->r->posx) * r->ddx;
	if (r->rdy < 0)
		r->sdy = (data->r->posy - r->mapy) * r->ddy;
	else
		r->sdy = (r->mapy + 1.0 - data->r->posy) * r->ddy;
}

void	ft_raycast_hit(t_ray *r, t_data *data)
{
	while (r->hit == 0)
	{
		if (r->sdx < r->sdy)
		{
			if (r->stepx < 0)
				r->side = 1;
			else
				r->side = 0;
			r->sdx += r->ddx;
			r->mapx += r->stepx;
		}
		else
		{
			if (r->stepy < 0)
				r->side = 2;
			else
				r->side = 3;
			r->sdy += r->ddy;
			r->mapy += r->stepy;
		}
		if (data->p->map[r->mapy][r->mapx] == 1)
			r->hit = 1;
	}
}

int		ft_raycast(t_data *data)
{
	double		zbuffer[data->p->width];
	t_img		i;
	t_ray		r;
	int			x;

	i.img = mlx_new_image(data->r->mlx, data->p->width, data->p->height);
	i.addr = mlx_get_data_addr(i.img, &i.bpp, &i.ls, &i.end);
	x = 0;
	while (x < data->p->width)
	{
		ft_raycast_set(&r, data, x);
		ft_raycast_hit(&r, data);
		ft_raycast_set2(&r, data);
		ft_texture(&r, data, &i, x);
		zbuffer[x] = r.perp;
		x++;
	}
	ft_sprite(data, &i, zbuffer);
	if (data->p->save == 0)
		mlx_put_image_to_window(data->r->mlx, data->r->win, i.img, 0, 0);
	if (data->p->save == 1)
		ft_bmp(data, &i);
	mlx_destroy_image(data->r->mlx, i.img);
	return (0);
}
