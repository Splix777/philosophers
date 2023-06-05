#include "philosophers.h"

void    *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (!(philo->pos % 2))
        go_sleep(philo, philo->table->t_eat);
    while (philo->status == ALIVE && philo->n_meals != philo->table->n_meals)
    {
        go_eat(philo);
        print_action(philo, "is sleeping\n", UNLOCK);
        go_sleep(philo, philo->table->t_sleep);
        print_action(philo, "is thinking\n", UNLOCK);
    }
    return (NULL);
}

void    start_sim(t_table *table)
{
    int             i;

    i = 0;
    table->t_start = get_time();
    while (i < table->n_philo)
    {
        if (pthread_create(&table->philos[i].thread_id, NULL, &routine, &table->philos[i]))
            exit_error_free("Error: pthread_create\n", table);
        i++;
    }
    monitor_philos(table);
}