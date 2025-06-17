/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoentifi <zoentifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:57:36 by zoentifi          #+#    #+#             */
/*   Updated: 2025/06/17 21:50:16 by zoentifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_status *philo(void)
{
	static t_status status;
	return (&status);
}

bool	valid_args(t_philo *arg, int ac)
{
	if (ac > 5)
	{
		if (arg->n_meals <= 0)
		{
			printf("need valid arguments !\n");
			gc_collect();
			return (false);
		}
	}
	if (arg->t_to_die <= 0 || arg->n_philo <= 0)
	{
		printf("need valid arguments !\n");
		gc_collect();
		return (false);
	}
	return (true);
}

bool	simple_check(int ac)
{
	if (ac > 6)
		return (false);
	return (true);
}

void	clear_philo(void)
{
	t_seats		*tmp;

	tmp = philo()->table->head;
	pthread_mutex_destroy(&philo()->meal);
	pthread_mutex_destroy(&philo()->death);
	pthread_mutex_destroy(&philo()->write);
	while (philo()->philo->n_philo--)
	{
		pthread_mutex_destroy(&tmp->my_fork);
		tmp = tmp->next;
	}
	gc_collect();
}

int main(int argc, char **argv)
{
	t_philo	*arg;
	t_philosophers	*table = NULL;

	if (!simple_check(argc))
	{
		printf("try again !\n");
		return (1);
	}
	arg = init_status(argc, argv);
	if (!arg)
	{
		gc_collect();
		return (1);
	}
	philo()->time = return_time();
	philo()->philo = arg;
	if (!valid_args(arg, argc))
		return (1);
	if (arg->n_philo == 1)
		return (lone_philo());
	table = init_table();
	start_the_simulation(table, arg);
	clear_philo();
	return (0);
}
