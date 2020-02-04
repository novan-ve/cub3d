/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sprite_init.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 11:17:26 by novan-ve       #+#    #+#                */
/*   Updated: 2020/02/04 11:12:29 by anon          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void	ft_free_sprite(t_parse *p, char *s, int i)
{
	while (i >= 0)
	{
		if (p->spmap[i])
			free(p->spmap[i]);
		i--;
	}
	free (p->spmap);
	ft_free_parse(p, s, p->map_y - 1);
}

void	ft_sprite_init(t_parse *p)
{
	int		x;
	int		y;
	int		i;

	y = 0;
	i = 0;
	p->spmap = (int**)malloc(sizeof(int*) * p->isprite);
	if (!p->spmap)
		ft_free_parse(p, "Sprite malloc fail", p->map_y - 1);
	while (y < p->map_y && i < p->isprite)
	{
		x = 0;
		while (x < p->map_x)
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
		y++;
	}
}