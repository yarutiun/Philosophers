/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yarutiun <yarutiun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:50:22 by yarutiun          #+#    #+#             */
/*   Updated: 2023/01/10 14:28:45 by yarutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

//function pushes arguments from input to a struct, 
//returns 1 if only 4 arguments, 1 if 5 args, 0 if less or more than needed
int	parse(t_data *philo, int argc, char **argv)
{
	philo->philos_done_eating = 0;
	philo->dead = 0;
	if (argc == 2 && argv[1][0] == 'H' && argv[1][1] \
	== 'e' && argv[1][2] == 'l' && argv[1][3] == 'p')
	{
		printf("Program takes theese arguments:\nnumber_of_philosophers, time_to_die, time_to_eat, \
		time_to_sleep, [number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	else if (argc > 4)
	{
		philo->number_philo = ft_atoi(argv[1]);
		if (philo->number_philo > 250)
			return (0);
		philo->time_to_die = ft_atoi(argv[2]);
		philo->time_to_eat = ft_atoi(argv[3]);
		philo->time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			philo->num_of_eats = ft_atoi(argv[5]);
	}
	else if (argc < 2 || argc > 7)
		return (0);
	assign_forks_and_philo(philo);
	assign_philo_threads(philo);
	return (1);
}

//assigns forks as mutexes into a struct, 
//return 1 if there was a problem initializing a mutex, 
//0 if everything was correct
int	assign_forks_and_philo(t_data *philo)
{
	int	i;

	i = philo->number_philo - 1;
	while (i >= 0)
	{
		if (pthread_mutex_init(&philo->forks[i], NULL))
			return (1);
		i--;
	}
	pthread_mutex_init(&philo->print_msg, NULL);
	pthread_mutex_init(&philo->protect_philo, NULL);
	pthread_mutex_init(&philo->another_msg, NULL);
	pthread_mutex_init(&philo->smth, NULL);
	pthread_mutex_init(&philo->for_death_checker, NULL);
	pthread_mutex_init(&philo->data_dog, NULL);
	pthread_mutex_init(&philo->protect_food, NULL);
	pthread_mutex_init(&philo->omg, NULL);
	return (0);
}

int	assign_philo_threads(t_data *philo)
{
	int	i;

	i = 0;
	while (i <= philo->number_philo)
	{
		philo->philosopher[i].index_of_philo = i;
		philo->philosopher[i].left_fork_id = i;
		philo->philosopher[i].t_last_meal = 0;
		philo->philosopher[i].right_fork_id = i + 1;
		philo->philosopher[i].rules = philo;
		philo->philosopher[i].times_ate = 0;
		i++;
	}
		philo->philosopher[i].index_of_philo = i;
		philo->philosopher[i].left_fork_id = i;
		philo->philosopher[i].t_last_meal = 0;
		philo->philosopher[i].right_fork_id = 0;
		philo->philosopher[i].rules = philo;
		philo->philosopher[i].times_ate = 0;
	return (0);
}
