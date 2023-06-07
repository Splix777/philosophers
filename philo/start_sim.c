#include "philosophers.h"

void    *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (!(philo->pos % 2))
        go_sleep(philo, philo->pos);
    while (philo->status == ALIVE && !(philo->table->stop))
    {
        go_eat(philo);
        print_action(philo, "is sleeping\n");
        go_sleep(philo, philo->table->t_sleep);
        print_action(philo, "is thinking\n");
    }
    return (NULL);
}

void    monitor_philos(t_table *table)
{
    int i;
    int full;

    while (!table->stop)
    {
        i = 0;
        full = 0;
        while (i < table->n_philo)
        {
            pthread_mutex_lock(&table->eating);
            if ((get_time() - table->philos[i].last_meal) >= table->t_die)
            {
                print_action(&table->philos[i], "died\n");
                table->philos[i].status = DEAD;
                table->stop = 1;
            }
            pthread_mutex_unlock(&table->eating);
            if (table->philos[i].n_meals == table->n_meals)
            {
                table->philos[i].status = FULL;
                full++;
            }
            i++;
        }
        if (full == table->n_philo)
        {
            printf("All philosophers have eaten %d times\n", table->n_meals);
            table->stop = 1;
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