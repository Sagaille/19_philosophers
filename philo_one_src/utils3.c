/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 12:06:16 by ldavids           #+#    #+#             */
/*   Updated: 2021/06/02 12:20:22 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_one.h"

unsigned int	time_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	h_sleep(unsigned int time)
{
	unsigned int	start;

	start = time_now();
	while ((time_now() - start) < time)
		usleep(500);
}

void	buffer_to_zero(char *buffer)
{
	int	i;

	i = 0;
	while (i < 350)
	{
		buffer[i] = '\0';
		i++;
	}
	return ;
}

int	ft_add_back(char *s, char *buffer, int len)
{
	int	i;

	i = 0;
	while (s[i])
	{
		buffer[len] = s[i];
		i++;
		len++;
	}
	return (len);
}

void	display(t_philo *philo, char *s, int len, int i)
{
	char	buffer[350];
	int		timestamp;
	char	*final;

	timestamp = ft_get_time() - philo->global->init_time;
	final = ft_itoa(timestamp);
	if (final == NULL)
		return ;
	buffer_to_zero(buffer);
	len = ft_add_back(final, buffer, len);
	len = ft_add_back(" ", buffer, len);
	free(final);
	final = ft_itoa(philo->nb + 1);
	if (final == NULL)
		return ;
	len = ft_add_back(final, buffer, len);
	free(final);
	len = ft_add_back(s, buffer, len);
	len = ft_add_back("\n", buffer, len);
	pthread_mutex_lock(&philo->global->m_display);
	write(1, buffer, len);
	if (i == 1)
		pthread_mutex_unlock(&philo->global->m_display);
}
