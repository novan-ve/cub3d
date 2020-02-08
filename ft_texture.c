/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_texture.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/08 16:47:32 by novan-ve       #+#    #+#                */
/*   Updated: 2020/02/08 17:11:10 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_tex_set(t_ray *r, t_data *d)
{
	if (r->side == 0)
	{
		r->twidth = d->e->texwidth;
		r->theight = d->e->texheight;
	}
	if (r->side == 1)
	{
		r->twidth = d->w->texwidth;
		r->theight = d->w->texheight;
	}
	if (r->side == 2)
	{
		r->twidth = d->n->texwidth;
		r->theight = d->n->texheight;
	}
	if (r->side == 3)
	{
		r->twidth = d->s->texwidth;
		r->theight = d->s->texheight;
	}
	r->tx = (int)(r->wallx * (double)r->twidth);
	if ((r->side == 0 || r->side == 1) && r->rdx > 0)
		r->tx = r->twidth - r->tx - 1;
	if ((r->side == 2 || r->side == 3) && r->rdy < 0)
		r->tx = r->twidth - r->tx - 1;
}

void	ft_tex_put(t_ray *r, t_data *d, t_img *i, int x)
{
	r->ty = (int)r->tpos & (r->theight - 1);
	r->tpos += r->step;
	if (r->side == 0)
	{
		r->tmp = r->ty * d->e->ls + r->tx * (d->e->bpp / 8);
		r->c = *(unsigned int*)(d->e->addr + r->tmp);
	}
	if (r->side == 1)
	{
		r->tmp = r->ty * d->w->ls + r->tx * (d->w->bpp / 8);
		r->c = *(unsigned int*)(d->w->addr + r->tmp);
	}
	if (r->side == 2)
	{
		r->tmp = r->ty * d->n->ls + r->tx * (d->n->bpp / 8);
		r->c = *(unsigned int*)(d->n->addr + r->tmp);
	}
	if (r->side == 3)
	{
		r->tmp = r->ty * d->s->ls + r->tx * (d->s->bpp / 8);
		r->c = *(unsigned int*)(d->s->addr + r->tmp);
	}
	r->dst = i->addr + (r->y * i->ls + x * (i->bpp / 8));
	*(unsigned int*)(r->dst) = r->c;
}

void	ft_texture(t_ray *r, t_data *d, t_img *i, int x)
{
	r->y = 0;
	ft_tex_set(r, d);
	r->step = 1.0 * r->theight / r->lheight;
	r->tpos = (r->draws - d->p->height / 2 + r->lheight / 2) * r->step;
	while (r->y < r->draws)
	{
		my_mlx_pixel_put(i, x, r->y, d->p->ceiling);
		r->y++;
	}
	while (r->y < r->drawe)
	{
		ft_tex_put(r, d, i, x);
		r->y++;
	}
	while (r->y < d->p->height)
	{
		my_mlx_pixel_put(i, x, r->y, d->p->floor);
		r->y++;
	}
}
