/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/08 12:27:35 by novan-ve       #+#    #+#                */
/*   Updated: 2020/02/08 14:19:12 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_free_img(t_data *d)
{
	mlx_destroy_image(d->r->mlx, d->n->img);
	mlx_destroy_image(d->r->mlx, d->s->img);
	mlx_destroy_image(d->r->mlx, d->e->img);
	mlx_destroy_image(d->r->mlx, d->w->img);
	ft_free_sprite(d->p, "Exited cleanly", d->p->isprite - 1);
	return (0);
}

int		ft_free_img2(t_data *data, char *s)
{
	mlx_destroy_image(data->r->mlx, data->n->img);
	mlx_destroy_image(data->r->mlx, data->s->img);
	mlx_destroy_image(data->r->mlx, data->e->img);
	mlx_destroy_image(data->r->mlx, data->w->img);
	ft_free_sprite(data->p, s, data->p->isprite - 1);
	return (0);
}

void	ft_free_parse(t_parse *p, char *s, int y)
{
	if (p->no)
		free(p->no);
	if (p->so)
		free(p->so);
	if (p->ea)
		free(p->ea);
	if (p->we)
		free(p->we);
	if (p->sprite)
		free(p->sprite);
	if (p->map)
	{
		while (y >= 0)
		{
			if (p->map[y])
				free(p->map[y]);
			y--;
		}
		free(p->map);
	}
	ft_exit(s);
}

void	ft_free_sprite(t_parse *p, char *s, int i)
{
	while (i >= 0)
	{
		if (p->spmap[i])
			free(p->spmap[i]);
		i--;
	}
	free(p->spmap);
	ft_free_parse(p, s, p->map_y - 1);
}
