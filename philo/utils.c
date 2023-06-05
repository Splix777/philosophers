#include "philosophers.h"

int ft_atoi(char *str)
{
    int nbr;
    int sign;
    int i;

    i = 0;
    sign = 1;
    nbr = 0;
    while (str[i] != 32 && (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign *= -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        nbr = nbr * 10 + (str[i] - '0');
        i++;
    }
    return (nbr * sign);
}

void    check_args(int argc, char **argv)
{
    int i;

    i = 1;
    while (i < argc)
    {
        if (!is_num(argv[i]))
            exit_error("Arguments must be numbers");
        i++;
    }
}

int is_num(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        i++;
    }
    return (1);
}

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
        i++;
    return (i);
}

unsigned long   get_time(void)
{
    struct timeval  t;
    unsigned long   time;

    gettimeofday(&t, NULL);
    time = ((t.tv_sec * 1000) + (t.tv_usec / 1000));
    return (time);
}

void    go_sleep(t_philo *philo, unsigned long time)
{
    unsigned long   start;

    start = get_time();
    while (philo->status == ALIVE)
    {
        if (get_time() - start >= time)
            break ;
        usleep(time - 1);
    }
}

void    is_eating(t_philo *philo, unsigned long time)
{
    unsigned long   start;

    start = get_time();
    while (philo->status == ALIVE)
    {
        if (get_time() - start >= time)
            break ;
        usleep(time - 1);
    }
}

void    go_eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
    print_action(philo, "has taken a fork\n", UNLOCK);
    pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
    print_action(philo, "has taken a fork\n", UNLOCK);
    pthread_mutex_lock(&philo->table->eating);
    print_action(philo, "is eating\n", UNLOCK);
    philo->last_meal = get_time();
    is_eating(philo, philo->table->t_eat);
    pthread_mutex_unlock(&philo->table->eating);
    pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
    pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
    philo->n_meals++;
}

void    print_action(t_philo *philo, char *str, int status)
{
    unsigned long   time;

    time = get_time() - philo->table->t_start;
    pthread_mutex_lock(&philo->table->writing);
    if (philo->status == ALIVE && philo->n_meals != philo->table->n_meals)
        printf("%lu %d %s", time, philo->pos, str);
    if (status == UNLOCK)
        pthread_mutex_unlock(&philo->table->writing);
}

void    end_sim(t_table *table)
{
    int i;

    i = 0;
    while (i < table->n_philo)
    {
        pthread_join(table->philos[i].thread_id, NULL);
        i++;
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
}