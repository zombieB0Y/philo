/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoentifi <zoentifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:04:49 by zm                #+#    #+#             */
/*   Updated: 2025/05/26 16:27:34 by zoentifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    start_the_simulation(t_philosophers *table, t_philo *arg)
{
	int	i;

	i = 0;
	philo()->philo = arg;
	philo()->table = table;
	philo()->is_dead = false;
	while (i < arg->n_philo)
	{
		add_a_seat(table, create_philosopher(table, i));
		i++;
	}
	run();
}
void	eat(t_seats *seat)
{
	pthread_mutex_t	*my_fork = &seat->fork;
	pthread_mutex_t	*next_fork = &seat->next->fork;
	pthread_mutex_lock(my_fork);
	pthread_mutex_lock(next_fork);
	printf("%d is eating ...\n", seat->seat_number);
	// usleep(seat->philo->t_to_eat);
	sleep(seat->philo->t_to_eat);
	pthread_mutex_unlock(my_fork);
	pthread_mutex_unlock(next_fork);
}

t_seats	*create_philosopher(t_philosophers *table, int	ID)
{
	t_seats	*philosopher;

	philosopher = gc_malloc(sizeof(t_seats));
	if (!philosopher)
		return (NULL);
	philosopher->next = table->head;
	philosopher->philosopher_ID = 0;
	pthread_mutex_init(&philosopher->fork, NULL);
	philosopher->seat_number = ID + 1;
	philosopher->philo = philo()->philo;
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

void	ft_sleep(t_seats *seat)
{
	printf("%d is sleeping ...\n", seat->seat_number);
	sleep(seat->philo->t_to_sleep);
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
		ft_sleep(seat);
	}
}

// void	*moderator(void *arg)
// {
// 	while (1)
// 	{
// 		if (philo()->is_dead)
// 			break;
// 		if (philo()->philo->)
// 	}
// }

void	run(void)
{
	t_seats	*curr = philo()->table->head;
	size_t		counter = 0;
	// pthread_t	mod;
	while (counter < philo()->table->size)
	{
		pthread_create(&curr->philosopher_ID, NULL, start, curr);
		curr = curr->next;
		counter++;
	}
	counter = 0;
	curr = philo()->table->head;
	while (counter < philo()->table->size)
	{
		pthread_join(curr->philosopher_ID, NULL);
		curr = curr->next;
		counter++;
	}
	// if (!pthread_create(mod, NULL, moderator, NULL))
	// 	return ; // need a struct that have all the info needed to monitor!
}

