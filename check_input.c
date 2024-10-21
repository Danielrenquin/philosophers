/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:40:23 by drenquin          #+#    #+#             */
/*   Updated: 2024/10/16 14:40:23 by drenquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

int     check_in(int argc, char **argv)
{
    if ((argc == 5) || (argc == 6))
    {
        if(only_num(argc, argv) || overflow(argc, argv))
            return (1);
        return (0);
    }
    else
        return (1);
}
// cette fonction parcours l' ensemble des argument afin de verifier qu' il s' agit bien de chiffre
int     only_num(int argc, char **argv)
{
    int i;
    int j;

    i = 1;
    j = 0;
    while (i < argc)
    {
        while (argv[i][j])
        {
            if (argv[i][j] < 48 || argv[i][j] > 57)
                return (1);
            j++;
        }
        j = 0;
        i++;    
    }
    return (0);
}
// convertit mes argument en int
int    ft_atoi(char *str)
{
    int result;

    result = 0;
    while(*str >= 48 && *str <= 57)
    {
        result = result * 10 + (*str - 48);
        str++;
    }
    return(result);
}
//verifie si aucun des argument va depasser la valeur d' un int
int     overflow(int argc, char **argv)
{
    long int result;
    int i;
    int j;

    result = 0;
    i = 1;
    j = 0;
    while (i < argc)
    {
        while (argv[i][j])
        {
            result = result * 10 + (argv[i][j] - 48);
            j++;
        }
        if (result > 2147483647 || result <= 0)
            return (1);
        i++;
        j = 0;
        result = 0;
    }
    return (0);
}

