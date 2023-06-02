#include "philosophers.h"

void    *routine(void *arg)
{
    t_philo *philo;
    t_table *table;

    philo = (t_philo *)arg;
    table = philo->table;
    if (philo->pos % 2 == 0 && table->n_philo != 1)
        go_sleep(table, table->t_eat / 2);
    while (philo->status == ALIVE && philo->n_meals != table->n_meals)
    {
        go_eat(philo);
        print_action(philo, "is sleeping\n", UNLOCK);
        go_sleep(philo, table->t_sleep);
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
        pthread_create(&table->philos[i].thread_id, NULL, &routine, &table->philos[i]);
        i++;
    }
}