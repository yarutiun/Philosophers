/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yarutiun <yarutiun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 21:18:58 by yarutiun          #+#    #+#             */
/*   Updated: 2023/01/10 21:24:35 by yarutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ultra_death(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->data_dog);
	if (data->dead == 1)
	{
		pthread_mutex_unlock(&data->data_dog);
		pthread_mutex_unlock(&(data->forks[philo->left_fork_id]));
		return (1);
	}
	pthread_mutex_unlock(&data->data_dog);
	return (0);
}

int	ultra_super_death(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->data_dog);
	if (data->dead == 1)
	{
		pthread_mutex_unlock(&data->data_dog);
		pthread_mutex_unlock(&(data->forks[philo->right_fork_id]));
		pthread_mutex_unlock(&(data->forks[philo->left_fork_id]));
		return (1);
	}
	pthread_mutex_unlock(&data->data_dog);
	return (0);
}

void	i_am_sry_future_self(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->data_dog);
	(philo->times_ate)++;
	pthread_mutex_unlock(&data->data_dog);
	pthread_mutex_unlock(&(data->forks[philo->left_fork_id]));
	pthread_mutex_unlock(&(data->forks[philo->right_fork_id]));
}
