/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalazar <fsalazar@student.42madrid.com:>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:10:46 by fsalazar          #+#    #+#             */
/*   Updated: 2023/06/12 11:10:48 by fsalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	go_eat(t_philo *philo, t_table *table)
{
	pick_up_forks(philo, table);
	print_action(philo, table, "is eating\n");
	pthread_mutex_lock(&table->status);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&table->status);
	is_eating(philo, table->t_eat);
	put_down_forks(philo, table);
	pthread_mutex_lock(&table->status);
	philo->n_meals++;
	pthread_mutex_unlock(&table->status);
}

void	pick_up_forks(t_philo *philo, t_table *table)
{
	if (philo->pos % 2)
	{
		pthread_mutex_lock(&table->forks[philo->right_fork]);
		print_action(philo, table, "has taken a fork\n");
		pthread_mutex_lock(&table->forks[philo->left_fork]);
		print_action(philo, table, "has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(&table->forks[philo->left_fork]);
		print_action(philo, table, "has taken a fork\n");
		pthread_mutex_lock(&table->forks[philo->right_fork]);
		print_action(philo, table, "has taken a fork\n");
	}
}

void	put_down_forks(t_philo *philo, t_table *table)
{
	if (philo->pos % 2)
	{
		pthread_mutex_unlock(&table->forks[philo->right_fork]);
		pthread_mutex_unlock(&table->forks[philo->left_fork]);
	}
	else
	{
		pthread_mutex_unlock(&table->forks[philo->left_fork]);
		pthread_mutex_unlock(&table->forks[philo->right_fork]);
	}
}

void	print_action(t_philo *philo, t_table *table, char *str)
{
	unsigned long	time;

	time = get_time() - table->t_start;
	pthread_mutex_lock(&table->writing);
	if (ft_strcmp(str, "is eating\n") == 0)
		printf(COLOR_GREEN);
	else if (ft_strcmp(str, "is sleeping\n") == 0)
		printf(COLOR_BLUE);
	else if (ft_strcmp(str, "is thinking\n") == 0)
		printf(COLOR_YELLOW);
	else if (ft_strcmp(str, "died\n") == 0)
		printf(COLOR_RED);
	pthread_mutex_lock(&table->status);
	if (philo->status != DEAD && table->stop == 0)
		printf("%lu %d %s", time, philo->pos, str);
	pthread_mutex_unlock(&table->status);
	printf(COLOR_RESET);
	pthread_mutex_unlock(&table->writing);
}

void	go_sleep(t_philo *philo, unsigned long time)
{
	unsigned long	start;
	(void) philo;

	start = get_time();
	usleep(time * 1000);
	while (1)
	{
		if ((get_time() - start) >= time)
			break ;
	}
}

void	is_eating(t_philo *philo, unsigned long time)
{
	unsigned long	start;
	(void) philo;

	start = get_time();
	usleep(time * 1000);
	while (1)
	{
		if ((get_time() - start) >= time)
			break ;
	}
}

unsigned long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}
