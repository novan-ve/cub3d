/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_map.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 13:23:24 by novan-ve       #+#    #+#                */
/*   Updated: 2020/02/08 12:56:32 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_map_init5(t_parse *p, int y, int x, int prev)
{
	if (x > prev && prev != 0)
		while (x > prev)
		{
			if (p->map[y][x - 1] != 1)
				ft_free_parse(p, "Encountered hole in outer walls", y);
			x--;
		}
	else if (x < prev && prev != 0)
		while (x < prev)
		{
			if (p->map[y - 1][x] != 1)
				ft_free_parse(p, "Encountered hole in outer walls", y);
			x++;
		}
}

int		ft_map_init4(t_parse *p, int y, int x, int i)
{
	if (p->orient != 0 || y == 0 || y == p->map_y - 1)
		ft_free_parse(p, "Multiple letters in map", y);
	if (x == ft_xlen(p->line) - 1)
		ft_free_parse(p, "Multiple letters in map", y);
	p->orient = p->line[i];
	p->map[y][x] = 0;
	p->posx = x;
	p->posy = y;
	x++;
	return (x);
}

int		ft_map_init3(t_parse *p, int y, int x, int i)
{
	if (p->line[i] != '1' && (y == 0 || y == p->map_y - 1))
		ft_free_parse(p, "Encountered hole in outer walls", y);
	if (p->line[i] != '1' && x == ft_xlen(p->line) - 1)
		ft_free_parse(p, "Encountered hole in outer walls", y);
	if (p->line[i] == '2')
		p->isprite++;
	p->map[y][x] = p->line[i] - 48;
	x++;
	return (x);
}

int		ft_map_init2(t_parse *p, int y, int prev)
{
	int		i;
	int		x;
	char	a;

	x = 0;
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
			ft_free_parse(p, "Wrong character in map", y);
		i++;
	}
	ft_map_init5(p, y, x, prev);
	y++;
	return (y);
}

void	ft_map_init(t_parse *p)
{
	int		y;
	int		ret;
	int		prev;

	y = 0;
	ret = 1;
	prev = 0;
	if (p->map_y == 0)
		ft_free_parse(p, "Wrong map format", y);
	p->map = malloc(sizeof(int*) * p->map_y);
	while (ret > 0)
	{
		ret = get_next_line(p->fd, &p->line);
		if (p->line[0] == '1' && y < p->map_y)
		{
			y = ft_map_init2(p, y, prev);
			prev = ft_xlen(p->line);
		}
		if (y > 0 && y < p->map_y && p->line[0] != '1')
			ft_free_parse(p, "Multiple maps", y - 1);
		free(p->line);
	}
}
