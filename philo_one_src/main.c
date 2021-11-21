/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 12:05:49 by ldavids           #+#    #+#             */
/*   Updated: 2021/06/02 12:20:38 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_one.h"

void	free_all(t_struct *glo)
{
	int		i;

	i = 0;
	if (glo->m_forks)
	{
		while (i < glo->nb_philo)
		{
			pthread_mutex_destroy(&glo->philos[i].m_eating);
			pthread_mutex_destroy(&glo->m_forks[i++]);
			usleep (10);
		}
		free(glo->m_forks);
	}
	i = 0;
	if (glo->philos)
		free(glo->philos);
	pthread_mutex_destroy(&glo->m_display);
	pthread_mutex_destroy(&glo->m_dead);
}

int	init_philosophers(t_struct *glo)
{
	int	i;

	i = -1;
	while (++i < glo->nb_philo)
	{
		glo->philos[i].global = glo;
		glo->philos[i].nb = i;
		glo->philos[i].lfork = i;
		glo->philos[i].rfork = (i + 1) % glo->nb_philo;
		glo->philos[i].meals_eaten = 0;
		if (pthread_mutex_init(&glo->philos[i].m_eating, NULL))
			return (-11);
		if (pthread_mutex_init(&glo->philos[i].m_start, NULL))
			return (-1);
		pthread_mutex_lock(&glo->philos[i].m_start);
	}
	return (0);
}

int	init_pm(t_struct *glo, int argc, char **argv)
{
	int	i;

	glo->nb_philo = ft_atoi(argv[1]);
	glo->t_to_die = ft_atoi(argv[2]);
	glo->t_to_eat = ft_atoi(argv[3]);
	glo->t_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		glo->nb_philo_must_eat = ft_atoi(argv[5]);
	glo->philos = (t_philo *)malloc(sizeof(t_philo) * glo->nb_philo);
	if (!glo->philos)
		return (-10);
	if (pthread_mutex_init(&glo->m_display, NULL)
		|| pthread_mutex_init(&glo->m_dead, NULL))
		return (-11);
	glo->m_forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* glo->nb_philo);
	if (!glo->m_forks)
		return (-10);
	i = -1;
	while (++i < glo->nb_philo)
		if (pthread_mutex_init(&glo->m_forks[i], NULL))
			return (-11);
	pthread_mutex_lock(&glo->m_dead);
	return (init_philosophers(glo));
}

int	main(int argc, char **argv)
{
	t_struct	global;

	if (ft_checker(argc, argv) == 1)
		return (1);
	if (assign_args(argc, argv, &global))
		return (1);
	init_pm(&global, argc, argv);
	threads(&global, -1);
	pthread_mutex_lock(&global.m_dead);
	pthread_mutex_unlock(&global.m_dead);
	free_all(&global);
	return (0);
}
