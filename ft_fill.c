/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_fill.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 12:00:36 by novan-ve       #+#    #+#                */
/*   Updated: 2020/01/27 17:20:10 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_fill_color2(t_parse *p, int r, int i)
{
	int		g;
	int		b;

	g = ft_atoi(p->line + i);
	while (p->line[i] >= '0' && p->line[i] <= '9')
		i++;
	if (p->line[i] != ',' || p->line[i + 1] < '0' || p->line[i + 1] > '9')
		ft_free_parse(p, "Wrong color format", 0);
	i++;
	b = ft_atoi(p->line + i);
	while (p->line[i] >= '0' && p->line[i] <= '9')
		i++;
	if (p->line[i] != '0' && p->line[i] != '\0')
		ft_free_parse(p, "Wrong color format", 0);
	while (p->line[i] == ' ')
		i++;
	if (p->line[i] != '\0' || r > 255 || g > 255 || b > 255)
		ft_free_parse(p, "Wrong color format", 0);
	if (p->line[0] == 'F')
		p->floor = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	else if (p->line[0] == 'C')
		p->ceiling = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

void	ft_fill_color(t_parse *p)
{
	int		i;
	int		r;

	i = 1;
	while (p->line[i] == ' ')
		i++;
	if (i == 1 || p->line[i] < '0' || p->line[i] > '9')
		ft_free_parse(p, "Wrong color format", 0);
	r = ft_atoi(p->line + i);
	while (p->line[i] >= '0' && p->line[i] <= '9')
		i++;
	if (p->line[i] != ',' || p->line[i + 1] < '0' || p->line[i + 1] > '9')
		ft_free_parse(p, "Wrong color format", 0);
	i++;
	ft_fill_color2(p, r, i);
}

void	ft_fill_path2(t_parse *p, int j)
{
	while (p->line[j] == ' ')
		j++;
	if (p->line[j] != '\0')
		ft_free_parse(p, "Multiple files declared", 0);
}

void	ft_fill_path(t_parse *p)
{
	int		i;
	int		j;

	i = (p->line[0] == 'S' && p->line[1] == ' ') ? 1 : 2;
	if (p->line[i] != ' ')
		ft_free_parse(p, "No space after format", 0);
	while (p->line[i] == ' ')
		i++;
	j = i;
	if (p->line[i] == '\0')
		ft_free_parse(p, "Missing texture", 0);
	while (p->line[j] != ' ' && p->line[j] != '\0')
		j++;
	if (p->line[0] == 'N' && p->line[1] == 'O')
		p->no = ft_substr(p->line, i, j - i);
	if (p->line[0] == 'S' && p->line[1] == 'O')
		p->so = ft_substr(p->line, i, j - i);
	if (p->line[0] == 'W' && p->line[1] == 'E')
		p->we = ft_substr(p->line, i, j - i);
	if (p->line[0] == 'E' && p->line[1] == 'A')
		p->ea = ft_substr(p->line, i, j - i);
	if (p->line[0] == 'S' && p->line[1] == ' ')
		p->sprite = ft_substr(p->line, i, j - i);
	ft_fill_path2(p, j);
}

void	ft_fill_r(t_parse *p)
{
	int		i;

	i = 1;
	while (p->line[i] == ' ')
		i++;
	if (i == 1)
		ft_free_parse(p, "Wrong R format", 0);
	while (p->line[i] >= '0' && p->line[i] <= '9')
	{
		p->width = p->width * 10 + p->line[i] - 48;
		i++;
	}
	if (p->width == 0 || p->line[i] != ' ')
		ft_free_parse(p, "Wrong R format", 0);
	while (p->line[i] == ' ')
		i++;
	while (p->line[i] >= '0' && p->line[i] <= '9')
	{
		p->height = p->height * 10 + p->line[i] - 48;
		i++;
	}
	while (p->line[i] == ' ')
		i++;
	if (p->height == 0 || p->line[i] != '\0')
		ft_free_parse(p, "Wrong R format", 0);
}
