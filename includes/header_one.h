/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_one.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 12:08:00 by ldavids           #+#    #+#             */
/*   Updated: 2021/06/02 12:20:04 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_ONE_H
# define HEADER_ONE_H
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t			thread;
	pthread_t			t_dead;

	int					nb;
	int					meals_eaten;
	int					lfork;
	int					rfork;

	unsigned long		death_time;
	unsigned long		last_meal;

	struct s_struct		*global;
	pthread_mutex_t		m_start;
	pthread_mutex_t		m_eating;
}t_philo;

typedef struct s_struct
{
	pthread_t		t_meal;

	int				nb_philo;
	unsigned long	t_to_die;
	unsigned long	t_to_eat;
	unsigned long	t_to_sleep;
	int				nb_philo_must_eat;

	unsigned long	init_time;

	t_philo			*philos;

	pthread_mutex_t	*m_forks;
	pthread_mutex_t	m_display;
	pthread_mutex_t	m_dead;
}t_struct;

int				ft_atoi(const char *str);
int				ft_strlen(char *str);
char			*ft_itoa(int n);
int				ft_isdigit(int c);
int				ft_putstr_error(char *s);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
int				threads(t_struct *glo, int i);
unsigned long	ft_get_time(void);
int				finish_philo_meals(int max, t_struct *glo);
void			life(t_philo *philo);
void			free_all(t_struct *glo);
void			h_sleep(unsigned int time);
unsigned int	time_now(void);
void			display(t_philo *philo, char *s, int len, int i);
int				ft_checker(int argc, char **argv);
int				assign_args(int argc, char **argv, t_struct *glo);

#endif
