#include "philosophers.h"

int main(int argc, char **argv)
{
    t_table   *table;

    if (argc != 5 && argc != 6)
        exit_error("Wrong number of arguments");
    check_args(argc, argv);
    set_table(table, argc, argv);
    invite_philos(table);
    start_sim(table);
}