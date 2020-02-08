/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/11 14:50:53 by novan-ve      #+#    #+#                 */
/*   Updated: 2019/11/14 13:28:29 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstsize(t_list *lst)
{
	int		index;

	index = 0;
	while (lst)
	{
		index++;
		lst = lst->next;
	}
	return (index);
}
