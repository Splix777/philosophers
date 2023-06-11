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
    pthread_mutex_destroy(&table->serving);
    free(table->forks);
    free(table->philos);
    free(table);
    exit(1);
}