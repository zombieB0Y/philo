/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoentifi <zoentifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:51:14 by zoentifi          #+#    #+#             */
/*   Updated: 2025/06/17 21:38:40 by zoentifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    print_msg(size_t seat_number, char *stat)
{
    long long   time_stamp = return_time() - philo()->time;
    if (is_dead())
        return ;
    pthread_mutex_lock(&philo()->write);
    printf("%lld %ld %s\n", time_stamp, seat_number, stat);
    pthread_mutex_unlock(&philo()->write);
}