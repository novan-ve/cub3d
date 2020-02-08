/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bmp.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/08 14:39:06 by novan-ve       #+#    #+#                */
/*   Updated: 2020/02/08 14:59:52 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_close_bmp(t_data *data, int file)
{
	close(file);
	ft_free_img2(data, "Error writing screenshot");
}

void	ft_bmp_header(t_data *data, int file, int filesize)
{
	unsigned char	fileheader[54];
	int				j;
	int				check;

	j = 0;
	while (j < 54)
	{
		fileheader[j] = (unsigned char)(0);
		j++;
	}
	fileheader[0] = (unsigned char)('B');
	fileheader[1] = (unsigned char)('M');
	ft_int_to_char(fileheader + 2, filesize);
	fileheader[10] = (unsigned char)(54);
	fileheader[14] = (unsigned char)(40);
	ft_int_to_char(fileheader + 18, data->p->width);
	ft_int_to_char(fileheader + 22, data->p->height);
	fileheader[26] = (unsigned char)(1);
	fileheader[28] = (unsigned char)(24);
	check = write(file, fileheader, 54);
	if (check == -1)
	{
		close(file);
		ft_free_img2(data, "Error writing screenshot header");
	}
}

void	ft_bmp_fill(t_data *data, t_img *i, int file, int padsize)
{
	unsigned char		zero[3];
	int					y;
	int					x;
	unsigned int		color;
	int					rgb;

	y = data->p->height - 1;
	zero[0] = 0;
	zero[1] = 0;
	zero[2] = 0;
	while (y >= 0)
	{
		x = 0;
		while (x < data->p->width)
		{
			color = *(unsigned int*)(i->addr + (y * i->ls + x * (i->bpp / 8)));
			rgb = (color & 0xFF0000) | (color & 0x00FF00) | (color & 0x0000FF);
			if (write(file, &rgb, 3) < 0)
				ft_close_bmp(data, file);
			if (padsize > 0 && write(file, &zero, padsize) < 0)
				ft_close_bmp(data, file);
			x++;
		}
		y--;
	}
}

void	ft_bmp(t_data *data, t_img *i)
{
	int		file;
	int		padsize;
	int		fsize;
	int		check;

	file = open("screenshot.bmp", O_WRONLY | O_CREAT, 0644);
	if (file < 0)
		ft_free_img2(data, "Error creating screenshot file");
	check = 0;
	padsize = (4 - ((int)data->p->width * 3) % 4) % 4;
	fsize = 54 + (3 * ((int)data->p->width + padsize) * (int)data->p->height);
	ft_bmp_header(data, file, fsize);
	ft_bmp_fill(data, i, file, padsize);
	close(file);
	mlx_destroy_image(data->r->mlx, i->img);
	ft_free_img(data);
}
