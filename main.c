/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 10:21:59 by novan-ve       #+#    #+#                */
/*   Updated: 2020/02/03 14:43:14 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_exit(char *s)
{
	printf("%s\n", s);
	exit(0);
	return (0);
}

t_run	init_run(t_data *data)
{
	t_run	run;

	run.posX = data->p->posx + 0.5;
	run.posY = data->p->posy + 0.5;
	if (data->p->orient == 'N' || data->p->orient == 'S')
	{
		run.dirX = 0;
		run.planeY = 0;
		run.dirY = (data->p->orient == 'N') ? -1 : 1;
		run.planeX = (data->p->orient == 'N') ? 0.66 : -0.66;
	}
	if (data->p->orient == 'E' || data->p->orient == 'W')
	{
		run.dirY = 0;
		run.planeX = 0;
		run.dirX = (data->p->orient == 'W') ? -1 : 1;
		run.planeY = (data->p->orient == 'W') ? -0.66 : 0.66;
	}
	return (run);
}

//E = 1, 0, 0, 0.66
//W = -1, 0, 0, -0.66
//S = 0, 1, -0.66, 0
//N = 0, -1, 0.66, 0

t_keys	init_keys()
{
	t_keys	keys;

	keys.key_up = 0;
	keys.key_down = 0;
	keys.key_left = 0;
	keys.key_right = 0;
	keys.key_a = 0;
	keys.key_d = 0;
	return (keys);
}

int		main(int argc, char **argv)
{
	t_data	data;
	t_parse	parse;
	t_run	run;
	t_keys	keys;

	if (argc != 2)
	{
		ft_printf("No map found\n");
		return (0);
	}
	ft_printf("Initialising map ...\n");
	parse = ft_parse(argv[1]);
	ft_printf("Map initialised!\n");
	data.p = &parse;
	data.p->file = argv[1];
	ft_printf("Opening game ...\n");
	run = init_run(&data);
	data.run = &run;
	keys = init_keys();
	data.keys = &keys;
	ft_run_game(&data);
	return (0);
}