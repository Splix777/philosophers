#include "philosophers.h"

void	go_eat(t_philo *philo, t_table *table)
{
    pthread_mutex_lock(&table->forks[philo->right_fork]);
    print_action(philo, table, "has taken a fork\n");
    pthread_mutex_lock(&table->forks[philo->left_fork]);
    print_action(philo, table, "has taken a fork\n");
    pthread_mutex_lock(&table->serving);
    print_action(philo, table, "is eating\n");
    pthread_mutex_unlock(&table->serving);
    philo->last_meal = get_time();
    is_eating(philo, table->t_eat);
    pthread_mutex_unlock(&table->forks[philo->right_fork]);
    pthread_mutex_unlock(&table->forks[philo->left_fork]);
    philo->n_meals++;
}

void	print_action(t_philo *philo, t_table *table, char *str)
{
    unsigned long	time;

    time = get_time() - table->t_start;
    pthread_mutex_lock(&table->writing);
    if (ft_strcmp(str, "is eating\n") == 0)
        printf(COLOR_GREEN);
    else if (ft_strcmp(str, "is sleeping\n") == 0)
        printf(COLOR_BLUE);
    else if (ft_strcmp(str, "is thinking\n") == 0)
        printf(COLOR_YELLOW);
    else if (ft_strcmp(str, "died\n") == 0)
        printf(COLOR_RED);
    if (philo->status == ALIVE && !(table->stop))
        printf("%lu %d %s", time, philo->pos, str);
    if (ft_strcmp(str, "died\n") == 0)
        philo->status = DEAD;
    printf(COLOR_RESET);
    pthread_mutex_unlock(&table->writing);
}

void	go_sleep(t_philo *philo, unsigned long time)
{
    unsigned long	start;
    
    start = get_time();
    usleep(time * 1000);
    while (philo->status == ALIVE)
    {
        if ((get_time() - start) >= time)
            break ;
    }
}

void	is_eating(t_philo *philo, unsigned long time)
{
    unsigned long	start;
    
    start = get_time();
    usleep(time * 1000);
    while (philo->status == ALIVE)
    {
        if ((get_time() - start) >= time)
            break ;
    }
}

unsigned long	get_time(void)
{
    struct timeval	t;

    gettimeofday(&t, NULL);
    return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}
