/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yarutiun <yarutiun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:13:38 by yarutiun          #+#    #+#             */
/*   Updated: 2023/01/10 21:18:55 by yarutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long long int	get_diff(long long int now, long long int prev)
{
	return (now - prev);
}

void	*one_case(void *info)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)info;
	data = philo->rules;
	pthread_mutex_lock(&(data->forks[philo->left_fork_id]));
	printf("%lld %i took a left fork\n", \
	(get_time_in_ms() - data->beggining_of_simulation), \
	philo->index_of_philo + 1);
	pthread_mutex_unlock(&(data->forks[philo->left_fork_id]));
	usleep(data->time_to_die * 1000);
	print_action(data, 0, "died");
	return (0);
}

void	death_loop(t_data *data)
{
	int		i;
	t_philo	*philo;

	philo = data->philosopher;
	i = 0;
	while (i <= data->number_philo)
	{
		pthread_mutex_lock(&data->smth);
		if (philo[i].t_last_meal != 0 && \
		get_diff(get_time_in_ms(), philo[i].t_last_meal) \
		> data->time_to_die)
		{
			print_action(data, i, "died\n");
			pthread_mutex_lock(&data->data_dog);
			data->dead = 1;
			pthread_mutex_unlock(&data->data_dog);
			pthread_mutex_unlock(&data->smth);
			break ;
		}
	i++;
		pthread_mutex_unlock(&data->smth);
		usleep(50);
	}
}

int	for_norme_checker(t_philo *philo)
{
	t_data	*info;

	info = philo->rules;
	pthread_mutex_lock(&info->protect_food);
	if (philo->times_ate == info->num_of_eats)
	{
		pthread_mutex_unlock(&info->protect_food);
		pthread_mutex_lock(&info->omg);
		info->philos_done_eating += 1;
		pthread_mutex_unlock(&info->omg);
		return (0);
	}
	pthread_mutex_unlock(&info->protect_food);
	return (1);
}

int	for_one(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->protect_philo);
	if (data->number_philo == 1)
	{
		pthread_mutex_unlock(&data->protect_philo);
		pthread_create(&(philo[0].thread_id), NULL, one_case, &(philo[0]));
		pthread_join(philo[0].thread_id, NULL);
		return (0);
	}
	pthread_mutex_unlock(&data->protect_philo);
	return (1);
}
