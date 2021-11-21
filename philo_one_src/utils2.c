/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 12:06:12 by ldavids           #+#    #+#             */
/*   Updated: 2021/06/02 12:13:41 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_one.h"

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

unsigned long	ft_get_time(void)
{
	unsigned long			res;
	static struct timeval	time;

	gettimeofday(&time, NULL);
	res = time.tv_sec * 1000;
	res += time.tv_usec / 1000;
	return (res);
}
