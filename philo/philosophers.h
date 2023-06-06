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

typedef struct s_table t_table;

typedef struct s_philo
{
    int             status;
    int             pos;
    int             n_meals;
    int             last_meal;
    int             left_fork;
    int             right_fork;
    pthread_t       thread_id;
    t_table         *table;
}               t_philo;

typedef struct s_table
{
    unsigned long   t_die;
    unsigned long   t_eat;
    unsigned long   t_sleep;
    unsigned long   t_start;
    int             n_philo;
    int             n_forks;
    int             n_meals;
    int             argc;
    int             stop;
    char            **argv;
    t_philo         *philos;
    pthread_mutex_t *forks;
    pthread_mutex_t writing;
    pthread_mutex_t eating;
}               t_table;

// utils.c
void            print_action(t_philo *philo, char *str, int status);
void            go_eat(t_philo *philo);
void            is_eating(t_philo *philo, unsigned long time);
void            go_sleep(t_philo *philo, unsigned long time);
void            check_args(int argc, char **argv);
void            end_sim(t_table *table);
int             ft_atoi(char *str);
int             is_num(char *str);
int             ft_strlen(char *str);
unsigned long   get_time(void);
// errors_and_exit.c
void            exit_error(char *str);
void            free_philos(t_table *table, int i);
void            exit_error_free(char *str, t_table *table);
// set_table.c
void            init_philos(t_table *table);
void            invite_philos(t_table *table);
void             init_mutex(t_table *table);
t_table         *set_table(int argc, char **argv);
// start_sim.c
void            *routine(void *arg);
void            start_sim(t_table *table);
void            monitor_philos(t_table *table);

#endif