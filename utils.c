/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoentifi <zoentifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:05:52 by zoentifi          #+#    #+#             */
/*   Updated: 2025/05/28 21:10:06 by zoentifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long    return_time(void)
{
    t_timeval   tv;

    pthread_mutex_lock(&time_mutex);
    if ((gettimeofday(&tv, NULL)) != 0)
        return (0);
    pthread_mutex_unlock(&time_mutex);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}