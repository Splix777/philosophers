/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalazar <fsalazar@student.42madrid.com:>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:10:40 by fsalazar          #+#    #+#             */
/*   Updated: 2023/06/12 11:10:42 by fsalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	if (!(philo->pos % 2))
		go_sleep(philo, table->t_eat);
	while (1)
	{
		go_eat(philo, table);
		print_action(philo, table, "is sleeping\n");
		go_sleep(philo, table->t_sleep);
		print_action(philo, table, "is thinking\n");
		if (ft_checker(philo, table))
			break ;
	}
	return (NULL);
}

void	monitor_philos(t_table *table, int i, int full)
{
	while (!table->stop)
	{
		pthread_mutex_lock(&table->status);
		if (table->philos[i].n_meals == table->n_meals
			&& table->philos[i].status == ALIVE)
		{
			table->philos[i].status = FULL;
			full++;
		}
		if (full == table->n_philo)
			table->stop = 2;
		if ((get_time() - table->philos[i].last_meal) >= table->t_die)
		{
			table->stop = 1;
			table->philos[i].status = DEAD;
			pthread_mutex_unlock(&table->status);
			print_dead_action(&table->philos[i], table, "died\n");
			break ;
		}
		pthread_mutex_unlock(&table->status);
		i = (i + 1) % table->n_philo;
		usleep(20);
	}
}

void	start_sim(t_table *table)
{
	int	i;
	int	full;

	i = 0;
	table->t_start = get_time();
	while (i < table->n_philo && table->n_philo > 1)
	{
		if (pthread_create(&table->philos[i].thread_id, NULL, &routine,
				&table->philos[i]))
		{
			printf("Error: pthread_create failed\n");
			end_sim(table, i, FAILED);
		}
		i++;
	}
	i = 0;
	full = 0;
	monitor_philos(table, i, full);
}

void	end_sim(t_table *table, int i, int status)
{
	if (status == SUCCESS && table->stop == 2)
	{
		printf(COLOR_MAGENTA);
		printf("All philosophers have eaten %d times!\n", table->n_meals);
		printf(COLOR_RESET);
	}
	while (i >= 0)
	{
		pthread_join(table->philos[i].thread_id, NULL);
		i--;
	}
	pthread_mutex_destroy(&table->writing);
	pthread_mutex_destroy(&table->status);
	i = 0;
	while (i < table->n_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
	free(table->philos);
	free(table);
	exit(status);
}

void	print_dead_action(t_philo *philo, t_table *table, char *str)
{
	unsigned long	time;

	time = get_time() - table->t_start;
	pthread_mutex_lock(&table->writing);
	if (ft_strcmp(str, "died\n") == 0)
		printf(COLOR_RED);
	printf("%lu %d %s", time, philo->pos, str);
	printf(COLOR_RESET);
	pthread_mutex_unlock(&table->writing);
}
