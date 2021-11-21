/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 16:08:20 by ldavids           #+#    #+#             */
/*   Updated: 2021/06/01 14:50:12 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_two.h"

unsigned long	ft_get_time(void)
{
	static struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	*life(t_philo *philo)
{
	philo_take_fork(philo);
	philo_eat(philo);
	philo_sleep(philo);
	philo_think(philo);
	return (NULL);
}

void	*ft_start(t_philo *philo)
{
	sem_wait(philo->glo->sem_start);
	philo->last_meal = time_now();
	philo->death = philo->last_meal + philo->glo->t_to_die;
	if (pthread_create(&philo->th_dead, NULL, (void *)&is_dead, philo))
		return (NULL);
	pthread_detach(philo->th_dead);
	philo->last_meal = time_now();
	while (1)
		life(philo);
	return (NULL);
}

int	launch_philo(t_struct *glo)
{
	int		i;

	if (glo->nb_philo_must_eat > 0)
	{
		if (pthread_create(&glo->th_meals, NULL, (void *)&meal_counter, glo))
			return (1);
		pthread_detach(glo->th_meals);
	}
	i = -1;
	while (++i < glo->nb_philo)
		sem_wait(glo->sem_start);
	i = 0;
	while (i < glo->nb_philo)
	{
		if (pthread_create(&glo->philo[i].th_thread, NULL, \
		(void *)&ft_start, (void *)&glo->philo[i]))
			return (1);
		pthread_detach(glo->philo[i].th_thread);
		i++;
	}
	i = -1;
	glo->start_time = time_now();
	while (++i < glo->nb_philo)
		sem_post(glo->sem_start);
	return (1);
}
