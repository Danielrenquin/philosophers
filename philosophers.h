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

typedef struct s_philo
{
    int                 n_philo;    //id du philosophe
    int                 odd;        //divise les philosophe 2 groupe (odd = 1 impaire) (odd = 0 paire)
    int                 last_meal;  //1 = philosophe a manger recement  0 = il a pas manger
    pthread_mutex_t     *l_fork;    //mutex de la fourchette du philosophe
    pthread_mutex_t     *r_fork;    //mutex de la fourchette droite du philosophe         
    pthread_t           td;         //thread du philosophe
    t_table             *tb;        //???

} t_philo;

typedef struct s_table
{
    int                 nb_philo;       //argv1
    int                 tdie;           //argv2 milliseconds                  
    int                 tsleep;         //argv3 milliseconds
    int                 teat;           //argv4 milliseconds
    int                 nb_meal;        //argv5 nombre de repas a prendre par philosophe (optionelle)
    pthread_mutex_t     *forks;
    t_philo     *ph;                    //???
} t_table;

int     check_in(int argc, char **argv);
int     only_num(int argc, char **argv);
int     ft_atoi(char *str);
int     overflow(int argc, char **argv);
void    init_tb(t_table *tb, char **argv);
void    init_ph(t_table *tb);
void    display_table_and_philos(t_table *table); //remove at end
void    routine(t_philo *philo);

#endif
