/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sprite.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/08 15:06:50 by novan-ve       #+#    #+#                */
/*   Updated: 2020/02/08 15:59:40 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_sprite_set(t_data *data, t_sprite *s, int j)
{
	double		tmp;

	tmp = (data->r->planex * data->r->diry - data->r->dirx * data->r->planey);
	s->sx = data->p->spmap[j][1] - data->r->posx + 0.5;
	s->sy = data->p->spmap[j][0] - data->r->posy + 0.5;
	s->invdet = 1.0 / tmp;
	s->trx = s->invdet * (data->r->diry * s->sx - data->r->dirx * s->sy);
	s->try = s->invdet * (-(data->r->planey) * s->sx + data->r->planex * s->sy);
	s->screen = (int)((data->p->width / 2) * (1 + s->trx / s->try));
	s->height = abs((int)(data->p->height / (s->try)));
	s->drawsy = -s->height / 2 + data->p->height / 2;
	if (s->drawsy < 0)
		s->drawsy = 0;
	s->drawey = s->height / 2 + data->p->height / 2;
	if (s->drawey >= data->p->height)
		s->drawey = data->p->height - 1;
	s->width = abs((int)(data->p->height / (s->try)));
	s->drawsx = -s->width / 2 + s->screen;
	if (s->drawsx < 0)
		s->drawsx = 0;
	s->drawex = s->width / 2 + s->screen;
	if (s->drawex >= data->p->width)
		s->drawex = data->p->width - 1;
	s->stripe = s->drawsx;
}

void	ft_sprite_loop(t_data *data, t_img *i, t_sprite *s, int texx)
{
	int				d;
	unsigned int	c;
	char			*dst;
	int				texy;
	int				tmp;

	s->y = s->drawsy;
	while (s->y < s->drawey)
	{
		d = (s->y) * 256 - data->p->height * 128 + s->height * 128;
		texy = ((d * data->sp->texheight) / s->height) / 256;
		tmp = texy * data->sp->ls + texx * (data->sp->bpp / 8);
		c = *(unsigned int*)(data->sp->addr + tmp);
		if (c != 0xFF000000)
		{
			dst = i->addr + (s->y * i->ls + s->stripe * (i->bpp / 8));
			*(unsigned int*)dst = c;
		}
		s->y++;
	}
}

void	ft_sprite(t_data *data, t_img *i, double *z)
{
	int			j;
	t_sprite	s;
	int			texx;
	double		tmp;

	j = 0;
	(void)i;
	ft_sprite_sort(data);
	while (j < data->p->isprite)
	{
		ft_sprite_set(data, &s, j);
		while (s.stripe < s.drawex)
		{
			tmp = 256.0 * (s.stripe - (-s.width / 2 + s.screen));
			texx = (int)(tmp * data->sp->texwidth / s.width) / 256;
			if (s.try > 0 && s.stripe > 0 && s.stripe < data->p->width)
				if (s.try < z[s.stripe])
					ft_sprite_loop(data, i, &s, texx);
			s.stripe++;
		}
		j++;
	}
}
