/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_map.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 13:23:24 by novan-ve       #+#    #+#                */
/*   Updated: 2020/02/10 14:16:25 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_map_init4(t_parse *p, int y, int x, int i)
{
	if (p->orient != 0 || y == 0 || y == p->map_y - 1)
		ft_free_parse(p, "Multiple letters in map", y, 1);
	if (x == ft_xlen(p->line) - 1)
		ft_free_parse(p, "Multiple letters in map", y, 1);
	p->orient = p->line[i];
	p->map[y][x] = 0;
	p->posx = x;
	p->posy = y;
	x++;
	return (x);
}

int		ft_map_init3(t_parse *p, int y, int x, int i)
{
	if (p->line[i] == '2')
		p->isprite++;
	p->map[y][x] = p->line[i] - 48;
	x++;
	return (x);
}

int		ft_map_init2(t_parse *p, int y)
{
	int		i;
	int		x;
	char	a;

	x = 0;
	p->mwidth[y] = ft_xlen(p->line);
	p->map[y] = malloc(sizeof(int) * ft_xlen(p->line));
	if (p->map_x < ft_xlen(p->line))
		p->map_x = ft_xlen(p->line);
	i = 0;
	while (p->line[i] != '\0')
	{
		a = p->line[i];
		if (p->line[i] == '0' || p->line[i] == '1' || p->line[i] == '2')
			x = ft_map_init3(p, y, x, i);
		else if (a == 'N' || a == 'S' || a == 'W' || a == 'E')
			x = ft_map_init4(p, y, x, i);
		else if (p->line[i] != ' ')
			ft_free_parse(p, "Wrong character in map", y, 1);
		i++;
	}
	y++;
	return (y);
}

void	ft_flood_check(t_parse *p)
{
	int		y;
	int		x;

	y = 0;
	ft_flood(p, p->posx, p->posy);
	while (y < p->map_y)
	{
		x = 0;
		while (x < p->mwidth[y])
		{
			if (p->map[y][x] == 3)
				p->map[y][x] = 0;
			x++;
		}
		y++;
	}
}

void	ft_map_init(t_parse *p)
{
	int		y;
	int		ret;

	y = 0;
	ret = 1;
	if (p->map_y == 0)
		ft_free_parse(p, "Wrong map format", y, 1);
	p->map = malloc(sizeof(int*) * p->map_y);
	if (!p->map)
		ft_free_parse(p, "Malloc fail", y - 1, 1);
	p->mwidth = malloc(sizeof(int) * p->map_y);
	if (!p->mwidth)
		ft_free_parse(p, "Malloc fail", y - 1, 1);
	while (ret > 0)
	{
		ret = get_next_line(p->fd, &p->line);
		if (p->line[0] >= '0' && p->line[0] <= '2' && y < p->map_y)
			y = ft_map_init2(p, y);
		if (y > 0 && y < p->map_y && !ft_xlen(p->line))
			ft_free_parse(p, "Multiple maps", y - 1, 1);
		free(p->line);
	}
	ft_flood_check(p);
}
