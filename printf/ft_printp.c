/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/27 16:06:59 by novan-ve       #+#    #+#                */
/*   Updated: 2019/12/27 16:07:34 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printp3(t_print *p)
{
	int		i;

	i = 0;
	if (p->just == 'r' || p->padchar == '0')
		ft_putstr_fd("0x", 1);
	if (p->just == 'r')
		ft_putstr_fd(p->hex, 1);
	while (i < (p->tmpwidth - p->tmplen))
	{
		ft_putchar_fd(p->padchar, 1);
		i++;
	}
	i = 0;
	if (p->just == 'l' && p->padchar != '0')
		ft_putstr_fd("0x", 1);
	while (i < (p->prec - p->tmplen + 2))
	{
		p->len++;
		ft_putchar_fd('0', 1);
		i++;
	}
	if (p->just == 'l')
		ft_putstr_fd(p->hex, 1);
}

void	ft_printp2(t_print *p)
{
	int		i;

	i = 0;
	p->tmplen = 3;
	if (p->prec == 0)
		p->tmplen = 2;
	while (i < p->tmpwidth - p->tmplen)
	{
		ft_putchar_fd(p->padchar, 1);
		i++;
	}
	i = 0;
	if (p->tmplen == 2)
		ft_putstr_fd("0x", 1);
	else if (p->tmplen == 3)
		ft_putstr_fd("0x0", 1);
	while (i < p->prec - 1)
	{
		p->len++;
		ft_putchar_fd('0', 1);
		i++;
	}
}

void	ft_printp(t_print *p)
{
	int		i;

	i = 0;
	ft_dec_to_hex(p, va_arg(p->args, unsigned long), 0, 13);
	p->tmplen += 2;
	if (p->hex[0] == '\0')
		ft_printp2(p);
	else
		ft_printp3(p);
}
