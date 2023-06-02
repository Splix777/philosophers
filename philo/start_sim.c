#include "philosophers.h"

void    start_sim(t_table *table)
{
    int             i;
    struct timeval  t_start;

    i = 0;
    gettimeofday(table->t_start, NULL);
    table->t_start = t_start.tv_sec * 1000 + t_start.tv_usec / 1000;
    
}