/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yarutiun <yarutiun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:39:51 by yarutiun          #+#    #+#             */
/*   Updated: 2023/01/09 20:49:20 by yarutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct philo_s
{
    int             index_of_philo;
    int	            left_fork_id;
	int	            right_fork_id;
    int             times_ate;
	long long	    t_last_meal;
    struct data_s	*rules;
    pthread_t       thread_id;  
} philo_t;


//Inside philo routine 
//After philo->times_ate == data->num_of_eats
//end the thread 

//Death check
//While(allthephilo[i])
// get_diff(get_time_in_ms(), philo[i].t_last_meal) >= data->time_to_die
// 

// data->dead = 1 == mutex

// inside philo before printing check if data->dead == 1
// Exit philo (end thread)



//dead = 0 if none of philosophers are dead, 1 if someone died
typedef struct data_s
{
    int             number_philo;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             num_of_eats;
    int             philos_done_eating;
    long long int   beggining_of_simulation;
    int             dead;
    pthread_mutex_t for_death_checker;
    pthread_mutex_t print_msg;
    pthread_mutex_t another_msg;
    pthread_mutex_t smth;
    pthread_mutex_t data_dog;
    pthread_mutex_t omg;
    pthread_mutex_t protect_food;
    pthread_mutex_t forks[200];
    philo_t         philosopher[200];
} data_t;

//   __________------parser------___________   //
int parse(data_t *philo, int argc, char **argv);
int assign_forks_and_philo(data_t *philo);
int assign_philo_threads(data_t *philo);



//   __________------executor------___________   //
// int exec(data_t *philo);
int death_checker(data_t *philo);
int execu(data_t *philo);
void *do_routine(void *philo1);
int eating(philo_t *philo);
int finish(philo_t *philo, data_t *data);

//   __________------utils------___________   //
int	ft_atoi(const char *str);
long long	get_time_in_ms(void);
long long int get_diff(long long int now, long long int prev);
void print_action(data_t *philo, int id, char *msg);
void sleep_eating(data_t *philo);
void sleep_sleeping(data_t *philo);
#endif