#include "philosophers.h"

void    init_philos(t_table *table)
{
    int i;

    i = 0;
    while (i < table->n_philo)
    {
        table->philos[i].status = ALIVE;
        table->philos[i].pos = i + 1;
        table->philos[i].n_meals = 0;
        table->philos[i].last_meal = 0;
        table->philos[i].left_fork = i;
        table->philos[i].right_fork = (i + 1);
        i++;
    }
}

int init_forks(t_table *table)
{
    int i;

    i = 0;
    while (i < table->n_forks)
    {
        if (pthread_mutex_init(&table->forks[i], NULL))
            return (0);
        i++;
    }
    if (pthread_mutex_init(&table->thinking, NULL))
        return (0);
    if (pthread_mutex_init(&table->eating, NULL))
        return (0);
    return (1);
}

void    invite_philos(t_table *table)
{
    table->philos = malloc(sizeof(t_philo) * table->n_philo);
    if (!table->philos)
        exit_error("Philos Malloc error");
    table->forks = malloc(sizeof(pthread_mutex_t) * table->n_forks);
    if (!table->forks)
    {
        free(table->philos);
        exit_error("Forks Malloc error");
    }
    if (!init_forks(table))
    {
        free(table->philos);
        free(table->forks);
        exit_error("Forks init error");
    }
    init_philos(table);
}

void    set_table(t_table *table, int argc, char **argv)
{
    table->n_philo = ft_atoi(argv[1]);
    if (table->n_philo <= 1)
        exit_error("Number of philosophers must be more than 1");
    table->n_forks = table->n_philo;
    if (argc == 6)
        table->n_meals = ft_atoi(argv[5]);
    else
        table->n_meals = 0;
    table->t_die = ft_atoi(argv[2]);
    table->t_eat = ft_atoi(argv[3]);
    table->t_sleep = ft_atoi(argv[4]);
    table->argc = argc;
    table->argv = argv;
    if (table->t_die <= 0 || table->t_eat <= 0 || table->t_sleep <= 0 || table->n_meals <= 0)
        exit_error("Arguments must be more than 0");
}