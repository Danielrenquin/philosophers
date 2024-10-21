/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:15:15 by drenquin          #+#    #+#             */
/*   Updated: 2024/10/21 12:15:15 by drenquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

void    is_finish(void *arg)
{   
    t_table *tb = (t_table *)arg;
    int i;
    long time;

    while (1) //!!! fin du dinner ou mort
    {
        i = 0;
        while (i < tb->nb_philo)
        {
            pthread_mutex_lock(&tb->end[i]);
            time = current_timestamp() - tb->ph[i].last_meal;
            if(time > tb->tdie)
            {
                printf("%ld %d is died\n", current_timestamp(), tb->ph[i].n_philo);
                tb->is_die = 1;
                pthread_mutex_unlock(&tb->end[i]);
                return ; 
            }
            pthread_mutex_unlock(&tb->end[i]);
            i++;
            printf("i vaut %d\n", i);
        }
        usleep(1000);
    }
}
