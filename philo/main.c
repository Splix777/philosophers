#include "philosophers.h"

int main(int argc, char **argv)
{
    t_table   *table;

    table = NULL;
    if (argc != 5 && argc != 6)
        exit_error("Wrong number of arguments");
    check_args(argc, argv);
    table = set_table(argc, argv);
    start_sim(table);
    end_sim(table);
    printf("Simulation ended\n");
    return (0);
}