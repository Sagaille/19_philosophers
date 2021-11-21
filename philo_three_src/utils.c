/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 16:39:31 by ldavids           #+#    #+#             */
/*   Updated: 2021/05/28 19:08:01 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_three.h"

int	ft_putstr_error(char *s)
{
	ft_putstr_fd(s, 2);
	return (1);
}

int	ft_isdigit(int c)
{
	if (c < 48 || c > 57)
		return (0);
	return (1);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	index;

	index = 0;
	if (s == NULL || fd < 0)
		return ;
	while (s[index])
	{
		write(fd, &s[index], 1);
		index++;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	sign;

	if (fd < 0)
		return ;
	sign = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		sign = -n;
	}
	if (sign >= 10)
		ft_putnbr_fd(sign / 10, fd);
	ft_putchar_fd(sign % 10 + '0', fd);
}
