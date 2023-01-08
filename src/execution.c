/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yarutiun <yarutiun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:27:52 by yarutiun          #+#    #+#             */
/*   Updated: 2023/01/08 16:34:22 by yarutiun         ###   ########.fr       */
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
        if(pthread_create(&(philo[i].thread_id), NULL, do_routine, &(philo[i])) != 0)
        {
            printf("There was a problem creating threads");
            return(1);
        }
        i++;
    }
    // death_checker(data);
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
        if(info->already_eated == 1)
            break;
        // function to eat and assign new valuje to amount of eats
        print_action(info, philo->index_of_philo, "is sleeping\n");
        sleep_sleeping(info);
        //function to sleep
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
    // pthread_mutex_unlock(&data->print_msg);
    philo->t_last_meal = get_time_in_ms();
    sleep_eating(data);
    pthread_mutex_lock(&data->another_msg);
    (philo->times_ate)++;
    pthread_mutex_unlock(&data->another_msg);
    pthread_mutex_unlock(&(data->forks[philo->left_fork_id]));
    pthread_mutex_unlock(&(data->forks[philo->right_fork_id]));
    return(0);
}

// int death_checker(data_t *philo)
// {
//     int i = 0;
//     while((philo->already_eated != philo->num_of_eats) || philo->dead != 1)
//     {
//         while(i <= philo->number_philo)
//         {
//         if(get_diff(get_time_in_ms(),philo->philosopher[i].t_last_meal) >= philo->time_to_die)
//         {
//             pthread_mutex_lock(&philo->for_death_checker);
//             print_action(philo, i, "died");
//             pthread_mutex_unlock(&philo->for_death_checker);
//             philo->dead = 1;
//         }
//         i++;
//         usleep(50);
//         }
//         if (philo->dead)
// 	        break ;
//     }
//     return(0);
// }

int finish(philo_t *philo, data_t *data)
{
    int i = 0;
    while (i < data->number_philo) //for 3 philo
    {
        pthread_join(philo[i].thread_id, NULL);
        i++;
    }
    // while (i < data->number_philo) //for 3 philo
    // {
    //     pthread_mutex_destroy(&data->forks[i]);
    //     i++;
    // }
    return(0);
}
