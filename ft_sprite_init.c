/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sprite_init.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 11:17:26 by novan-ve       #+#    #+#                */
/*   Updated: 2020/02/08 14:21:43 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_sprite_sort2(t_data *data, double *spritedistance)
{
	int		j;
	double	tmp;
	int		tmpi;

	j = 0;
	tmp = 0.0;
	tmpi = 0;
	while (j < data->p->isprite)
	{
		if (spritedistance[j] > tmp)
		{
			tmp = spritedistance[j];
			tmpi = j;
		}
		j++;
	}
	return (tmpi);
}

void	ft_sprite_sort(t_data *data)
{
	double		spritedistance[data->p->isprite];
	int			copy[data->p->isprite][2];
	int			i;
	int			tmpi;

	i = 0;
	while (i < data->p->isprite)
	{
		tmpi = data->p->spmap[i][1];
		spritedistance[i] = (data->r->posx - tmpi) * (data->r->posx - tmpi);
		tmpi = data->p->spmap[i][0];
		spritedistance[i] += (data->r->posy - tmpi) * (data->r->posy - tmpi);
		copy[i][0] = data->p->spmap[i][0];
		copy[i][1] = data->p->spmap[i][1];
		i++;
	}
	i = 0;
	while (i < data->p->isprite)
	{
		tmpi = ft_sprite_sort2(data, spritedistance);
		data->p->spmap[i][0] = copy[tmpi][0];
		data->p->spmap[i][1] = copy[tmpi][1];
		spritedistance[tmpi] = 0;
		i++;
	}
}

int		ft_sprite_init2(t_parse *p, char *line, int y, int i)
{
	int		x;

	x = 0;
	while (x < ft_xlen(line))
	{
		if (p->map[y][x] == 2)
		{
			p->spmap[i] = (int*)malloc(sizeof(int) * 2);
			if (!p->spmap[i])
				ft_free_sprite(p, "Spmap[i] malloc fail", i);
			p->spmap[i][0] = y;
			p->spmap[i][1] = x;
			i++;
		}
		x++;
	}
	return (i);
}

void	ft_sprite_init(t_parse *p)
{
	int		y;
	int		i;
	int		check;
	char	*line;

	y = 0;
	i = 0;
	check = 1;
	p->spmap = (int**)malloc(sizeof(int*) * p->isprite);
	if (!p->spmap)
		ft_free_parse(p, "Sprite malloc fail", p->map_y - 1);
	while (check > 0)
	{
		check = get_next_line(p->fd, &line);
		if (line[0] == '1' && i < p->isprite)
		{
			i = ft_sprite_init2(p, line, y, i);
			y++;
		}
		free(line);
	}
}
