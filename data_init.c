/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:06:51 by drenquin          #+#    #+#             */
/*   Updated: 2024/10/17 17:06:51 by drenquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

//fonction pour initialiser les valeurs de la structure table
void    init_tb(t_table *tb, char **argv)
{
    tb->nb_philo = ft_atoi(argv[1]);
    tb->tdie = ft_atoi(argv[2]);
    tb->teat = ft_atoi(argv[3]);
    tb->tsleep = ft_atoi(argv[4]);
    tb->is_die = 0;
    if(argv[5])
        tb->nb_meal = ft_atoi(argv[5]);
    else
        tb->nb_meal = -1;
}

//fonction qui initialise les philosophe
//initialiser les fourchette et attribue
//la fourchette gauche et droite a chaque philosophe 
void    init_ph(t_table *tb)
{
    int i;

    i = 0;
    tb->ph = malloc(sizeof(t_philo) * tb->nb_philo);
    if (tb->ph == NULL)
        return ;
    tb->forks = malloc(sizeof(pthread_mutex_t) * tb->nb_philo);
    if (tb->forks == NULL)
        return ;
    tb->end = malloc(sizeof(pthread_mutex_t)* tb->nb_philo);
    if (tb->end == NULL)
        return ;
    while (i < tb->nb_philo)
    {
        if (pthread_mutex_init(&tb->end[i], NULL) != 0)
            return;
        if (pthread_mutex_init(&tb->forks[i], NULL) != 0)
            return ;
        tb->ph[i].n_philo = i + 1;
        tb->ph[i].last_meal = current_timestamp();
        tb->ph[i].odd = i % 2;
        tb->ph[i].tb = tb;
        tb->ph[i].l_fork = &tb->forks[i];
        tb->ph[i].r_fork = &tb->forks[(i + 1) % tb->nb_philo]; 
        i++;
    }
    return ;
}

long current_timestamp(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL); // Récupère le temps actuel

    // Convertit les secondes et microsecondes en millisecondes
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void    routine(t_philo *philo)
{
    int i = 0;
    while (i < 5) //!!!dans cette boucle definir quand le repas est fini!!!
    {
        // Le philosophe pense
        printf("%ld %d is thinking\n", current_timestamp(), philo->n_philo);
        
        // Le philosophe essaie de prendre la fourchette gauche
        pthread_mutex_lock(philo->l_fork);
        printf("%ld %d has taken a fork\n", current_timestamp(), philo->n_philo);

        // Le philosophe essaie de prendre la fourchette droite
        pthread_mutex_lock(philo->r_fork);
        printf("%ld %d has taken a fork\n", current_timestamp(), philo->n_philo);

        // Le philosophe mange
        printf("%ld %d is eating\n", current_timestamp(), philo->n_philo);
        philo->last_meal = current_timestamp(); // Met à jour le dernier temps de repas
        usleep(philo->tb->teat * 1000); // Simule le temps de manger

        // Le philosophe repose les fourchettes après avoir mangé
        pthread_mutex_unlock(philo->r_fork);
        pthread_mutex_unlock(philo->l_fork);

        // Le philosophe dort
        printf("%ld %d is sleeping\n", current_timestamp(), philo->n_philo);
        usleep(philo->tb->tsleep * 1000); // Simule le temps de dormir
        i++;
    }
}





