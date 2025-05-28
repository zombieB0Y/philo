/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoentifi <zoentifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:57:36 by zoentifi          #+#    #+#             */
/*   Updated: 2025/05/28 21:09:16 by zoentifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long i = 0;
pthread_mutex_t i_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t time_mutex = PTHREAD_MUTEX_INITIALIZER;

t_status *philo(void)
{
	static t_status status;
	return (&status);
}

int main(int argc, char **argv)
{
	t_philo	*arg;

	arg = init_status(argv);
	(void)argc;
	t_philosophers	*table;

	table = init_table();
	if (!table)
		return (1);
	i = return_time();
	start_the_simulation(table, arg);
	gc_collect();
	pthread_mutex_destroy(&philo()->meal);
	pthread_mutex_destroy(&philo()->death);
	
	return (0);
}
