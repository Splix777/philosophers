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
/*Statuses of Philosphers*/
# define DEAD 0
# define ALIVE 1
# define FULL 2
/*LOCK/UNLOCK for writting*/
# define LOCK 0
# define UNLOCK 1
/*Colors for printf*/
#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_RESET "\x1b[0m"
/*Declaration of s_table so I can use it in s_philo*/
typedef struct s_table t_table;
/*Philosopher Structure*/
typedef struct s_philo
{
    int             status;
    int             pos;
    int             n_meals;    
    int             left_fork;
    int             right_fork;
    unsigned long   last_meal;
    pthread_t       thread_id;
    t_table         *table;
}               t_philo;
/*Table Structure*/
typedef struct s_table
{
    unsigned long   t_die;
    unsigned long   t_eat;
    unsigned long   t_sleep;
    unsigned long   t_start;
    int             n_philo;
    int             n_forks;
    int             n_meals;
    int             stop;
    int             argc;
    char            **argv;
    t_philo         *philos;
    pthread_mutex_t *forks;
    pthread_mutex_t writing;
    pthread_mutex_t eating;
}               t_table;

// utils.c
void            print_action(t_philo *philo, char *str);
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
void            start_sim(t_table *table);
void            monitor_philos(t_table *table);
void            *routine(void *arg);

#endif