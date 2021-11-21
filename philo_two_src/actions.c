/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 12:52:33 by ldavids           #+#    #+#             */
/*   Updated: 2021/06/01 14:52:00 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_two.h"

void	philo_take_fork(t_philo *philo)
{
	sem_wait(philo->glo->sem_waiter);
	sem_wait(philo->glo->sem_forks);
	display(philo, "has taken a fork", 0, 1);
	sem_wait(philo->glo->sem_forks);
	display(philo, "has taken a fork", 0, 1);
	sem_post(philo->glo->sem_waiter);
}

void	philo_drop_fork(t_philo *philo)
{
	sem_post(philo->glo->sem_forks);
	sem_post(philo->glo->sem_forks);
}

void	philo_sleep(t_philo *philo)
{
	display(philo, "is sleeping", 0, 1);
	philo_drop_fork(philo);
	h_sleep(philo->glo->t_to_sleep);
}

void	philo_think(t_philo *philo)
{
	display(philo, "is thinking", 0, 1);
}

void	philo_eat(t_philo *philo)
{
	sem_wait(philo->sem_eating);
	display(philo, "is eating", 0, 1);
	philo->eating = 1;
	philo->last_meal = time_now();
	philo->death = philo->last_meal + philo->glo->t_to_die;
	philo->eating = 0;
	sem_post(philo->sem_eating);
	h_sleep(philo->glo->t_to_eat);
	philo->meals_eaten++;
}
