/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 10:21:59 by novan-ve       #+#    #+#                */
/*   Updated: 2020/01/27 17:39:23 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_exit(char *s)
{
	printf("%s\n", s);
	exit(0);
	return (0);
}

int		main(int argc, char **argv)
{
	t_data	data;
	t_parse	parse;

	if (argc != 2)
	{
		printf("No map found\n");
		return (0);
	}
	parse = ft_parse(argv[1]);
	data.parse = &parse;
	return (0);
}
