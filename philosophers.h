/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:40:00 by drenquin          #+#    #+#             */
/*   Updated: 2024/10/16 14:40:00 by drenquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PHILOSOPHERS_H_
#define _PHILOSOPHERS_H_

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

/*la structure philo contiendra les donner propre a un philosophe
tandis que la structure table contiendra des donner commune a tout
les philosophes */

/*??? quelle interet a integrer la structure philo dans la structure table
et vice versa???*/

typedef struct s_table t_table;

// representation  d' un philosophe
typedef struct s_philo
{
    int                 n_philo;    //id du philosophe
    int                 odd;        //divise les philosophe 2 groupe (odd = 1 impaire) (odd = 0 paire)
    pthread_mutex_t     *l_fork;    //mutex de la fourchette du philosophe
    pthread_mutex_t     *r_fork;    //mutex de la fourchette droite du philosophe         
    pthread_t           td;         //thread du philosophe
    pthread_t           die;        //thread qui verifie la mort
    long int            last_meal;  //indique le temp du dernier repas en milliseconds
    int                 meals_eaten;
    t_table             *tb;        //???

} t_philo;

// representation de la table
typedef struct s_table
{
    int                 nb_philo;       //argv1 (???declarer les miliseconds en long ???)
    long int                tdie;       //argv2 milliseconds                  
    long int              tsleep;       //argv3 milliseconds
    long int                teat;       //argv4 milliseconds
    int                  nb_meal;       //argv5 nombre de repas a prendre par philosophe (optionelle)
    pthread_mutex_t       *forks;
    pthread_mutex_t          end;       //repas fini ou philo mort
    pthread_mutex_t        write;
    int                   is_die;       //renvoie 1 qui un philo est mort
    t_philo                  *ph;       //???
    long int           start_time;
} t_table;

int     check_in(int argc, char **argv);
int     only_num(int argc, char **argv);
int     ft_atoi(char *str);
int     overflow(int argc, char **argv);
void    init_tb(t_table *tb, char **argv);
void    init_ph(t_table *tb);
long    current_timestamp(void);
void	ft_usleep(long int time_in_ms);
void    display_table_and_philos(t_table *table); //remove at end
void    *is_dead(void *data);
void    *routine(void *arg);
int     launch_philo(t_table *tb);

#endif
