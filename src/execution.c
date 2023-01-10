/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yarutiun <yarutiun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:27:52 by yarutiun          #+#    #+#             */
/*   Updated: 2023/01/10 16:41:32 by yarutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	execu(t_data *data)
{
	t_philo	*philo;
	int		i;

	philo = data->philosopher;
	i = 0;
	data->beggining_of_simulation = get_time_in_ms();
	if (data->number_philo == 1)
		pthread_create(&(philo[0].thread_id), NULL, one_case, &(philo[0]));
	while (++i < data->number_philo)
		philo[i].t_last_meal = get_time_in_ms();
	i = 0;
	while (i < data->number_philo && data->number_philo != 1)
	{
		if (pthread_create(&philo[i].thread_id, NULL, \
		do_routine, &philo[i]) != 0)
			return (1);
		i++;
	}
	death_checker(data);
	finish(philo, data);
	return (0);
}

void	*do_routine(void *philo1)
{
	t_philo	*philo;
	t_data	*info;

	philo = (t_philo *)philo1;
	info = philo->rules;
	if (philo->index_of_philo % 2)
		usleep(15000);
	pthread_mutex_lock(&info->data_dog);
	while (info->dead != 1)
	{
		pthread_mutex_unlock(&info->data_dog);
		eating(philo);
		print_action(info, philo->index_of_philo, "is sleeping\n");
		pthread_mutex_lock(&info->data_dog);
		pthread_mutex_unlock(&info->data_dog);
		sleep_sleeping(info);
		if (for_norme_checker(philo) == 0)
			return (0);
		print_action(info, philo->index_of_philo, "is thinking\n");
	}
	pthread_mutex_unlock(&info->data_dog);
	return (0);
}

int	eating(t_philo *philo)
{
	t_data	*data;

	data = philo->rules;
	pthread_mutex_lock(&(data->forks[philo->left_fork_id]));
	printf("%lld %i took a left fork\n", \
	(get_time_in_ms() - data->beggining_of_simulation), \
	philo->index_of_philo + 1);
	pthread_mutex_lock(&(data->forks[philo->right_fork_id]));
	printf("%lld %i took a right fork\n", \
	(get_time_in_ms() - data->beggining_of_simulation), \
	philo->index_of_philo + 1);
	print_action(data, philo->index_of_philo, "is eating\n");
	sleep_eating(data);
	pthread_mutex_lock(&data->data_dog);
	(philo->times_ate)++;
	pthread_mutex_unlock(&data->data_dog);
	pthread_mutex_unlock(&(data->forks[philo->left_fork_id]));
	pthread_mutex_unlock(&(data->forks[philo->right_fork_id]));
	pthread_mutex_lock(&data->smth);
	philo->t_last_meal = get_time_in_ms();
	pthread_mutex_unlock(&data->smth);
	return (0);
}

int	death_checker(t_data *data)
{
	// int		i;
	// t_philo	*philo;

	// philo = data->philosopher;
	// i = 0;
	while (1)
	{
		pthread_mutex_lock(&data->omg);
		if (data->philos_done_eating == data->number_philo)
		{
			pthread_mutex_unlock(&data->omg);
			return (0);
		}
		pthread_mutex_unlock(&data->omg);
		pthread_mutex_lock(&data->data_dog);
		if (data->dead == 1)
		{
			pthread_mutex_unlock(&data->data_dog);
			return (0);
		}
		pthread_mutex_unlock(&data->data_dog);
		death_loop(data);
	}
	return (0);
}

int	finish(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_philo)
	{
		pthread_join(philo[i].thread_id, NULL);
		i++;
	}
	while (i < data->number_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_msg);
	pthread_mutex_destroy(&data->omg);
	pthread_mutex_destroy(&data->another_msg);
	pthread_mutex_destroy(&data->smth);
	pthread_mutex_destroy(&data->for_death_checker);
	pthread_mutex_destroy(&data->data_dog);
	return (0);
}
