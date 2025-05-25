/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zm <zm@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:04:49 by zm                #+#    #+#             */
/*   Updated: 2025/05/25 17:46:16 by zm               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*eat(t_seats *seat)
{
	printf("%d is eating\n", seat->seat_number);
	usleep()
	return (NULL);
}

t_seats	*create_philosopher(t_philosophers *table, int	ID)
{
	t_seats	*philosopher;

	philosopher = gc_malloc(sizeof(t_seats));
	if (!philosopher)
		return (NULL);
	philosopher->next = table->head;
	philosopher->philosopher_ID = 0;
	philosopher->seat_number = ID + 1;
	return (philosopher);
}

void	add_a_seat(t_philosophers *table, t_seats *philosopher)
{
	if (!table)
		return ;
	if (!table->head)
	{
		table->head = philosopher;
		table->tail = philosopher;
	}
	else
	{
		table->tail->next = philosopher;
		table->tail = philosopher;
	}
	table->size++;
}

void	*start(void	*arg)
{
	// int		count = 0;
	// t_philo	*philo = (t_philo *)arg;
	t_seats	*seat = (t_seats *)arg;
	while (1)
	{
		// if (count == philo->t_to_die)
		eat(seat);
	}
}

void	run(t_philosophers *table, t_philo *philo)
{
	t_seats	*curr = table->head;
	int		counter = 0;
	pthread_t	mod;
	while (counter < table->size)
	{
		pthread_create(curr->philosopher_ID, NULL, start, curr);
		curr = curr->next;
		counter++;
	}
	pthread_create(mod, NULL, moderator, table); // need a struct that have all the info needed to monitor!
}

void    start_the_simulation(t_philosophers *table, t_philo *arg)
{
	int	i;

	i = 0;
	philo()->is_dead = false;
	while (i < arg->n_philo)
	{
		add_a_seat(table, create_philosopher(table, i));
		i++;
	}
	run(table, arg);
}
