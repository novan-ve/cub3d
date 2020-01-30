/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_raycast.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/29 14:53:17 by novan-ve       #+#    #+#                */
/*   Updated: 2020/01/30 17:34:46 by novan-ve      ########   odam.nl         */
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

	int		texWidth;
	int		texHeight;

	t_img		png;
	t_img		img;

	img.img = mlx_new_image(data->run->mlx, data->p->width, data->p->height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_size, &img.endian);
	printf("Test1\n");
	png.img = mlx_png_file_to_image(data->run->mlx, "./texture.png", &texWidth, &texHeight);
	printf("Test2\n");
	png.addr = mlx_get_data_addr(png.img, &png.bits_per_pixel, &png.line_size, &png.endian);
	int			x = 0;
	printf("New frame\n");
	while (x < data->p->width)
	{
		double	cameraX = 2 * x / (double)data->p->width - 1;
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

		//Texture

		double	wallX;
		if (side == 0)
			wallX = data->run->posY + perpWallDist * rayDirY;
		else
			wallX = data->run->posX + perpWallDist * rayDirX;
		wallX -= floor((wallX));

		int		texX = (int)(wallX * (double)texWidth);
		if (side == 0 && rayDirX > 0)
			texX = texWidth - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = texWidth - texX - 1;

		double	step = 1.0 * texHeight / lineHeight;

		double	texPos = (drawStart - data->p->height / 2 + lineHeight / 2) * step;
		int		y = drawStart;
		//printf("Test3\n");
		while (y < drawEnd)
		{
			int	texY = (int)texPos & (texHeight - 1);
			texPos += step;

			int color = *(unsigned int*)(png.addr + (texY * png.line_size + texX * (png.bits_per_pixel / 8)));
			//if (side == 1)
			//	color = (color >> 1) & 8355711;

			char	*dst;
			dst = img.addr + (y * img.line_size + x * (img.bits_per_pixel / 8));
			*(unsigned int*)dst = color;

			y++;
		}
		//printf("Test4\n");

		//End Texture

		// int	index = 0;
		// unsigned long	color = 14753280;
		// if (side == 1)
		// 	color = 8192000;
		// while (index < data->p->height)
		// {
		// 	if (index < drawStart)
		// 		my_mlx_pixel_put(&img, x, index, data->p->ceiling);
		// 	else if (index >= drawStart && index <= drawEnd)
		// 		my_mlx_pixel_put(&img, x, index, color);
		// 	else
		// 		my_mlx_pixel_put(&img, x, index, data->p->floor);
		// 	index++;
		// }
		x++;
	}
	mlx_put_image_to_window(data->run->mlx, data->run->win, img.img, 0, 0);
	mlx_destroy_image(data->run->mlx, img.img);
	mlx_destroy_image(data->run->mlx, png.img);
	return (0);
}
