#include "philosophers.h"

void    exit_error(char *str)
{
    write(2, &str, ft_strlen(str));
    exit(1);
}
