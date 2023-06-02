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

typedef struct s_table
{
    int             n_philo;
    int             n_forks;
    int             n_meals;
    int             t_die;
    int             t_eat;
    int             t_sleep;    
    int             argc;
    int long        t_start;
    char            **argv;
    t_philo         *philos;
    pthread_mutex_t *forks;
    pthread_mutex_t writing;
    pthread_mutex_t eating;
}               t_table;

typedef struct s_philo
{
    int         status;
    int         pos;
    int         n_meals;
    int         last_meal;
    int         left_fork;
    int         right_fork;
    pthread_t   thread_id;
    t_table     *table;
}               t_philo;

// utils.c
int     ft_atoi(char *str);
int     is_num(char *str);
// errors_and_exit.c
void    exit_error(char *str);
// main.c



#endif