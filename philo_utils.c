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


void *is_dead(void *data)
{
    t_philo *ph = (t_philo *)data;

    // Attendre le temps défini pour mourir
    ft_usleep(ph->tb->tdie);

    // Verrouiller avant de vérifier les données partagées
    pthread_mutex_lock(&ph->tb->end);

    // Vérifier si le philosophe a dépassé son temps avant de manger
    if ((current_timestamp() - ph->last_meal) >= ph->tb->tdie && ph->tb->is_die == 0)
    {
        //printf("%ld %d is died\n", relative_timestamp(ph->tb), ph->n_philo);
        lock_msg(ph, "is died");
        ph->tb->is_die = 1;
        pthread_mutex_unlock(&ph->tb->end);
        return NULL;
    }
    // Déverrouiller après vérification
    pthread_mutex_unlock(&ph->tb->end);
    return NULL;
}
void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    long start_time = current_timestamp();

    // Délai initial pour les philosophes pairs
    if (philo->n_philo % 2 == 0)
        ft_usleep(10);
    // Lancer le thread de surveillance de la mort
    if (pthread_create(&philo->die, NULL, is_dead, (void *)philo) != 0)
    {
        printf("Error creating death checker thread for philosopher %d\n", philo->n_philo);
        return NULL;
    }
    pthread_detach(philo->die);
    while (check_if_dead(philo))
    {
        pthread_mutex_unlock(&philo->tb->end);
        take_forks(philo, start_time);
        sleeping(philo, start_time);
        thinking(philo, start_time);
    }
    return NULL;
}
/*void    take_forks(t_philo *philo, long start_time)
{
    pthread_mutex_lock(&philo->tb->end);
    if (philo->tb->is_die)
    {
        pthread_mutex_unlock(&philo->tb->end);
        return;
    }
    pthread_mutex_unlock(&philo->tb->end);
    if (philo->n_philo % 2 == 1) // Philosophe impair
    {
        pthread_mutex_lock(philo->l_fork);
        printf("%ld %d has taken a fork (left)\n", current_timestamp() - start_time, philo->n_philo);

        pthread_mutex_lock(philo->r_fork);
        printf("%ld %d has taken a fork (right)\n", current_timestamp() - start_time, philo->n_philo);
        printf("%ld %d is eating\n", current_timestamp() - start_time, philo->n_philo);
        ft_usleep(philo->tb->teat);
    }
    else // Philosophe pair
    {
        pthread_mutex_lock(philo->r_fork);
        printf("%ld %d has taken a fork (right)\n", current_timestamp() - start_time, philo->n_philo);

        pthread_mutex_lock(philo->l_fork);
        printf("%ld %d has taken a fork (left)\n", current_timestamp() - start_time, philo->n_philo);
        pthread_mutex_lock(&philo->tb->eating);
        printf("%ld %d is eating\n", current_timestamp() - start_time, philo->n_philo);
        ft_usleep(philo->tb->teat);
    }
    pthread_mutex_unlock(&philo->tb->eating);
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
    philo->last_meal = current_timestamp();
    return;
}*/
/*void take_forks(t_philo *philo, long start_time)
{
    if (philo->n_philo % 2 == 1 && check_if_dead(philo)) // Philosophe impair
    {
        pthread_mutex_lock(philo->l_fork);
        printf("%s%ld %d has taken a fork (left)%s\n", COLOR_YELLOW, current_timestamp() - start_time, philo->n_philo, COLOR_RESET);

        pthread_mutex_lock(philo->r_fork);
        printf("%s%ld %d has taken a fork (right)%s\n", COLOR_YELLOW, current_timestamp() - start_time, philo->n_philo, COLOR_RESET);

        //pthread_mutex_lock(&philo->tb->eating);
        printf("%s%ld %d is eating%s\n", COLOR_GREEN, current_timestamp() - start_time, philo->n_philo, COLOR_RESET);
        ft_usleep(philo->tb->teat);
    }
    else if (check_if_dead(philo)) // Philosophe pair
    {
        pthread_mutex_lock(philo->r_fork);
        printf("%s%ld %d has taken a fork (right)%s\n", COLOR_YELLOW, current_timestamp() - start_time, philo->n_philo, COLOR_RESET);

        pthread_mutex_lock(philo->l_fork);
        printf("%s%ld %d has taken a fork (left)%s\n", COLOR_YELLOW, current_timestamp() - start_time, philo->n_philo, COLOR_RESET);

        //pthread_mutex_lock(&philo->tb->eating);
        printf("%s%ld %d is eating%s\n", COLOR_GREEN, current_timestamp() - start_time, philo->n_philo, COLOR_RESET);
        ft_usleep(philo->tb->teat);
    }
    //pthread_mutex_unlock(&philo->tb->eating);
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
    philo->last_meal = current_timestamp();
    return;
}*/
void take_forks(t_philo *philo, long start_time)
{
    pthread_mutex_lock(&philo->tb->end);
    if (philo->tb->is_die)
    {
        pthread_mutex_unlock(&philo->tb->end);
        return;
    }
    pthread_mutex_unlock(&philo->tb->end);
    if (philo->n_philo % 2 == 1) // Philosophe impair
    {
        pthread_mutex_lock(philo->l_fork);
        lock_msg(philo, "has taken a fork (left)");

        pthread_mutex_lock(philo->r_fork);
        lock_msg(philo, "has taken a fork (right)");

        lock_msg(philo, "is eating");
        ft_usleep(philo->tb->teat);
    }
    else // Philosophe pair
    {
        pthread_mutex_lock(philo->r_fork);
        lock_msg(philo, "has taken a fork (right)");

        pthread_mutex_lock(philo->l_fork);
        lock_msg(philo, "has taken a fork (left)");

        lock_msg(philo, "is eating");
        ft_usleep(philo->tb->teat);
    }

    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
    philo->last_meal = current_timestamp();
}
void    sleeping(t_philo *philo, long start_time)
{
    pthread_mutex_lock(&philo->tb->end);
    if (philo->tb->is_die)
    {
        pthread_mutex_unlock(&philo->tb->end);
        return;
    }
    pthread_mutex_unlock(&philo->tb->end);
    lock_msg(philo, "is sleeping");
    ft_usleep(philo->tb->tsleep);
    return;
}
void thinking(t_philo *philo, long start_time)
{
    pthread_mutex_lock(&philo->tb->end);
    if (philo->tb->is_die)
    {
        pthread_mutex_unlock(&philo->tb->end);
        return;
    }
    pthread_mutex_unlock(&philo->tb->end);
    lock_msg(philo, "is thinking");
    return;
}



