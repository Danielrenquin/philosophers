/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:07:01 by drenquin          #+#    #+#             */
/*   Updated: 2024/10/17 13:07:01 by drenquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

/*int main(int argc, char **argv)
{
    t_table tb;

    int i;
    i = check_in(argc, argv);
    if(i == 1)
        printf("arguments non valide");
    else if(i == 0)
    {
        printf("argument valide");
        init_tb(&tb, argv);
        init_ph(&tb);
        display_table_and_philos(&tb);
    }
    return (0);
}*/

int main(int argc, char **argv)
{
    t_table tb;
    int i;

    if (check_in(argc, argv) != 0)
        return (1);

    init_tb(&tb, argv);   // Initialisation des données de la table
    init_ph(&tb);         // Initialisation des philosophes

    // Lancement des threads pour chaque philosophe
    i = 0;
    //!!!voir pour lancer tout les philosophe simultanement ???vraiment necessaire???!!!
    while (i < tb.nb_philo) 
    {
        if (pthread_create(&tb.ph[i].td, NULL, (void *(*)(void *))routine, &tb.ph[i]) != 0)
        {
            printf("Error: Failed to create thread for philosopher %d\n", i + 1);
            return (1);
        }
        if (pthread_create(&tb.ph[i].die, NULL, (void *(*)(void *))is_finish, NULL) != 0)
        {
            printf("Error: Failed to create thread for philosopher %d\n", i + 1);
            return (1);
        }
        i++;
    }

    // Attente de la fin de chaque thread
    i = 0;
    while (i < tb.nb_philo)
    {
        pthread_join(tb.ph[i].td, NULL);
        pthread_join(tb.ph[i].die, NULL);
        i++;
    }

    return (0);
}

