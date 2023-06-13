/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_and_exits.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalazar <fsalazar@student.42madrid.com:>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:11:16 by fsalazar          #+#    #+#             */
/*   Updated: 2023/06/12 11:11:17 by fsalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	exit_error(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}

void	exit_error_free(char *str, int i, t_table *table)
{
	write(2, str, ft_strlen(str));
	while (i >= 0)
	{
		i--;
		pthread_mutex_destroy(&table->forks[i]);
	}
	pthread_mutex_destroy(&table->writing);
	pthread_mutex_destroy(&table->status);
	free(table->forks);
	free(table->philos);
	free(table);
	exit(1);
}
