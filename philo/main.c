#include "philosophers.h"

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

void    init_philo(t_sim *sim, t_philo *philos, int argc, char **argv)
{
    sim->n_philo = ft_atoi(argv[1]);
    sim->n_forks = sim->n_philo;
    sim->argc = argc;
    sim->argv = argv;
    if (argc == 6)
        philos->n_meals = ft_atoi(argv[5]);
    else
        philos->n_meals = -1;
    philos->t_die = ft_atoi(argv[2]);
    philos->t_eat = ft_atoi(argv[3]);
    philos->t_sleep = ft_atoi(argv[4]);
    philos->left_fork = 0;
    philos->right_fork = 0;
    if (!philos->t_die || !philos->t_eat || !philos->t_sleep)
        exit_error("Time arguments must be greater than 0");
}

int main(int argc, char **argv)
{
    t_sim   *sim;
    t_philo *philos;

    if (argc != 5 && argc != 6)
        exit_error("Wrong number of arguments");
    check_args(argc, argv);
    init_philo(sim, philos, argc, argv);
}