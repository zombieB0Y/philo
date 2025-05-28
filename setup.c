/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoentifi <zoentifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:04:49 by zm                #+#    #+#             */
/*   Updated: 2025/05/28 21:56:07 by zoentifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	slp(int time)
{
	long long	(i) = return_time();
	while ((return_time() - i) < time)
		;
}

int	is_dead()
{
	pthread_mutex_lock(&philo()->death);
	if (philo()->is_dead)
		return (pthread_mutex_unlock(&philo()->death), 1);
	return (pthread_mutex_unlock(&philo()->death), 0);
}

long int	get_last_meal(t_seats *curr)
{
	long int last = 0;
	pthread_mutex_lock(&philo()->meal);
	last = curr->last_meal;
	pthread_mutex_unlock(&philo()->meal);
	return (last);
}
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
	long long	(i) = 0;
	if (is_dead())
		return ;
	pthread_mutex_t	*my_fork = &seat->fork;
	pthread_mutex_t	*next_fork = &seat->next->fork;
	if (seat->seat_number % 2)
	{
		pthread_mutex_lock(&i_mutex);
		i = return_time();
		pthread_mutex_unlock(&i_mutex);
		pthread_mutex_lock(my_fork);
		printf("[%lld] %d pick up a fork !\n", (return_time() - i), seat->seat_number);
		pthread_mutex_lock(next_fork); // deadlock d zeb
		printf("[%lld] %d pick up a fork !\n", (return_time() - i), seat->seat_number);
	}
	else
	{
		pthread_mutex_lock(&i_mutex);
		i = return_time();
		pthread_mutex_unlock(&i_mutex);
		pthread_mutex_lock(my_fork);		
		printf("[%lld] %d pick up a fork !\n", (return_time() - i), seat->seat_number);
		pthread_mutex_lock(next_fork);
		printf("[%lld] %d pick up a fork !\n", (return_time() - i), seat->seat_number);
	}
	// usleep(seat->philo->t_to_eat);
	if (is_dead())
		return ;
	pthread_mutex_lock(&philo()->meal);
	seat->last_meal = return_time();
	pthread_mutex_unlock(&philo()->meal);
	pthread_mutex_lock(&i_mutex);
	i = return_time();
	pthread_mutex_unlock(&i_mutex);
	printf("[%lld] %d is eating ...\n", (return_time() - i), seat->seat_number);
	//set last time eaten
	// if (is_dead())
	// 	return ;
	slp(seat->philo->t_to_eat);
	// usleep(seat->philo->t_to_eat * 1000);
	if (is_dead())
		return ;
	if (seat->seat_number % 2)
	{
		pthread_mutex_lock(&i_mutex);
		i = return_time();
		pthread_mutex_unlock(&i_mutex);
		pthread_mutex_unlock(my_fork);
		printf("[%lld] %d put down a fork !\n", (return_time() - i), seat->seat_number);
		pthread_mutex_unlock(next_fork);
		printf("[%lld] %d put down a fork !\n", (return_time() - i), seat->seat_number);
	}
	else
	{
		pthread_mutex_lock(&i_mutex);
		i = return_time();
		pthread_mutex_unlock(&i_mutex);
		pthread_mutex_unlock(next_fork);
		printf("[%lld] %d put down a fork !\n", (return_time() - i), seat->seat_number);
		pthread_mutex_unlock(my_fork);
		printf("[%lld] %d put down a fork !\n", (return_time() - i), seat->seat_number);
	}
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
	long long	i = 0;
	if (is_dead())
	return ;
	pthread_mutex_lock(&i_mutex);
	i = return_time();
	pthread_mutex_unlock(&i_mutex);
	printf("[%lld] %d is sleeping ...\n", (return_time() - i), seat->seat_number);
	slp(seat->philo->t_to_sleep);
	if (is_dead())
		return ;
	// usleep(seat->philo->t_to_sleep);
}

void	think(t_seats *seat)
{
	long long	i = 0;
	if (is_dead())
		return ;
	pthread_mutex_lock(&i_mutex);
	i = return_time();
	pthread_mutex_unlock(&i_mutex);
	printf("[%lld] %d is thinking ...\n", (return_time() - i), seat->seat_number);
}


void	*start(void	*arg)
{
	t_seats	*seat = (t_seats *)arg;
	while (1)
	{
		if (is_dead())
			 break ;
		pthread_mutex_lock(&i_mutex);
		i = return_time();
		pthread_mutex_unlock(&i_mutex);
		eat(seat);
		ft_sleep(seat);
		think(seat);
	}
	return (NULL);
}

void	*moderator(void *arg)
{
	(void)arg;
	t_seats *curr = philo()->table->head;
	while (curr)
	{
		pthread_mutex_lock(&philo()->death);
		if (return_time() - get_last_meal(curr) >= philo()->philo->t_to_die)
		{
			philo()->is_dead = true;
			pthread_mutex_unlock(&philo()->death);
			break;
		}
		pthread_mutex_unlock(&philo()->death);
		curr = curr->next;
	}
	return (NULL);
}

void	run(void)
{
	t_seats	*curr = philo()->table->head;
	size_t		counter = 0;
	pthread_t	mod = 0;
	while (counter < philo()->table->size)
	{
		curr->last_meal = return_time();
		pthread_create(&curr->philosopher_ID, NULL, start, curr);
		curr = curr->next;
		counter++;
	}
	// if (mod == 0)
	// {
		pthread_create(&mod, NULL, moderator, NULL);
	// }
	counter = 0;
	curr = philo()->table->head;
	while (counter < philo()->table->size)
	{
		pthread_join(curr->philosopher_ID, NULL);
		curr = curr->next;
		counter++;
	}
		pthread_join(mod, NULL);
}

