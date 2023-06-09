#include "philosophers.h"

void	check_args(int argc, char **argv)
{
    int	i;

    i = 1;
    while (i < argc)
    {
        if (!is_num(argv[i]))
            exit_error(ERROR_FORMAT);
        i++;
    }
}

int	main(int argc, char **argv)
{
    t_table	*table;

    table = NULL;
    if (argc != 5 && argc != 6)
        exit_error(ERROR_ARGS);
    check_args(argc, argv);
    table = set_table(argc, argv);
    start_sim(table);
    end_sim(table, table->n_philo - 1, SUCCESS);
}