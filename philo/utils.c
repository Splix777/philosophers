#include "philosophers.h"

int ft_atoi(char *str)
{
    int nbr;
    int sign;
    int i;

    i = 0;
    sign = 1;
    nbr = 0;
    while (str[i] != 32 && (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign *= -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        nbr = nbr * 10 + (str[i] - '0');
        i++;
    }
    return (nbr * sign);
}

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

int is_num(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        i++;
    }
    return (1);
}

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
        i++;
    return (i);
}