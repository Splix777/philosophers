/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalazar <fsalazar@student.42madrid.com:>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:11:22 by fsalazar          #+#    #+#             */
/*   Updated: 2023/06/12 11:11:24 by fsalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		table->philos[i].status = ALIVE;
		table->philos[i].pos = i + 1;
		table->philos[i].n_meals = 0;
		table->philos[i].last_meal = get_time();
		table->philos[i].left_fork = (i + 1) % table->n_forks;
		table->philos[i].right_fork = i;
		table->philos[i].table = table;
		i++;
	}
}

void	init_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_forks)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			exit_error_free(ERROR_MUTEX, i, table);
		i++;
	}
	if (pthread_mutex_init(&table->writing, NULL) != 0)
		exit_error_free(ERROR_MUTEX, i, table);
	if (pthread_mutex_init(&table->status, NULL) != 0)
		exit_error_free(ERROR_MUTEX, i, table);
}

void	invite_philos(t_table *table)
{
	table->philos = malloc(sizeof(t_philo) * table->n_philo);
	if (!table->philos)
	{
		free(table);
		exit_error(ERROR_MALLOC);
	}
	table->forks = malloc(sizeof(pthread_mutex_t) * table->n_forks);
	if (!table->forks)
	{
		free(table->philos);
		free(table);
		exit_error(ERROR_MALLOC);
	}
	init_philos(table);
	init_mutex(table);
}

t_table	*set_table(int argc, char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		exit_error(ERROR_MALLOC);
	table->n_philo = ft_atoi(argv[1]);
	table->t_die = ft_atoi(argv[2]);
	table->t_eat = ft_atoi(argv[3]);
	table->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->n_meals = ft_atoi(argv[5]);
	else
		table->n_meals = -1;
	table->n_forks = table->n_philo;
	table->stop = 0;
	table->argc = argc;
	table->argv = argv;
	if (table->t_die <= 0 || table->t_eat <= 0 || table->t_sleep <= 0
		|| table->n_meals == 0 || table->n_philo < 1 || table->n_philo > 200)
	{
		free(table);
		exit_error(ERROR_FORMAT);
	}
	invite_philos(table);
	return (table);
}
