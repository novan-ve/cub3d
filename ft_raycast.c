/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_raycast.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/29 14:53:17 by novan-ve       #+#    #+#                */
/*   Updated: 2020/02/04 13:21:38 by anon          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_size + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	ft_sprite_sort(t_data *data)
{
	double spriteDistance[data->p->isprite];
	int			copy[data->p->isprite][2];
	int			i;
	int			j;
	double		tmp;
	int			tmpi;

	i = 0;
	while (i < data->p->isprite)
	{
		spriteDistance[i] = ((data->run->posX - data->p->spmap[i][1]) * (data->run->posX - data->p->spmap[i][1]) + (data->run->posY - data->p->spmap[i][0]) * (data->run->posY - data->p->spmap[i][0]));
		copy[i][0] = data->p->spmap[i][0];
		copy[i][1] = data->p->spmap[i][1];
		i++;
	}
	i = 0;
	while (i < data->p->isprite)
	{
		j = 0;
		tmp = 0.0;
		tmpi = 0;
		while (j < data->p->isprite)
		{
			if (spriteDistance[j] > tmp)
			{
				tmp = spriteDistance[j];
				tmpi = j;
			}
			j++;
		}
		data->p->spmap[i][0] = copy[tmpi][0];
		data->p->spmap[i][1] = copy[tmpi][1];
		spriteDistance[tmpi] = 0;
		i++;
	}
}

int		ft_loop(t_data *data)
{
	double		ZBuffer[data->p->width];
	int			texWidth = 64;
	int			texHeight = 64;

	t_img		img;
	img.img = mlx_new_image(data->run->mlx, data->p->width, data->p->height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_size, &img.endian);
	int			x = 0;
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
		double	perpWallDist = 0;
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
				if (stepX < 0)
					side = 1;
				else
					side = 0;
				sideDistX += deltaDistX;
				mapX += stepX;
			}
			else
			{
				if (stepY < 0)
					side = 2;
				else
					side = 3;
				sideDistY += deltaDistY;
				mapY += stepY;
			}
			if (data->p->map[mapY][mapX] == 1)
				hit = 1;
		}
		if (side == 0 || side == 1)
			perpWallDist = (mapX - data->run->posX + (1 - stepX) / 2) / rayDirX;
		else if (side == 2 || side == 3)
			perpWallDist = (mapY - data->run->posY + (1 - stepY) / 2) / rayDirY;
		int lineHeight = (int)(data->p->height / perpWallDist);
		int	drawStart = -lineHeight / 2 + data->p->height / 2;
		if (drawStart < 0)
			drawStart = 0;
		int	drawEnd = lineHeight / 2 + data->p->height / 2;
		if (drawEnd >= data->p->height)
			drawEnd = data->p->height - 1;

		//Texture

		double	wallX = 0;
		if (side == 0 || side == 1)
			wallX = data->run->posY + perpWallDist * rayDirY;
		else if (side == 2 || side == 3)
			wallX = data->run->posX + perpWallDist * rayDirX;
		wallX -= floor((wallX));

		int		texX = (int)(wallX * (double)texWidth);
		if ((side == 0 || side == 1) && rayDirX > 0)
			texX = texWidth - texX - 1;
		if ((side == 2 || side == 3) && rayDirY < 0)
			texX = texWidth - texX - 1;

		double	step = 1.0 * texHeight / lineHeight;

		double	texPos = (drawStart - data->p->height / 2 + lineHeight / 2) * step;
		int		y = 0;
		while (y < drawStart)
		{
			my_mlx_pixel_put(&img, x, y, data->p->ceiling);
			y++;
		}
		while (y < drawEnd)
		{
			int	texY = (int)texPos & (texHeight - 1);
			texPos += step;

			int color;
			//East == 0
			//West == 1
			//Nord == 2
			//Zuid == 3
			if (side == 0)
				color = *(unsigned int*)(data->e->addr + (texY * data->e->line_size + texX * (data->e->bits_per_pixel / 8)));
			if (side == 1)
				color = *(unsigned int*)(data->w->addr + (texY * data->w->line_size + texX * (data->w->bits_per_pixel / 8)));
			if (side == 2)
				color = *(unsigned int*)(data->n->addr + (texY * data->n->line_size + texX * (data->n->bits_per_pixel / 8)));
			if (side == 3)
				color = *(unsigned int*)(data->s->addr + (texY * data->s->line_size + texX * (data->s->bits_per_pixel / 8)));
			char	*dst;
			dst = img.addr + (y * img.line_size + x * (img.bits_per_pixel / 8));
			*(unsigned int*)dst = color;

			y++;
		}
		while (y < data->p->height)
		{
			my_mlx_pixel_put(&img, x, y, data->p->floor);
			y++;
		}
		ZBuffer[x] = perpWallDist;
		x++;
	}

	//Sprite
	ft_sprite_sort(data);
	int			i = 0;
	while (i < data->p->isprite)
	{
		double		spriteX = data->p->spmap[i][1] - data->run->posX + 0.5;
		double		spriteY = data->p->spmap[i][0] - data->run->posY + 0.5;
		double		invDet = 1.0 / (data->run->planeX * data->run->dirY - data->run->dirX * data->run->planeY);
		double		transformX = invDet * (data->run->dirY * spriteX - data->run->dirX * spriteY);
		double		transformY = invDet * (-(data->run->planeY) * spriteX + data->run->planeX * spriteY);
		int			spriteScreenX = (int)((data->p->width / 2) * (1 + transformX / transformY));
		int				spriteHeight = abs((int)(data->p->height / (transformY)));
		int			drawStartY = -spriteHeight / 2 + data->p->height / 2;
		if (drawStartY < 0)
			drawStartY = 0;
		int			drawEndY = spriteHeight / 2 + data->p->height / 2;
		if (drawEndY >= data->p->height)
			drawEndY = data->p->height - 1;
		int			spriteWidth = abs((int)(data->p->height / (transformY)));
		int			drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0)
			drawStartX = 0;
		int			drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= data->p->width)
			drawEndX = data->p->width - 1;
		int		stripe = drawStartX;
		while (stripe < drawEndX)
		{
			int	texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * data->sp->texWidth / spriteWidth) / 256;
			if (transformY > 0 && stripe > 0 && stripe < data->p->width && transformY < ZBuffer[stripe])
			{
				int		y = drawStartY;
				while (y < drawEndY)
				{
					int		d = (y) * 256 - data->p->height * 128 + spriteHeight * 128;
					int		texY = ((d * data->sp->texHeight) / spriteHeight) / 256;
					unsigned int	color = *(unsigned int*)(data->sp->addr + (texY * data->sp->line_size + texX * (data->sp->bits_per_pixel / 8)));
					char			*dst;
					if (color != 0x000000)
					{
						dst = img.addr + (y * img.line_size + stripe * (img.bits_per_pixel / 8));
						*(unsigned int*)dst = color;
					}
					y++;
				}
			}
			stripe++;
		}
		i++;
	}
	mlx_put_image_to_window(data->run->mlx, data->run->win, img.img, 0, 0);
	mlx_destroy_image(data->run->mlx, img.img);
	return (0);
}
