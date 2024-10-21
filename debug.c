/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:18:40 by drenquin          #+#    #+#             */
/*   Updated: 2024/10/19 16:18:43 by drenquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

void display_table_and_philos(t_table *tb)
{
    int i;

    // Affichage des informations de la table
    printf("Informations de la table:\n");
    printf("Nombre de philosophes : %d\n", tb->nb_philo);
    printf("Temps avant de mourir (tdie) : %ld ms\n", tb->tdie);
    printf("Temps pour manger (teat) : %ld ms\n", tb->teat);
    printf("Temps pour dormir (tsleep) : %ld ms\n", tb->tsleep);
    printf("Nombre de repas par philosophe : %d\n", tb->nb_meal);

    printf("\n---\n\n");

    // Affichage des informations des philosophes
    printf("Informations des philosophes:\n");
    for (i = 0; i < tb->nb_philo; i++)
    {
        printf("Philosophe %d :\n", tb->ph[i].n_philo);
        printf("  Pair ou impair : %s\n", tb->ph[i].odd ? "pair" : "impair");
        printf("  A mangé récemment : %s\n", tb->ph[i].last_meal ? "Oui" : "Non");
        printf("  Adresse de la fourchette gauche : %p\n", (void *)tb->ph[i].l_fork);
        printf("  Adresse de la fourchette droite : %p\n", (void *)tb->ph[i].r_fork);
        printf("\n");
    }
}
