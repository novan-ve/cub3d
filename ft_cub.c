/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cub.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 10:21:59 by novan-ve       #+#    #+#                */
/*   Updated: 2020/02/10 13:55:12 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_exit(char *s, int x)
{
	if (x == 1)
		ft_printf("Error\n");
	ft_printf("%s\n", s);
	exit(0);
	return (0);
}

t_run	init_run(t_data *data)
{
	t_run	run;

	run.posx = data->p->posx + 0.5;
	run.posy = data->p->posy + 0.5;
	if (data->p->orient == 'N' || data->p->orient == 'S')
	{
		run.dirx = 0;
		run.planey = 0;
		run.diry = (data->p->orient == 'N') ? -1 : 1;
		run.planex = (data->p->orient == 'N') ? 0.66 : -0.66;
	}
	if (data->p->orient == 'E' || data->p->orient == 'W')
	{
		run.diry = 0;
		run.planex = 0;
		run.dirx = (data->p->orient == 'W') ? -1 : 1;
		run.planey = (data->p->orient == 'W') ? -0.66 : 0.66;
	}
	return (run);
}

t_keys	init_keys(void)
{
	t_keys	keys;

	keys.key_left = 0;
	keys.key_right = 0;
	keys.key_a = 0;
	keys.key_s = 0;
	keys.key_d = 0;
	keys.key_w = 0;
	return (keys);
}

int		main(int argc, char **argv)
{
	t_data	data;
	t_parse	parse;
	t_run	run;
	t_keys	keys;

	if (argc < 2 || argc > 3 || (argc == 3 && ft_strncmp(argv[2], "--save", 7)))
	{
		ft_printf("No map found\n");
		return (0);
	}
	ft_printf("Initialising map ...\n");
	parse = ft_parse(argv[1]);
	ft_printf("Map initialised!\n");
	data.p = &parse;
	data.p->file = argv[1];
	if (argc == 3)
		data.p->save = (!ft_strncmp(argv[2], "--save", 6)) ? 1 : 0;
	ft_printf("Opening game ...\n");
	run = init_run(&data);
	data.r = &run;
	keys = init_keys();
	data.keys = &keys;
	ft_run_game(&data);
	return (0);
}
