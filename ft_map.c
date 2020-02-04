/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_map.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 13:23:24 by novan-ve       #+#    #+#                */
/*   Updated: 2020/02/04 10:46:17 by anon          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_map_x(t_parse *p)
{
	int		i;

	i = 0;
	while (p->line[i] != '\0')
	{
		if (p->line[i] == '1')
			p->map_x++;
		i++;
	}
}

int		ft_map_init3(t_parse *p, int x, int y, int i)
{
	char	a;

	a = p->line[i];
	if (a == '0' || a == '1' || a == '2')
	{
		if (a != '1' && (y == 0 || y == p->map_y - 1))
			ft_free_parse(p, "Encountered hole in outer walls", y);
		if (a != '1' && (x == p->map_x || x == 0))
			ft_free_parse(p, "Encountered hole in outer walls", y);
		if (a == '2')
			p->isprite++;
		p->map[y][x] = p->line[i] - 48;
		x++;
	}
	else if (a == 'N' || a == 'S' || a == 'W' || a == 'E')
	{
		if (p->orient != 0 || y == 0 || y == p->map_y - 1)
			ft_free_parse(p, "Multiple letters in map", y);
		p->orient = a;
		p->map[y][x] = 0;
		p->posx = x;
		p->posy = y;
		x++;
	}
	else if (a != ' ')
		ft_free_parse(p, "Wrong character in map", y);
	return (x);
}

int		ft_map_init2(t_parse *p, int y)
{
	int		i;
	int		x;

	i = 0;
	x = 0;
	if (p->map_x == 0)
		ft_map_x(p);
	p->map[y] = malloc(sizeof(int) * p->map_x);
	while (p->line[i] != '\0')
	{
		if (x > p->map_x)
			ft_free_parse(p, "Uneven map", y);
		x = ft_map_init3(p, x, y, i);
		i++;
	}
	if (x != p->map_x)
		ft_free_parse(p, "Uneven map", y);
	y++;
	return (y);
}

void	ft_map_init(t_parse *p)
{
	int		y;
	int		check;

	y = 0;
	check = 1;
	if (p->map_y == 0)
		ft_free_parse(p, "Wrong map format", y);
	p->map = malloc(sizeof(int*) * p->map_y);
	while (check > 0)
	{
		check = get_next_line(p->fd, &p->line);
		if (p->line[0] == '1' && y < p->map_y)
			y = ft_map_init2(p, y);
		if (y > 0 && y < p->map_y && p->line[0] != '1')
			ft_free_parse(p, "Multiple maps", y - 1);
		free(p->line);
	}
}
