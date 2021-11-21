/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_two.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 23:06:56 by ldavids           #+#    #+#             */
/*   Updated: 2021/06/01 14:51:32 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_TWO_H
# define HEADER_TWO_H

# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_philo
{
	int					nb;
	pthread_t			th_thread;
	pthread_t			th_dead;
	int					eating;
	unsigned long		last_meal;
	int					left_fork;
	int					right_fork;
	int					meals_eaten;
	char				*sem_name;
	unsigned long		death;
	sem_t				*sem_eating;
	struct s_struct		*glo;
}				t_philo;

typedef struct s_struct
{
	pthread_t		th_meals;
	int				nb_philo;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				nb_philo_must_eat;
	int				dead;
	unsigned int	start_time;
	sem_t			*sem_start;
	sem_t			*sem_waiter;
	sem_t			*sem_forks;
	sem_t			*sem_philo_display;
	sem_t			*sem_philo_dead;
	t_philo			*philo;
}				t_struct;

int				ft_putstr_error(char *s);
int				ft_atoi(const char *str);
char			*ft_itoa(int n);
int				ft_isdigit(int c);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *s, int fd);
int				ft_checker(int argc, char **argv);
int				init_philo(t_struct *glo);
int				launch_philo(t_struct *glo);
void			philo_take_fork(t_philo *philo);
void			philo_drop_fork(t_philo *philo);
void			philo_eat(t_philo *philo);
void			philo_sleep(t_philo *philo);
void			philo_think(t_philo *philo);
void			display(t_philo *philo, char *s, int len, int i);
void			controler(t_struct *glo, t_philo *philo);
int				elapsed_time(void);
void			solo(t_struct *glo);
void			free_philo(t_struct *glo, t_philo *philo);
unsigned long	ft_get_time(void);
void			*meal_counter(t_struct *global);
void			*is_dead(t_philo *philo);
unsigned int	time_now(void);
void			h_sleep(unsigned int time);
int				ft_strlen(char *s);

#endif
