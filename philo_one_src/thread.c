/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 12:06:05 by ldavids           #+#    #+#             */
/*   Updated: 2021/06/02 12:16:30 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_one.h"

void	*meal_count(t_struct *global)
{
	while (1)
	{
		if (finish_philo_meals(global->nb_philo_must_eat, global))
		{
			pthread_mutex_lock(&global->m_display);
			pthread_mutex_unlock(&global->m_dead);
			return (NULL);
		}
		usleep(1000);
	}
}

void	*check_death(t_philo *philo)
{
	while (1)
	{
		if (time_now() - philo->last_meal > philo->global->t_to_die)
		{
			display(philo, " has died", 0, 0);
			pthread_mutex_unlock(&philo->global->m_dead);
		}
		usleep(1000);
	}
	(void) philo;
}

void	*start_thread(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_start);
	philo->last_meal = time_now();
	pthread_create(&philo->t_dead, NULL,
		(void *)&check_death, philo);
	pthread_detach(philo->t_dead);
	while (1)
		life(philo);
}

int	threads(t_struct *glo, int i)
{
	glo->init_time = time_now();
	if (glo->nb_philo_must_eat > 0)
	{
		pthread_create(&glo->t_meal, NULL,
			(void *)&meal_count, glo);
		pthread_detach(glo->t_meal);
	}
	i = -1;
	while (++i < glo->nb_philo)
	{
		pthread_create(&glo->philos[i].thread, NULL,
			(void *)&start_thread, (void *)&glo->philos[i]);
		pthread_detach(glo->philos[i].thread);
	}
	i = -1;
	while (++i < glo->nb_philo)
		if (i % 2 == 1)
			pthread_mutex_unlock(&glo->philos[i].m_start);
	usleep(1000);
	i = -1;
	while (++i < glo->nb_philo)
		if (i % 2 == 0)
			pthread_mutex_unlock(&glo->philos[i].m_start);
	return (1);
}
