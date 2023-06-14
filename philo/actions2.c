/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalazar <fsalazar@student.42madrid.com:>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:53:21 by fsalazar          #+#    #+#             */
/*   Updated: 2023/06/14 11:53:23 by fsalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	go_sleep(t_philo *philo, unsigned long time)
{
	unsigned long	start;

	(void)philo;
	start = get_time();
	usleep(time * 900);
	while (1)
	{
		if ((get_time() - start) >= time)
			break ;
	}
}

void	is_eating(t_philo *philo, unsigned long time)
{
	unsigned long	start;

	(void)philo;
	start = get_time();
	usleep(time * 900);
	while (1)
	{
		if ((get_time() - start) >= time)
			break ;
	}
}

int	ft_checker(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(&table->status);
	if (philo->n_meals == table->n_meals)
	{
		pthread_mutex_unlock(&table->status);
		return (1);
	}
	if (table->stop)
	{
		pthread_mutex_unlock(&table->status);
		return (1);
	}
	pthread_mutex_unlock(&table->status);
	return (0);
}
