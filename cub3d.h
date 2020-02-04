/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 10:13:45 by novan-ve       #+#    #+#                */
/*   Updated: 2020/02/04 12:34:06 by anon          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define KEY_ESC 0xff1b
# define KEY_LEFT 0xff51
# define KEY_RIGHT 0xff53
# define KEY_A 0x61
# define KEY_S 0x73
# define KEY_D 0x64
# define KEY_W 0x77

# include "get_next_line/get_next_line.h"
# include "printf/ft_printf.h"
# include <mlx.h>
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
	int				isprite;
	int				**spmap;
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
	int				texWidth;
	int				texHeight;
}					t_img;

typedef struct		s_keys
{
	int				key_left;
	int				key_right;
	int				key_a;
	int				key_s;
	int				key_d;
	int				key_w;
}					t_keys;


typedef struct		s_data
{
	t_parse			*p;
	t_run			*run;
	t_img			*img;
	t_keys			*keys;
	t_img			*n;
	t_img			*s;
	t_img			*w;
	t_img			*e;
	t_img			*sp;
}					t_data;

int					ft_exit(char *s);
void				ft_map_init(t_parse *p);
int					ft_run_game(t_data *data);

int					ft_loop(t_data *data);

t_parse				ft_parse(char *file);
void				ft_init_parse(t_parse *p);
void				ft_read(t_parse *p);
void				ft_free_parse(t_parse *p, char *s, int y);

void				ft_sprite_init(t_parse *p);
void				ft_free_sprite(t_parse *p, char *s, int i);

void				ft_fill_r(t_parse *p);
void				ft_fill_path(t_parse *p);
void				ft_fill_color(t_parse *p);

#endif
