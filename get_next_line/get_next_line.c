/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/27 14:15:45 by novan-ve       #+#    #+#                */
/*   Updated: 2020/01/23 15:38:24 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_cpy(char **line, char **str, int fd)
{
	int		i;

	i = 0;
	while (str[fd][i] != '\n' && str[fd][i] != '\0')
		i++;
	if (str[fd][i] == '\n')
	{
		*line = ft_gsubstr(str[fd]);
		if (!*line)
		{
			free(str[fd]);
			return (-1);
		}
		return (1);
	}
	*line = ft_gstrdup(str[fd]);
	if (!*line)
		return (-1);
	free(str[fd]);
	str[fd] = 0;
	return (0);
}

int		ft_strcheck(char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strread(int fd, char **str, ssize_t red)
{
	char		*buf;

	while (red > 0)
	{
		buf = (char*)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf)
		{
			free(str[fd]);
			return (0);
		}
		red = read(fd, buf, BUFFER_SIZE);
		if (red < 0)
		{
			free(str[fd]);
			return (0);
		}
		buf[red] = '\0';
		str[fd] = ft_strcat(str[fd], buf);
		if (!str[fd])
			return (0);
		if (ft_strcheck(str[fd]))
			break ;
	}
	return (str[fd]);
}

char	*ft_plusn(char *str)
{
	char	*dst;
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
		{
			dst = ft_gstrdup(str + i + 1);
			if (!dst)
			{
				free(str);
				return (0);
			}
			free(str);
			return (dst);
		}
		i++;
	}
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static char	*str[INT_MAX];
	ssize_t		red;
	int			check;

	red = 1;
	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	if (!str[fd])
		str[fd] = ft_gstrdup("");
	if (!str[fd])
		return (-1);
	str[fd] = ft_strread(fd, str, red);
	if (!str[fd])
		return (-1);
	check = ft_cpy(line, str, fd);
	if (check == -1)
		return (-1);
	if (!check)
		return (0);
	str[fd] = ft_plusn(str[fd]);
	if (!str[fd])
		return (-1);
	return (1);
}
