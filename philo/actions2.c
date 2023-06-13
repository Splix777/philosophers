#include "philosophers.h"

void	go_sleep(t_philo *philo, unsigned long time)
{
	unsigned long	start;
	(void) philo;

	start = get_time();
	usleep(time * 1000);
	while (1)
	{
		if ((get_time() - start) >= time)
			break ;
	}
}

void	is_eating(t_philo *philo, unsigned long time)
{
	unsigned long	start;
	(void) philo;

	start = get_time();
	usleep(time * 1000);
	while (1)
	{
		if ((get_time() - start) >= time)
			break ;
	}
}
