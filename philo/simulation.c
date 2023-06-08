#include "philosophers.h"

void    *routine(void *arg)
{
    t_philo *philo;
    t_table *table;

    philo = (t_philo *)arg;
    table = philo->table;
    if (!(philo->pos % 2))
        go_sleep(philo, table->t_eat);
    while (philo->status == ALIVE && !(table->stop))
    {
        go_eat(philo, table);
        print_action(philo, table, "is sleeping\n");
        go_sleep(philo, table->t_sleep);
        print_action(philo, table, "is thinking\n");
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
            if ((get_time() - table->philos[i].last_meal) > table->t_die)
            {
                print_action(&table->philos[i], table, "died\n");
                table->stop = 1;
            }
            if (table->philos[i].n_meals == table->n_meals)
            {
                table->philos[i].status = FULL;
                full++;
            }
            pthread_mutex_unlock(&table->eating);
            i++;
        }
        if (full == table->n_philo)
            table->stop = 2;
    }
}

void    start_sim(t_table *table)
{
    int             i;

    i = 0;
    table->t_start = get_time();
    while (i < table->n_philo)
    {
        if (pthread_create(&table->philos[i].thread_id, NULL, &routine,
            &table->philos[i]))
        {
            printf("Error: pthread_create failed\n");
            end_sim(table, i, FAILED);
        }
        i++;
    }
    monitor_philos(table);
}

void    end_sim(t_table *table, int i, int status)
{
    if (status == SUCCESS && table->stop == 2)
    {
        printf(COLOR_MAGENTA);
        printf("All philosophers have eaten %d times!\n", table->n_meals);
    }
    while (i >= 0)
    {
        pthread_join(table->philos[i].thread_id, NULL);
        i--;
    }
    pthread_mutex_destroy(&table->writing);
    pthread_mutex_destroy(&table->eating);
    i = 0;
    while (i < table->n_philo)
    {
        pthread_mutex_destroy(&table->forks[i]);
        i++;
    }
    free(table->forks);
    free(table->philos);
    free(table);
    exit(status);
}