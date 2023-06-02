#include "philosophers.h"

t_philo **init_philos(t_philo **philos, t_table *table)
{
    int i;

    i = 0;
    while (i < table->n_philo)
    {
        philos[i] = malloc(sizeof(t_philo));
        if (!philos[i])
        {
            free_philos(table, i);
            return (NULL);
        }
        philos[i]->status = ALIVE;
        philos[i]->pos = i + 1;
        philos[i]->n_meals = 0;
        philos[i]->last_meal = 0;
        philos[i]->left_fork = i;
        philos[i]->right_fork = (i + 1) % table->n_forks;
        //philos[i]->thread_id = i;
        philos[i]->table = table;
        i++;
    }
    return (philos);
}

int init_mutex(t_table *table)
{
    int i;

    i = 0;
    while (i < table->n_forks)
    {
        if (pthread_mutex_init(&table->forks[i], NULL))
            return (0);
        i++;
    }
    if (pthread_mutex_init(&table->writing, NULL))
        return (0);
    if (pthread_mutex_init(&table->eating, NULL))
        return (0);
    return (1);
}

t_philo **invite_philos(t_table *table)
{
    t_philo **philos;

    philos = malloc(sizeof(t_philo) * table->n_philo);
    if (!philos)
        exit_error("Philos Malloc error");
    memset(philos, 0, sizeof(t_philo) * table->n_philo);
    philos = init_philos(philos, table);
    if (!philos)
        exit_error("Philos Malloc error");
    table->forks = malloc(sizeof(pthread_mutex_t) * table->n_forks);
    if (!table->forks)
    {
        free_philos(table, table->n_philo - 1);
        exit_error("Forks Malloc error");
    }
    memset(table->forks, 0, sizeof(pthread_mutex_t) * table->n_forks);
    if (!init_mutex(table))
        exit_error_free("Mutex init error", table);
    return (philos);
}

t_table    *set_table(int argc, char **argv)
{
    t_table *table;

    table = malloc(sizeof(t_table));
    if (!table)
        exit_error("Table Malloc error");
    table->n_philo = ft_atoi(argv[1]);
    table->t_die = ft_atoi(argv[2]);
    table->t_eat = ft_atoi(argv[3]);
    table->t_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        table->n_meals = ft_atoi(argv[5]);
    else
        table->n_meals = -1;
    table->n_forks = table->n_philo;
    table->argc = argc;
    table->argv = argv;
    table->t_start = get_time();
    if (table->t_die <= 0 || table->t_eat <= 0 || table->t_sleep <= 0
        || table->n_meals <= 0 || table->n_philo <= 1)
        {
            free(table);
            exit_error("Arguments must be more than 0");
        }
    return (table);
}