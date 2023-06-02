#include "philosophers.h"

void    exit_error(char *str)
{
    write(2, &str, ft_strlen(str));
    exit(1);
}

void    free_philos(t_table *table, int i)
{
    while (i >= 0)
        free(table->philos[i--]);
    free(table->philos);
}

void    exit_error_free(char *str, t_table *table)
{
    int i;

    i = 0;
    write(2, &str, ft_strlen(str));
    free_philos(table, table->n_philo - 1);
    while (i < table->n_forks)
    {
        pthread_mutex_destroy(&table->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&table->writing);
    pthread_mutex_destroy(&table->eating);
    free(table->forks);
    exit(1);
}