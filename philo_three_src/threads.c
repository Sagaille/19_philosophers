/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 13:58:57 by ldavids           #+#    #+#             */
/*   Updated: 2021/06/01 15:25:32 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_three.h"

int	finish_philo_meals(int max, t_struct *glo)
{
	int	i;

	i = 0;
	while (i < glo->nb_philo)
	{
		if (glo->philo[i].meals_eaten < max)
			return (0);
		i++;
	}
	return (1);
}

void	*meal_counter(t_struct *glo)
{
	int		i;

	i = 0;
	while (i < glo->nb_philo)
	{
		sem_wait(glo->sem_meal_count);
		usleep(1);
		i++;
	}
	sem_wait(glo->sem_philo_display);
	usleep(10);
	sem_post(glo->sem_philo_dead);
	return (NULL);
}

void	*is_dead(t_philo *philo)
{
	while (1)
	{
		if (time_now() > philo->death)
		{
			display(philo, "died", 0, 0);
			sem_post(philo->glo->sem_philo_dead);
			break ;
		}
		usleep(100);
	}
	return (NULL);
}
