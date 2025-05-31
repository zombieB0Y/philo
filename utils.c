/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zm <zm@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:05:52 by zoentifi          #+#    #+#             */
/*   Updated: 2025/05/31 04:21:41 by zm               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	return_time(void)
{
	t_timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
void	assign_next_fork(t_philosophers *table, size_t ID)
{
	if (ID + 1 == table->size)
		table->seats_array[ID].next_fork = table->seats_array[0].my_fork;
	table->seats_array[ID].next_fork = table->seats_array[ID + 1].my_fork;
}