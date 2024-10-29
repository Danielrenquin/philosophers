/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:18:49 by drenquin          #+#    #+#             */
/*   Updated: 2024/10/29 13:18:49 by drenquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

long relative_timestamp(t_table *tb)
{
    return current_timestamp() - tb->start_time;
}
int ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
        i++;
    return(s1[i] - s2[i]);
}
void lock_msg(t_philo *philo, char *message)
{
    pthread_mutex_lock(&philo->tb->write);

    if (philo->tb->is_die == 0)
    {
        const char *color;
        if (ft_strcmp(message, "is died") == 0)
            color = COLOR_RED;
        else if (ft_strcmp(message, "is sleeping") == 0)
            color = COLOR_CYAN;
        else if (ft_strcmp(message, "is thinking") == 0)
            color = COLOR_BLUE;
        else if (ft_strcmp(message, "has taken a fork") == 0)
            color = COLOR_BRIGHT_YELLOW;
        else if (ft_strcmp(message, "is eating") == 0)
            color = COLOR_GREEN;
        else
            color = COLOR_WHITE;
        printf("%s%ld %d %s%s\n", color, current_timestamp() - philo->tb->start_time, philo->n_philo, message, COLOR_RESET);
    }
    pthread_mutex_unlock(&philo->tb->write);
}
int check_if_dead(t_philo *philo)
{
    pthread_mutex_lock(&philo->tb->end);
    if (philo->tb->is_die)
    {
        pthread_mutex_unlock(&philo->tb->end);
        return 0; // Philosophe est mort
    }
    pthread_mutex_unlock(&philo->tb->end);
    return 1; // Philosophe est encore en vie
}

