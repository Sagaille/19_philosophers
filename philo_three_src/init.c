/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 16:30:55 by ldavids           #+#    #+#             */
/*   Updated: 2021/06/01 15:15:59 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_three.h"

int	init_sub(t_struct *glo, int i)
{
	while (i < glo->nb_philo)
	{
		glo->philo[i].glo = glo;
		glo->philo[i].nb = i + 1;
		glo->philo[i].eating = 0;
		glo->philo[i].meals_eaten = 0;
		glo->philo[i].death = 0;
		glo->philo[i].sem_name = ft_itoa(i + 1);
		if (glo->philo[i].sem_name == NULL)
		{
			free(glo->philo);
			return (1);
		}
		sem_unlink(glo->philo[i].sem_name);
		glo->philo[i].sem_eating = \
		sem_open(glo->philo[i].sem_name, O_CREAT, 0644, 1);
		if (glo->philo[i].sem_name == (char *)SEM_FAILED)
		{
			free(glo->philo);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_philo(t_struct *glo)
{
	glo->philo = malloc(sizeof(t_philo) * glo->nb_philo);
	if (glo->philo == NULL)
		return (1);
	sem_unlink("sem_dead");
	glo->sem_philo_dead = sem_open("sem_dead", O_CREAT, 0644, 0);
	sem_unlink("sem_philo_display");
	glo->sem_philo_display = sem_open("sem_philo_display", O_CREAT, 0644, 1);
	sem_unlink("sem_waiter");
	glo->sem_waiter = sem_open("sem_waiter", O_CREAT, 0644, 1);
	sem_unlink("sem_forks");
	glo->sem_forks = sem_open("sem_forks", O_CREAT, 0644, glo->nb_philo);
	sem_unlink("sem_count");
	glo->sem_meal_count = sem_open("sem_count", O_CREAT, 0644, 0);
	sem_unlink("sem_start");
	glo->sem_start = sem_open("sem_start", O_CREAT, 0644, glo->nb_philo);
	if (init_sub(glo, 0) == 1)
		return (1);
	return (0);
}
