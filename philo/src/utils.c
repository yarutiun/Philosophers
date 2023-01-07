#include "../inc/philo.h"

int	ft_atoi(const char *str)
{
	unsigned int	num;
	int				i;
	int				ifminus;

	ifminus = 1;
	i = 0;
	num = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\f' || \
		str[i] == '\r' || str[i] == '\n' || \
		str[i] == '\v' )
	{
		i++;
	}
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			ifminus = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(ifminus * num));
}

//function returns the time of the day since 00:00:00, January 1, 1970 in milliseconds
time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	if(gettimeofday(&tv, NULL) == -1)
	{
		printf("Time is just an illusion... Something went wrong!");
		exit(EXIT_FAILURE);
	}
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void print_action(data_t *philo, int id, char *msg)
{
	if(!philo->dead)
	{
		pthread_mutex_lock(&philo->print_msg);
		printf("%lld ", get_time_in_ms() - philo->beggining_of_simulation);
		printf("%i ", id);
		printf("%s\n", msg);
		pthread_mutex_unlock(&philo->print_msg);
	}
}

long long int get_diff(long long int now, long long int prev)
{
	return(now - prev);
}

void sleep_eating(data_t *philo)
{
	long long int time_from_fall_sleep;
	time_from_fall_sleep = get_time_in_ms();
	while(philo->dead != 1)
	{
		if(get_diff(get_time_in_ms(), time_from_fall_sleep) >= philo->time_to_eat)
		printf("\n %lld\n", get_diff(get_time_in_ms(), time_from_fall_sleep));
			break;
		sleep(50);
	}
	return ;
}

void sleep_sleeping(data_t *philo)
{
	int time_from_fall_sleep;
	time_from_fall_sleep = get_time_in_ms();
	while(philo->dead != 1)
	{
		if(get_diff(get_time_in_ms(), time_from_fall_sleep) >= philo->time_to_sleep)
			break;
		sleep(50);
	}
	return ;
}