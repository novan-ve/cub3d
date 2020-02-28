/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 10:13:45 by novan-ve       #+#    #+#                */
/*   Updated: 2020/02/10 14:16:59 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define KEY_ESC 53
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13
# define BUFFER_SIZE 1024

# include "ft_printf/ft_printf.h"
# include "mlx/mlx.h"
# include <fcntl.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <math.h>

typedef struct		s_ray
{
	double			cam;
	double			rdx;
	double			rdy;
	int				mapx;
	int				mapy;
	double			sdx;
	double			sdy;
	double			ddx;
	double			ddy;
	double			perp;
	int				stepx;
	int				stepy;
	int				hit;
	int				side;
	int				lheight;
	int				draws;
	int				drawe;
	double			wallx;
	int				twidth;
	int				theight;
	int				tx;
	int				ty;
	double			step;
	double			tpos;
	int				y;
	int				c;
	int				tmp;
	char			*dst;
}					t_ray;

typedef struct		s_sprite
{
	double			sx;
	double			sy;
	double			invdet;
	double			trx;
	double			try;
	int				screen;
	int				height;
	int				width;
	int				drawsx;
	int				drawsy;
	int				drawex;
	int				drawey;
	int				stripe;
	int				y;
}					t_sprite;

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
	int				save;
	int				*mwidth;
}					t_parse;

typedef struct		s_run
{
	double			dirx;
	double			diry;
	double			posx;
	double			posy;
	double			planex;
	double			planey;
	void			*mlx;
	void			*win;
}					t_run;

typedef struct		s_img
{
	void			*img;
	int				bpp;
	int				ls;
	int				end;
	char			*addr;
	int				texwidth;
	int				texheight;
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
	t_run			*r;
	t_img			*img;
	t_keys			*keys;
	t_img			*n;
	t_img			*s;
	t_img			*w;
	t_img			*e;
	t_img			*sp;
}					t_data;

int					ft_exit(char *s, int x);
void				ft_map_init(t_parse *p);
int					ft_run_game(t_data *data);
int					ft_free_img(t_data *data, int x);
int					ft_free_img2(t_data *data, char *s, int x);
void				ft_free_parse(t_parse *p, char *s, int y, int x);
void				ft_free_sprite(t_parse *p, char *s, int i, int x);
int					ft_raycast(t_data *data);
t_parse				ft_parse(char *file);
void				ft_init_parse(t_parse *p, char *file);
void				ft_read(t_parse *p);
int					ft_xlen(char *s);
void				ft_int_to_char(unsigned char *str, int x);
void				my_mlx_pixel_put(t_img *img, int x, int y, int color);
void				ft_sprite_init(t_parse *p);
int					ft_sprite_init2(t_parse *p, char *line, int y, int i);
void				ft_sprite_sort(t_data *data);
int					ft_sprite_sort2(t_data *data, double *spritedistance);
void				ft_fill_r(t_parse *p);
void				ft_fill_path(t_parse *p);
void				ft_fill_color(t_parse *p);
void				ft_bmp(t_data *d, t_img *img);
void				ft_move(t_data *d);
void				ft_move2(t_data *d);
void				ft_move3(t_data *d);
int					ft_key_search(t_data *d);
void				ft_sprite(t_data *data, t_img *i, double *zbuffer);
void				ft_texture(t_ray *r, t_data *d, t_img *i, int x);
void				ft_flood(t_parse *p, int x, int y);
int					get_next_line(int fd, char **line);
int					ft_cpy(char **line, char **str, int fd);
int					ft_strcheck(char *str);
char				*ft_strread(int fd, char **str, ssize_t red);
char				*ft_plusn(char *str);
size_t				ft_strlen(const char *s);
char				*ft_gstrdup(char *s1);
char				*ft_strcat2(char *origin, char *append, char *dest);
char				*ft_strcat(char *origin, char *append);
char				*ft_gsubstr(char *str);

#endif
