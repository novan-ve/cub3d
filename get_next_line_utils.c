/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/27 14:16:22 by novan-ve       #+#    #+#                */
/*   Updated: 2020/02/10 12:01:24 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	ft_strlen(const char *s)
{
	size_t	index;

	index = 0;
	while (s[index])
		index++;
	return (index);
}

char	*ft_gstrdup(char *s1)
{
	void	*ptr;
	char	*p;
	size_t	len;

	len = ft_strlen(s1) + 1;
	ptr = malloc(len);
	if (ptr == 0)
		return (NULL);
	p = ptr;
	while (len != 0)
	{
		*p = *s1;
		p++;
		s1++;
		len--;
	}
	return ((char*)ptr);
}

char	*ft_strcat2(char *origin, char *append, char *dest)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (origin[i] != '\0')
	{
		dest[i] = origin[i];
		i++;
	}
	while (append[j] != '\0')
	{
		dest[i] = append[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcat(char *origin, char *append)
{
	size_t	i;
	size_t	x;
	char	*dest;

	i = 0;
	x = ft_strlen(origin) + ft_strlen(append);
	dest = (char*)malloc(sizeof(char) * (x + 1));
	if (!dest)
	{
		free(append);
		free(origin);
		return (0);
	}
	dest = ft_strcat2(origin, append, dest);
	free(append);
	free(origin);
	return (dest);
}

char	*ft_gsubstr(char *str)
{
	char	*dst;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
		return (0);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	dst = (char*)malloc(sizeof(char) * i + 1);
	if (!dst)
		return (0);
	while (j < i)
	{
		dst[j] = str[j];
		j++;
	}
	dst[j] = '\0';
	return (dst);
}
