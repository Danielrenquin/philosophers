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

/*int main(int argc, char **argv)
{
    t_table table;

    // Vérifie les arguments passés en ligne de commande
    if (check_in(argc, argv) != 0)
        return (1);

    // Initialisation de la table
    init_tb(&table, argv);

    // Initialisation des philosophes
    init_ph(&table);

    // Lancement des threads pour chaque philosophe
    int i = 0;
    while (i < table.nb_philo)
    {
        if (pthread_create(&table.ph[i].td, NULL, philosopher_routine, &table.ph[i]) != 0)
        {
            fprintf(stderr, "Erreur : Impossible de créer le thread pour le philosophe %d\n", i + 1);
            return (1);
        }
        i++;
    }

    // Attendre que tous les philosophes aient terminé (bien que ici ils tournent en boucle infinie)
    i = 0;
    while (i < table.nb_philo)
    {
        if (pthread_join(table.ph[i].td, NULL) != 0)
        {
            fprintf(stderr, "Erreur : Impossible de joindre le thread du philosophe %d\n", i + 1);
            return (1);
        }
        i++;
    }

    // Détruire les mutex et libérer la mémoire
    i = 0;
    while (i < table.nb_philo)
    {
        pthread_mutex_destroy(&table.ph[i].fork);
        i++;
    }
    free(table.ph); // Libérer la mémoire allouée pour les philosophes

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
        i++;
    }

    // Attente de la fin de chaque thread
    i = 0;
    while (i < tb.nb_philo)
    {
        pthread_join(tb.ph[i].td, NULL);
        i++;
    }

    return (0);
}

