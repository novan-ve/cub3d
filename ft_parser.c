/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_parser.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 11:17:26 by novan-ve       #+#    #+#                */
/*   Updated: 2020/02/08 12:31:39 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_file_check(t_parse *p, char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_free_parse(p, "Non existing file", p->map_y - 1);
	close(fd);
}

void	ft_val_check(t_parse *p)
{
	if (p->width == 0 || p->height == 0)
		ft_free_parse(p, "Wrong resolution", p->map_y - 1);
	if (p->orient == 0)
		ft_free_parse(p, "Missing orientation", p->map_y - 1);
	if (p->posx == 0 || p->posy == 0)
		ft_free_parse(p, "Missing player letter", p->map_y - 1);
	if (!p->no || !p->so || !p->we || !p->ea || !p->sprite)
		ft_free_parse(p, "Missing path", p->map_y - 1);
	if (p->floor < 0 || p->ceiling < 0)
		ft_free_parse(p, "Wrong colors for ceiling/floor", p->map_y - 1);
	if (!p->map)
		ft_free_parse(p, "Missing map", 0);
	if (p->width > 2560)
		p->width = 2560;
	if (p->height > 1440)
		p->height = 1440;
	ft_file_check(p, p->no);
	ft_file_check(p, p->so);
	ft_file_check(p, p->we);
	ft_file_check(p, p->ea);
	ft_file_check(p, p->sprite);
}

void	ft_read(t_parse *p)
{
	while (p->check > 0)
	{
		p->check = get_next_line(p->fd, &p->line);
		if (p->line[0] == 'R' && p->width == 0 && p->height == 0)
			ft_fill_r(p);
		else if (p->line[0] == 'N' && p->line[1] == 'O' && p->no == NULL)
			ft_fill_path(p);
		else if (p->line[0] == 'S' && p->line[1] == 'O' && p->so == NULL)
			ft_fill_path(p);
		else if (p->line[0] == 'E' && p->line[1] == 'A' && p->ea == NULL)
			ft_fill_path(p);
		else if (p->line[0] == 'W' && p->line[1] == 'E' && p->we == NULL)
			ft_fill_path(p);
		else if (p->line[0] == 'S' && p->line[1] == ' ' && p->sprite == NULL)
			ft_fill_path(p);
		else if (p->line[0] == 'C' && p->ceiling == 0)
			ft_fill_color(p);
		else if (p->line[0] == 'F' && p->floor == 0)
			ft_fill_color(p);
		else if (p->line[0] == '1')
			p->map_y++;
		else if (p->line[0] != '\0')
			ft_free_parse(p, "Wrong format in map", 0);
		free(p->line);
	}
}

void	ft_init_parse(t_parse *p, char *file)
{
	if (file[ft_strlen(file) - 1] != 'b' || file[ft_strlen(file) - 2] != 'u')
		ft_exit("Not a cub format");
	if (file[ft_strlen(file) - 3] != 'c' || file[ft_strlen(file) - 4] != '.')
		ft_exit("Not a cub format");
	p->width = 0;
	p->height = 0;
	p->orient = 0;
	p->line = NULL;
	p->no = NULL;
	p->ea = NULL;
	p->so = NULL;
	p->we = NULL;
	p->sprite = NULL;
	p->ceiling = 0;
	p->floor = 0;
	p->map_x = 0;
	p->map_y = 0;
	p->map = NULL;
	p->posx = 0;
	p->posy = 0;
	p->orient = 0;
	p->check = 1;
	p->isprite = 0;
	p->save = 0;
}

t_parse	ft_parse(char *file)
{
	t_parse	p;

	ft_init_parse(&p, file);
	p.fd = open(file, O_RDONLY);
	if (p.fd == -1)
		ft_free_parse(&p, "Failed to open file", 0);
	ft_read(&p);
	close(p.fd);
	p.fd = open(file, O_RDONLY);
	if (p.fd == -1)
		ft_free_parse(&p, "Failed to open file second time", 0);
	ft_map_init(&p);
	close(p.fd);
	p.fd = open(file, O_RDONLY);
	if (p.fd == -1)
		ft_free_parse(&p, "Failed to open file third time", p.map_y - 1);
	if (p.isprite > 0)
		ft_sprite_init(&p);
	close(p.fd);
	ft_val_check(&p);
	return (p);
}
