/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 10:13:45 by novan-ve       #+#    #+#                */
/*   Updated: 2020/01/27 16:43:19 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line/get_next_line.h"
# include "printf/ft_printf.h"
# include "mlx/mlx.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct		s_parse
{
	int				width;
	int				height;
	int				fd;
	int				orient;
	int				posx;
	int				posy;
	char			*line;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*sprite;
	unsigned long	floor;
	unsigned long	ceiling;
	int				map_x;
	int				map_y;
	int				**map;
	int				check;
}					t_parse;

typedef struct		s_data
{
	t_parse			*parse;
}					t_data;

int					ft_exit(char *s);

t_parse				ft_parse(char *file);
void				ft_init_parse(t_parse *p);
void				ft_read(t_parse *p);
void				ft_free_parse(t_parse *p, char *s, int y);

void				ft_fill_r(t_parse *p);
void				ft_fill_path(t_parse *p);
void				ft_fill_color(t_parse *p);

void				ft_map_init(t_parse *p);

#endif
