/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 15:23:00 by ldavids           #+#    #+#             */
/*   Updated: 2021/06/01 15:23:10 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_three.h"

unsigned int	time_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	h_sleep(unsigned int time)
{
	unsigned int	start;

	start = time_now();
	while ((time_now() - start) < time)
		usleep(250);
}

void	solo(t_struct *glo)
{
	ft_putstr_fd("0......1   has taken a fork\n", 1);
	ft_putnbr_fd(glo->t_to_die, 1);
	ft_putstr_fd("......1   died\n", 1);
	free(glo->philo[0].sem_name);
	free(glo->philo);
	free(glo);
}
