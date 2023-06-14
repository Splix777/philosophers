/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalazar <fsalazar@student.42madrid.com:>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:10:58 by fsalazar          #+#    #+#             */
/*   Updated: 2023/06/12 11:11:02 by fsalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
/*memset*/
# include <string.h>
/*printf*/
# include <stdio.h>
/*malloc, free*/
# include <stdlib.h>
/*write, usleep*/
# include <unistd.h>
/*gettimeofday*/
# include <sys/time.h>
/*pthread_creat, pthread_detach, pthread_join, pthread_mutex_init,
	pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock*/
# include <pthread.h>
/*Statuses of Philosphers*/
# define DEAD 0
# define ALIVE 1
# define FULL 2
/*Colors for printf*/
# define COLOR_RED "\x1b[31m"
# define COLOR_GREEN "\x1b[32m"
# define COLOR_BLUE "\x1b[34m"
# define COLOR_YELLOW "\x1b[33m"
# define COLOR_MAGENTA "\x1b[35m"
# define COLOR_RESET "\x1b[0m"
/*Errors*/
# define ERROR_ARGS "Error: Wrong number of arguments\nFormat: \
<number_of_philosophers> <time_to_die time_to_eat> <time_to_sleep>\
[number_of_times_each_philosopher_must_eat]\n"
# define ERROR_FORMAT "Error: Arguments must be positive integers\n"
# define ERROR_MALLOC "Error: Malloc error\n"
# define ERROR_MUTEX "Error: Mutex error\n"
# define FAILED 1
# define SUCCESS 0
/*Declaration of s_table so I can use it in s_philo*/
typedef struct s_table	t_table;
/*Philosopher Structure*/
typedef struct s_philo
{
	int					status;
	int					pos;
	int					n_meals;
	int					left_fork;
	int					right_fork;
	unsigned long		last_meal;
	pthread_t			thread_id;
	t_table				*table;
}						t_philo;
/*Table Structure*/
typedef struct s_table
{
	unsigned long		t_die;
	unsigned long		t_eat;
	unsigned long		t_sleep;
	unsigned long		t_start;
	int					n_philo;
	int					n_forks;
	int					n_meals;
	int					stop;
	int					argc;
	char				**argv;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		writing;
	pthread_mutex_t		status;
}						t_table;
// main.c
void					check_args(int argc, char **argv);
// errors_and_exits.c
void					exit_error(char *str);
void					exit_error_free(char *str, int i, t_table *table);
// utils.c
unsigned long			ft_atoi(const char *str);
unsigned long			get_time(void);
int						is_num(char *str);
int						ft_strlen(char *str);
int						ft_strcmp(char *s1, char *s2);
// set_table.c
void					init_philos(t_table *table);
void					init_mutex(t_table *table);
void					invite_philos(t_table *table);
t_table					*set_table(int argc, char **argv);
// simulation.c
void					*routine(void *arg);
void					print_dead_action(t_philo *philo, t_table *table,
							char *str);
void					monitor_philos(t_table *table, int i, int full);
void					start_sim(t_table *table);
void					end_sim(t_table *table, int i, int status);
// actions2.c
void					go_sleep(t_philo *philo, unsigned long time);
void					is_eating(t_philo *philo, unsigned long time);
// actions.c
void					go_eat(t_philo *philo, t_table *table);
void					print_action(t_philo *philo, t_table *table, char *str);
void					pick_up_forks(t_philo *philo, t_table *table);
void					put_down_forks(t_philo *philo, t_table *table);

#endif
