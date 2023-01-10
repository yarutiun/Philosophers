/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yarutiun <yarutiun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:13:41 by yarutiun          #+#    #+#             */
/*   Updated: 2023/01/10 13:18:12 by yarutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

//function returns the time of the day since 00:00:00, 
//January 1, 1970 in milliseconds
long long	get_time_in_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		printf("Time is just an illusion... Something went wrong!");
		return (0);
	}
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_action(t_data *philo, int id, char *msg)
{
	pthread_mutex_lock(&philo->data_dog);
	if (philo->dead == 1)
	{
		pthread_mutex_unlock(&philo->data_dog);
		return ;
	}
	pthread_mutex_unlock(&philo->data_dog);
	pthread_mutex_lock(&philo->another_msg);
	printf("%lld ", get_time_in_ms() - philo->beggining_of_simulation);
	printf("%i ", id + 1);
	printf("%s", msg);
	pthread_mutex_unlock(&philo->another_msg);
}

void	sleep_eating(t_data *philo)
{
	long long int	time_from_fall_sleep;

	time_from_fall_sleep = get_time_in_ms();
	pthread_mutex_lock(&philo->data_dog);
	while (philo->dead != 1)
	{
		pthread_mutex_unlock(&philo->data_dog);
		if (get_diff(get_time_in_ms(), time_from_fall_sleep) \
		>= philo->time_to_eat)
		{
			return ;
		}
		usleep(50);
	}
	pthread_mutex_unlock(&philo->data_dog);
}

void	sleep_sleeping(t_data *philo)
{
	long long int	time_from_fall_sleep;

	time_from_fall_sleep = get_time_in_ms();
	while (philo->dead != 1)
	{
		if (get_diff(get_time_in_ms(), time_from_fall_sleep) \
		>= philo->time_to_sleep)
			break ;
		usleep(50);
	}
	return ;
}
