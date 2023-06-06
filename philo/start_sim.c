#include "philosophers.h"

void    *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (!(philo->pos % 2))
        go_sleep(philo, philo->table->t_eat / 2);
    while (philo->status == ALIVE && philo->table->stop == 0)
    {
        go_eat(philo);
        print_action(philo, "is sleeping\n", UNLOCK);
        go_sleep(philo, philo->table->t_sleep);
        print_action(philo, "is thinking\n", UNLOCK);
    }
    return (NULL);
}

void    monitor_philos(t_table *table)
{
    int i;

    while (table->stop == 0)
    {
        i = 0;
        while (i < table->n_philo)
        {
            pthread_mutex_lock(&table->eating);
            if ((get_time() - table->philos[i].last_meal) >= table->t_die)
            {
                print_action(&table->philos[i], "died\n", UNLOCK);
                table->stop = 1;
                break ;
            }
            pthread_mutex_unlock(&table->eating);
            i++;
        }
    }
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