#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
/*memset*/
#include <string.h>
/*printf*/
#include <stdio.h>
/*malloc, free*/
#include <stdlib.h>
/*write, usleep*/
#include <unistd.h>
/*gettimeofday*/
#include <sys/time.h>
/*pthread_creat, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock*/
#include <pthread.h>

# define DEAD 0
# define ALIVE 1
# define EATING 2
# define SLEEPING 3
# define THINKING 4

# define LOCK 0
# define UNLOCK 1

typedef struct s_sim
{
    int n_philo;
    int n_forks;
    int argc;
    char **argv;
}               t_sim;

typedef struct s_philo
{
    int n_meals;
    int t_die;
    int t_eat;
    int t_sleep;
    int left_fork;
    int right_fork;
}               t_philo;

// utils.c
int     ft_atoi(char *str);
int     is_num(char *str);
// errors_and_exit.c
void    exit_error(char *str);
// main.c



#endif