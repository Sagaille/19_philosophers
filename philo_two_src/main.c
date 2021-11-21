/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 13:31:09 by ldavids           #+#    #+#             */
/*   Updated: 2021/06/01 14:47:46 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_two.h"

int	ft_args_manager(int argc, t_struct *glo)
{
	if (glo->nb_philo_must_eat < 1 && argc == 6)
		return (ft_putstr_error("nb_philo_must_eat shoudn't be less then 1\n"));
	if (glo->nb_philo < 1)
		return (ft_putstr_error("nb_philo shoudn't be less then 1\n"));
	if (glo->t_to_die < 1)
		return (ft_putstr_error("time_to_die shoudn't be less then 1\n"));
	if (glo->t_to_eat < 1)
		return (ft_putstr_error("time_to_eat shoudn't be less then 1\n"));
	if (glo->t_to_sleep < 1)
		return (ft_putstr_error("time_to_sleep shoudn't be less then 1\n"));
	if (glo->t_to_sleep < 50 || glo->t_to_eat < 50 || glo->t_to_die < 50)
		ft_putstr_fd("less then 50 ms could be inaccurate\n", 1);
	if (glo->nb_philo > 50)
		ft_putstr_fd("more then 50 philosophers could cause crashes/lag\n", 1);
	return (0);
}

int	assign_args(int argc, char **argv, t_struct *glo)
{
	glo->nb_philo = ft_atoi(argv[1]);
	glo->t_to_die = ft_atoi(argv[2]);
	glo->t_to_eat = ft_atoi(argv[3]);
	glo->t_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		glo->nb_philo_must_eat = ft_atoi(argv[5]);
	else
		glo->nb_philo_must_eat = 0;
	if (ft_args_manager(argc, glo))
		return (1);
	return (0);
}

int	ft_checker(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	if (argc < 5 || argc > 6)
		return (1);
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
				return (1);
			if (ft_atoi(argv[i]) < 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	ft_free(t_struct *glo)
{
	int	i;

	i = 0;
	while (i < glo->nb_philo)
	{
		if (glo->philo[i].sem_name)
			free(glo->philo[i].sem_name);
		sem_close(glo->philo[i].sem_eating);
		i++;
	}
	sem_post(glo->sem_philo_dead);
	if (glo->philo != NULL)
		free(glo->philo);
}

int	main(int argc, char **argv)
{
	t_struct	glo;

	if (ft_checker(argc, argv) == 1)
	{
		ft_putstr_fd("Wrong args\n", 2);
		return (1);
	}
	if (assign_args(argc, argv, &glo))
		return (1);
	if (init_philo(&glo) == 1)
		return (1);
	if (glo.nb_philo == 1)
	{
		solo(&glo);
		ft_free(&glo);
		return (0);
	}
	launch_philo(&glo);
	sem_wait(glo.sem_philo_dead);
	ft_free(&glo);
	return (0);
}
