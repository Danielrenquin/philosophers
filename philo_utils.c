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
    usleep(ph->tb->tdie * 1000);

    // Verrouiller avant de vérifier les données partagées
    pthread_mutex_lock(&ph->tb->end);

    // Vérifier si le philosophe a dépassé son temps avant de manger
    if ((current_timestamp() - ph->last_meal) >= ph->tb->tdie)
    {
        printf("%ld %d is died\n", current_timestamp(), ph->n_philo);
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

    // Lancer le thread de surveillance de la mort
    if (pthread_create(&philo->die, NULL, is_dead, (void *)philo) != 0)
    {
        printf("Error creating death checker thread for philosopher %d\n", philo->n_philo);
        return NULL;
    }
    pthread_detach(philo->die);

    while (philo->tb->is_die == 0)
    {
        //if (philo->tb->is_die)
            //break;
        //les philosophe impaire marque un temp d' arret
        if(philo->odd != 0)
            ft_usleep(philo->tb->tdie * 100);

        // Philosophe mange (début de la boucle)
        //implementer cette partie la a part avec priorité de fourchette
        pthread_mutex_lock(philo->l_fork);
        printf("%ld %d has taken a fork\n", current_timestamp(), philo->n_philo);
        pthread_mutex_lock(philo->r_fork);
        printf("%ld %d is eating\n", current_timestamp(), philo->n_philo);

        pthread_mutex_lock(&philo->tb->end);
        philo->last_meal = current_timestamp(); // Mettre à jour le dernier repas
        pthread_mutex_unlock(&philo->tb->end);

        usleep(philo->tb->teat * 1000);

        pthread_mutex_unlock(philo->l_fork);
        pthread_mutex_unlock(philo->r_fork);

        if(philo->tb->is_die)
            break;
        // Philosophe dort
        printf("%ld %d is sleeping\n", current_timestamp(), philo->n_philo);
        usleep(philo->tb->tsleep * 1000);
        if(philo->tb->is_die)
            break;
        // Philosophe pense
        printf("%ld %d is thinking\n", current_timestamp(), philo->n_philo);
    }
    return NULL;
}


