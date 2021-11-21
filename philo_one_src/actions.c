/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 12:05:06 by ldavids           #+#    #+#             */
/*   Updated: 2021/06/02 12:19:48 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_one.h"

int	finish_philo_meals(int max, t_struct *glo)
{
	int	i;

	i = 0;
	while (i < glo->nb_philo)
	{
		if (glo->philos[i].meals_eaten < max)
		{
			return (0);
		}
		i++;
	}
	return (1);
}

void	philo_take_forks(t_philo *philo)
{
	if (philo->nb % 2 == 0)
	{
		pthread_mutex_lock(&philo->global->m_forks[philo->lfork]);
		pthread_mutex_lock(&philo->global->m_forks[philo->rfork]);
		display(philo, " has taken a fork", 0, 1);
		display(philo, " has taken a fork", 0, 1);
	}
	else
	{
		pthread_mutex_lock(&philo->global->m_forks[philo->rfork]);
		pthread_mutex_lock(&philo->global->m_forks[philo->lfork]);
		display(philo, " has taken a fork", 0, 1);
		display(philo, " has taken a fork", 0, 1);
	}
}

void	philo_drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->global->m_forks[philo->rfork]);
	pthread_mutex_unlock(&philo->global->m_forks[philo->lfork]);
}

void	life(t_philo *philo)
{
	philo_take_forks(philo);
	pthread_mutex_lock(&philo->m_eating);
	display(philo, " is eating", 0, 1);
	philo->last_meal = time_now();
	h_sleep(philo->global->t_to_eat);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->m_eating);
	philo_drop_forks(philo);
	display(philo, " is sleeping", 0, 1);
	h_sleep(philo->global->t_to_sleep);
	display(philo, " is thinking", 0, 1);
}
