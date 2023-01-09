/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yarutiun <yarutiun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:27:52 by yarutiun          #+#    #+#             */
/*   Updated: 2023/01/09 15:17:25 by yarutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int execu(data_t *data)
{
    philo_t *philo;
    philo = data->philosopher;
    int i = 0;
    data->beggining_of_simulation = get_time_in_ms();
    while(i < data->number_philo)
    {
        philo->t_last_meal = get_time_in_ms();
        i++;
    }
    i = 0;
    while(i < data->number_philo)
    {
        if(pthread_create(&(philo[i].thread_id), NULL, do_routine, &(philo[i])) != 0)
        {
            printf("There was a problem creating threads");
            return(1);
        }
        i++;
    }
    death_checker(data);
    finish(philo, data);
    return(0);
}

void *do_routine(void *philo1)
{
    philo_t *philo;
    philo = (philo_t *)philo1;
    data_t *info;
    info = philo->rules;
    if (philo->index_of_philo % 2)
	    usleep(15000);
    while(info->dead != 1)
    {
        eating(philo);
        // function to eat and assign new value to amount of eats
        if(info->dead == 1)
            break;
        print_action(info, philo->index_of_philo, "is sleeping\n");
        if(info->dead == 1)
            break;
        sleep_sleeping(info);
        //function to sleep
        if(info->dead == 1)
            break;
        print_action(info, philo->index_of_philo, "is thinking\n");
        // function to think
    }
    return(0);
}

int eating(philo_t *philo)
{
    data_t *data;
    data = philo->rules;
    pthread_mutex_lock(&(data->forks[philo->left_fork_id]));
    printf("%lld %i took a left fork\n", (get_time_in_ms() - data->beggining_of_simulation), philo->index_of_philo);
    pthread_mutex_lock(&(data->forks[philo->right_fork_id]));
    printf("%lld %i took a right fork\n",(get_time_in_ms() - data->beggining_of_simulation), philo->index_of_philo);
    print_action(data, philo->index_of_philo, "eating\n");
    philo->t_last_meal = get_time_in_ms();
    sleep_eating(data);
    pthread_mutex_lock(&data->another_msg);
    (philo->times_ate)++;
    pthread_mutex_unlock(&data->another_msg);
    pthread_mutex_unlock(&(data->forks[philo->left_fork_id]));
    pthread_mutex_unlock(&(data->forks[philo->right_fork_id]));
    return(0);
}

int death_checker(data_t *data)
{
    philo_t *philo;
    philo = data->philosopher;
    int i;
    i = 0;
    pthread_mutex_lock(&data->smth);
    while(data->dead != 1 || philo[i].times_ate != data->num_of_eats) //(data->already_eated != data->num_of_eats) || 
    {
        i = 0;
        while(i <= data->number_philo)
        {
        if(get_diff(get_time_in_ms(), philo[i].t_last_meal) >= data->time_to_die)
        {
            print_action(data, i, "died");
            pthread_mutex_lock(&data->for_death_checker);
            data->dead = 1;
            break;
        }
        i++;
        usleep(50);
        }
        // printf("           %i           \n", philo[i].times_ate);
        pthread_mutex_lock(&data->smth);
        if (data->dead)
        {
            pthread_mutex_unlock(&data->for_death_checker);            
	        break ;
        }
          pthread_mutex_unlock(&data->for_death_checker);
    }
    return(0);
}

int finish(philo_t *philo, data_t *data)
{
    int i = 0;
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
    pthread_mutex_destroy(&data->another_msg);
    pthread_mutex_destroy(&data->smth);
    pthread_mutex_destroy(&data->for_death_checker);
    pthread_mutex_destroy(&data->data_dog);
    return(0);
}
