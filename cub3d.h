/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 10:13:45 by novan-ve       #+#    #+#                */
/*   Updated: 2020/01/30 13:28:41 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define KEY_ESC 53
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126

# include "get_next_line/get_next_line.h"
# include "printf/ft_printf.h"
# include "mlx/mlx.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>

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
	char			*file;
	unsigned long	floor;
	unsigned long	ceiling;
	int				map_x;
	int				map_y;
	int				**map;
	int				check;
}					t_parse;

typedef struct		s_run
{
	double			dirX;
	double			dirY;
	double			posX;
	double			posY;
	double			planeX;
	double			planeY;
	void			*mlx;
	void			*win;
}					t_run;

typedef struct		s_img
{
	void			*img;
	int				bits_per_pixel;
	int				line_size;
	int				endian;
	char			*addr;
}					t_img;

typedef struct		s_keys
{
	int				key_up;
	int				key_down;
	int				key_left;
	int				key_right;
}					t_keys;


typedef struct		s_data
{
	t_parse			*p;
	t_run			*run;
	t_img			*img;
	t_keys			*keys;
}					t_data;

int					ft_exit(char *s);
void				ft_map_init(t_parse *p);
int					ft_run_game(t_data *data);

int					ft_loop(t_data *data);

t_parse				ft_parse(char *file);
void				ft_init_parse(t_parse *p);
void				ft_read(t_parse *p);
void				ft_free_parse(t_parse *p, char *s, int y);

void				ft_fill_r(t_parse *p);
void				ft_fill_path(t_parse *p);
void				ft_fill_color(t_parse *p);

#endif
