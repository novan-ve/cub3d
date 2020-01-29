/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_raycast.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/29 14:53:17 by novan-ve       #+#    #+#                */
/*   Updated: 2020/01/29 18:17:16 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_size + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int		ft_loop(t_data *data)
{
	t_img		img;

	img.img = mlx_new_image(data->run->mlx, data->p->width, data->p->height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_size, &img.endian);
	int			x = 0;
	printf("Test\n");
	while (x < data->p->width)
	{
		double	cameraX = x * 2 / (double)data->p->width - 1;
		double	rayDirX = data->run->dirX + data->run->planeX * cameraX;
		double	rayDirY = data->run->dirY + data->run->planeY * cameraX;
		int		mapX = (int)data->run->posX;
		int		mapY = (int)data->run->posY;
		double	sideDistX;
		double	sideDistY;
		double	deltaDistX = fabs(1 / rayDirX);
		double	deltaDistY = fabs(1 / rayDirY);
		double	perpWallDist;
		int		stepX;
		int		stepY;
		int		hit = 0;
		int		side;
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (data->run->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - data->run->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (data->run->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - data->run->posY) * deltaDistY;
		}
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (data->p->map[mapY][mapX] > 0)
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (mapX - data->run->posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - data->run->posY + (1 - stepY) / 2) / rayDirY;
		int lineHeight = (int)(data->p->height / perpWallDist);
		int	drawStart = -lineHeight / 2 + data->p->height / 2;
		if (drawStart < 0)
			drawStart = 0;
		int	drawEnd = lineHeight / 2 + data->p->height / 2;
		if (drawEnd >= data->p->height)
			drawEnd = data->p->height - 1;
		unsigned long color = data->p->ceiling;
		if (side == 1)
			color = color / 2;
		int index = drawStart;
		while (index <= drawEnd)
		{
			my_mlx_pixel_put(&img, x, index, color);
			index++;
		}
		x++;
	}
	mlx_put_image_to_window(data->run->mlx, data->run->win, img.img, 0, 0);
	return (0);
}