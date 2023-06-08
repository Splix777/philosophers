#include "philosophers.h"

int ft_atoi(const char *str)
{
    unsigned long	nbr;
    int				i;

    i = 0;
    nbr = 0;
    while (str[i] != 32 && (str[i] >= 9 && str[i] <= 13))
        i++;
    while (str[i] >= '0' && str[i] <= '9')
    {
        nbr = nbr * 10 + (str[i] - '0');
        i++;
    }
    return (nbr);
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

int ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    while (s1[i] && s2[i])
    {
        if (s1[i] != s2[i])
            break ;
        i++;
    }
    return (s1[i] - s2[i]);
}
