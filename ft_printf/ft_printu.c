/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printu.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/17 17:30:51 by novan-ve       #+#    #+#                */
/*   Updated: 2019/12/27 16:06:18 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putprec_fd(char *s, int fd, int prec)
{
	int		i;

	i = 0;
	if (s)
		while (s[i] != '\0' && i < prec)
		{
			ft_putchar_fd(s[i], fd);
			i++;
		}
}

void	ft_uputnbr_fd(unsigned int n, int fd)
{
	if (n < 0)
		ft_putnbr_fd(4294967295 - -n, fd);
	else if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
		ft_putchar_fd(n + '0', fd);
}

int		ft_nbrlenu(unsigned int nb, int x)
{
	int				i;

	i = 0;
	if (nb == 0)
		return (1);
	if (nb < 0 && x == 0)
		i = 1;
	while (nb > 0 || nb < 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

void	ft_printu2(t_print *p)
{
	int		i;

	i = 0;
	if (p->just == 'l')
		while (i < p->tmpwidth - p->tmplen && i < p->tmpwidth - p->prec)
		{
			ft_putchar_fd(p->padchar, 1);
			i++;
		}
	i = 0;
	while (i < (p->prec - p->tmplen))
	{
		p->len++;
		ft_putchar_fd('0', 1);
		i++;
	}
	if (p->prec != 0)
		ft_uputnbr_fd(p->itmp, 1);
	i = 0;
	if (p->just == 'r')
		while (i < p->tmpwidth - p->tmplen && i < p->tmpwidth - p->prec)
		{
			ft_putchar_fd(p->padchar, 1);
			i++;
		}
}

void	ft_printu(t_print *p)
{
	p->itmp = va_arg(p->args, unsigned int);
	p->tmplen += ft_nbrlenu(p->itmp, 1);
	if (p->prec == 0)
		p->tmplen = 0;
	if (p->tmplen < p->tmpwidth || p->prec != -1)
		ft_printu2(p);
	else
		ft_uputnbr_fd(p->itmp, 1);
}
