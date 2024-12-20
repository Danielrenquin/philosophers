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

//le projet ne comporte a priori pas de memory leaks
//data race a voir
int main(int argc, char **argv)
{
    t_table tb;

    if (check_in(argc, argv) == 1)
        return (1);
    init_tb(&tb, argv);         
    init_ph(&tb);
    launch_philo(&tb);
    cleanup(&tb);               
    return 0;
}


