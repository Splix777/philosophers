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

void    *monitor_philos(t_table *table)
{
    int i;
    int total_dead;

    total_dead = 0;
    while (1)
    {
        i = 0;
        while (i < table->n_philo)
        {
            pthread_mutex_lock(&table->eating);
            if (get_time() - table->philos[i].last_meal >= table->t_die)
            {
                table->philos[i].status = DEAD;
                if (table->philos[i].status == DEAD)
                    total_dead++;
                print_action(&table->philos[i], "died\n", UNLOCK);
            }
            pthread_mutex_unlock(&table->eating);
            i++;
        }
        if (total_dead == table->n_philo)
            break ;
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
    if (pthread_create(&table->monitor, NULL, &monitor_philos, table))
        exit_error_free("Error: pthread_create\n", table);
}