#include "philosophers.h"

void    *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    //philo->table->t_die = philo->table->t_die + get_time();
    if (philo->pos % 2 == 0 && philo->table->n_philo != 1)
        go_sleep(philo, philo->table->t_eat / 2);
    while (philo->status == ALIVE && philo->n_meals != philo->table->n_meals)
    {
        if (get_time() > philo->table->t_die)
        {
            philo->status = DEAD;
            print_action(philo, "died\n", UNLOCK);
            break ;
        }
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
        if (pthread_create(&table->philos[i]->thread_id, NULL, &routine, &table->philos[i]))
            exit_error_free("Error: pthread_create\n", table);
        i++;
    }
    i = 0;
    while (i < table->n_philo)
    {
        if (pthread_join(table->philos[i]->thread_id, NULL))
            exit_error_free("Error: pthread_join\n", table);
        i++;
    }
}