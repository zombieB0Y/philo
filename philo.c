/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoentifi <zoentifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:57:36 by zoentifi          #+#    #+#             */
/*   Updated: 2025/06/17 16:06:07 by zoentifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_status *philo(void)
{
	static t_status status;
	return (&status);
}

int main(int argc, char **argv)
{
	t_philo	*arg;
	t_philosophers	*table = NULL;

	arg = init_status(argc, argv);
	if (!arg)
	{
		gc_collect();
		return (1);
	}
	philo()->philo = arg;
	if (arg->n_philo == 1)
		return (lone_philo());
	table = init_table();
	start_the_simulation(table, arg);
	gc_collect();
	pthread_mutex_destroy(&philo()->meal);
	pthread_mutex_destroy(&philo()->death);
	pthread_mutex_destroy(&philo()->write);
	
	return (0);
}
