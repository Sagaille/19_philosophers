/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 16:08:23 by ldavids           #+#    #+#             */
/*   Updated: 2021/06/01 15:25:02 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_three.h"

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

	timestamp = time_now() - philo->start_sec;
	final = ft_itoa(timestamp);
	if (final == NULL)
		return ;
	buffer_to_zero(buffer);
	len = ft_add_back(final, buffer, len);
	len = ft_add_back(" ", buffer, len);
	free(final);
	final = ft_itoa(philo->nb);
	if (final == NULL)
		return ;
	len = ft_add_back(final, buffer, len);
	len = ft_add_back(" ", buffer, len);
	free(final);
	len = ft_add_back(s, buffer, len);
	len = ft_add_back("\n", buffer, len);
	sem_wait(philo->glo->sem_philo_display);
	write(1, buffer, len);
	if (i == 1)
		sem_post(philo->glo->sem_philo_display);
}
