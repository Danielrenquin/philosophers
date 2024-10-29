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
    tb->start_time = current_timestamp();
    pthread_mutex_init(&tb->end, NULL);
    pthread_mutex_init(&tb->eating, NULL);
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
    while (i < tb->nb_philo)
    {
        if (pthread_mutex_init(&tb->forks[i], NULL) != 0)
            return ;
        tb->ph[i].n_philo = i + 1;
        tb->ph[i].last_meal = current_timestamp(); // a mettre apres la creation de tout les thread???
        tb->ph[i].odd = i % 2;
        tb->ph[i].tb = tb;
        tb->ph[i].l_fork = &tb->forks[i];
        tb->ph[i].r_fork = &tb->forks[(i + 1) % tb->nb_philo];
        tb->ph[i].meals_eaten = 0; 
        i++;
    }
    return ;
}
// La fonction actual_time renvoie donc le nombre total
//de millisecondes écoulées depuis le 1er janvier 1970 (l'époque Unix), 
//en combinant les secondes et microsecondes fournies par gettimeofday.
long current_timestamp(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL); // Récupère le temps actuel

    // Convertit les secondes et microsecondes en millisecondes
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}
//La fonction standard usleep fait une pause
// pour au minimum le temps indiqué en microsecondes,
// mais en réalité, le temps de pause peut être plus long.
// Cela peut être dû à des facteurs comme
// la precision de l' horloge systeme
//la gestion des processus
void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = current_timestamp();
	while ((current_timestamp() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}
int     launch_philo(t_table *tb)
{
    int i;

    i = 0;
    while(i < tb->nb_philo)
    {
        if(pthread_create(&tb->ph[i].td, NULL, routine, (void *)&tb->ph[i]) != 0)
        {
            printf("Error creating philosopher thread\n");
            return (1);
        }
        i++;
    }
    while (tb->is_die == 0)
    {
        if(tb->is_die ==  1)
            break;
    }
    i = 0;
    while (i < tb->nb_philo)
    {
        pthread_join(tb->ph[i].td, NULL);
        i++;
    }
     
    return (0);
}




