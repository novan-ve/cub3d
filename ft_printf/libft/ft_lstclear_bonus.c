/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/11 16:24:29 by novan-ve      #+#    #+#                 */
/*   Updated: 2019/11/14 13:14:04 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	while (*lst)
	{
		del((*lst)->next);
		*lst = (*lst)->next;
	}
	*lst = NULL;
	free(*lst);
}
