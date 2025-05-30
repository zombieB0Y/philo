/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoentifi <zoentifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:51:14 by zoentifi          #+#    #+#             */
/*   Updated: 2025/05/30 16:02:52 by zoentifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    print_msg(size_t seat_number, char *stat)
{
    pthread_mutex_lock(&philo()->write);
    if (!is_dead())
        printf("%lld %ld %s\n", return_time() - philo()->time, seat_number, stat);
    pthread_mutex_unlock(&philo()->write);
}