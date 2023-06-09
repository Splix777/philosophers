#include "philosophers.h"

void	exit_error(char *str)
{
    write(2, str, ft_strlen(str));
    exit(1);
}

void	exit_error_free(char *str, t_table *table)
{
    int	i;

    i = 0;
    write(2, str, ft_strlen(str));
    while (i < table->n_forks)
    {
        pthread_mutex_destroy(&table->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&table->writing);
    pthread_mutex_destroy(&table->serving);
    free(table->forks);
    free(table->philos);
    free(table);
    exit(1);
}