/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 16:57:22 by ldavids           #+#    #+#             */
/*   Updated: 2021/06/01 18:17:21 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_two.h"

static unsigned int	checkmax(unsigned long nb, int pos)
{
	if (nb > 2147483647 && pos > 0)
		return (-1);
	if (nb > 2147483648 && pos < 0)
		return (-1);
	return ((int)nb * pos);
}

int	ft_atoi(const char *str)
{
	unsigned long	nb;
	int				i;
	int				pos;

	pos = 1;
	i = 0;
	nb = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' \
			 || str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			pos = -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] > 47 && str[i] < 58)
			nb = (str[i++] - 48) + (nb * 10);
		else
			break ;
	}
	return (checkmax(nb, pos));
}

static int	ft_len(long int n)
{
	int				i;

	i = 0;
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	return (i + 1);
}

char	*ft_itoa(int n)
{
	long int		i;
	char			*str;
	long int		negatif;
	long int		nb;

	negatif = 0;
	nb = (long int)n;
	if (nb < 0)
	{
		negatif = 1;
		nb = -nb;
	}
	i = ft_len(nb) + negatif;
	str = (char *)malloc(sizeof(char) * i + 1);
	str[i--] = '\0';
	while (i >= 0)
	{
		str[i--] = nb % 10 + 48;
		nb = nb / 10;
	}
	if (negatif == 1)
		str[0] = '-';
	return (str);
}
