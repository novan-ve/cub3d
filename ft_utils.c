/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_utils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/08 12:52:30 by novan-ve       #+#    #+#                */
/*   Updated: 2020/02/08 15:00:25 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_xlen(char *s)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '0' || s[i] == '1' || s[i] == '2')
			len++;
		if (s[i] == 'N' || s[i] == 'E' || s[i] == 'W' || s[i] == 'S')
			len++;
		i++;
	}
	return (len);
}

void	ft_int_to_char(unsigned char *str, int x)
{
	str[0] = (unsigned char)(x);
	str[1] = (unsigned char)(x >> 8);
	str[2] = (unsigned char)(x >> 16);
	str[3] = (unsigned char)(x >> 24);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->ls + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}
