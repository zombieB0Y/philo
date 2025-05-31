/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zm <zm@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:04:49 by zm                #+#    #+#             */
/*   Updated: 2025/05/31 04:16:23 by zm               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	slp(long time)
{
	long	start;
	long	sleep_interval;

	start = return_time();
	if (philo()->philo->n_philo > 100)
		sleep_interval = 500;
	else if (philo()->philo->n_philo > 50)
		sleep_interval = 100;
	else
		sleep_interval = 50;
	while ((return_time() - start) < time)
		usleep(sleep_interval);
}

int	is_dead()
{
	pthread_mutex_lock(&philo()->death);
	if (philo()->is_dead)
		return (pthread_mutex_unlock(&philo()->death), 1);
	return (pthread_mutex_unlock(&philo()->death),0);
}

long int	get_last_meal(t_seats curr)
{
	long int last;
	pthread_mutex_lock(&philo()->meal);
	last = curr.last_meal;
	pthread_mutex_unlock(&philo()->meal);
	return (last);
}
void    start_the_simulation(t_philosophers *table, t_philo *arg)
{
	int	i;

	i = 0;
	philo()->philo = arg;
	table = init_table();
	if (!table)
		return ;
	philo()->table = table;
	philo()->is_dead = false;
	while (i < arg->n_philo)
	{
		create_philosopher(i);
		i++;
	}
	i = 0;
	while (i < arg->n_philo)
	{
		assign_next_fork(table, i);
		i++;
	}
	run();
}
void	eat(t_seats *seat)
{
	if (is_dead())
		return ;
	pthread_mutex_t	*my_fork = &seat->my_fork;
	pthread_mutex_t	*next_fork = &seat->next_fork;
	if (seat->seat_number % 2)
	{
		pthread_mutex_lock(next_fork);
		print_msg(seat->seat_number, "has taken a fork");
		if (is_dead())
		{
			pthread_mutex_unlock(next_fork);
			return ;
		}
		pthread_mutex_lock(my_fork);
		print_msg(seat->seat_number, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(my_fork);
		print_msg(seat->seat_number, "has taken a fork");
		if (is_dead())
		{
			pthread_mutex_unlock(my_fork);
			return ;
		}
		pthread_mutex_lock(next_fork);
		print_msg(seat->seat_number, "has taken a fork");
	}
	pthread_mutex_lock(&philo()->meal);
	seat->last_meal = return_time();
	pthread_mutex_unlock(&philo()->meal);
	print_msg(seat->seat_number, "is eating");
	if (!is_dead())
		slp(seat->philo->t_to_eat);
	// if (seat->seat_number % 2)
	// {
	pthread_mutex_unlock(my_fork);
	pthread_mutex_unlock(next_fork);
	// }
	// else
	// {
	// 	pthread_mutex_unlock(next_fork);
	// 	pthread_mutex_unlock(my_fork);
	// }
}

t_seats	*create_philosopher(int	ID)
{
	t_seats	*philosopher;

	philosopher = gc_malloc(sizeof(t_seats));
	if (!philosopher)
		return (NULL);
	// philosopher->next = table->head;
	philosopher->philosopher_ID = 0;
	pthread_mutex_init(&philosopher->my_fork, NULL);
	philosopher->seat_number = ID + 1;
	philosopher->philo = philo()->philo;
	return (philosopher);
}

// void	add_a_seat(t_philosophers *table, t_seats *philosopher)
// {
// 	if (!table)
// 		return ;
// 	if (!table->head)
// 	{
// 		table->head = philosopher;
// 		table->tail = philosopher;
// 	}
// 	else
// 	{
// 		table->tail->next = philosopher;
// 		table->tail = philosopher;
// 	}
// 	table->size++;
// }

void	ft_sleep(t_seats *seat)
{
	print_msg(seat->seat_number, "is sleeping");
	if (!is_dead())
		slp(seat->philo->t_to_sleep);
}

void	think(t_seats *seat)
{
	print_msg(seat->seat_number, "is thinking");
	// if (philo()->philo->n_philo % 2 != 0
	// 	&& (philo()->philo->t_to_eat * 3) <= philo()->philo->t_to_die)
	// 	slp(1);
}


void	*start(void	*arg)
{
	t_seats	*seat = (t_seats *)arg;
	while (!is_dead())
	{
		eat(seat);
		ft_sleep(seat);
		think(seat);
	}
	return (NULL);
}

void	*moderator(void *arg)
{
	t_philosophers	*table = philo()->table;
	size_t			n_philo;
	long long		t_to_die;
	t_seats			*curr;
	size_t			i;

	(void)arg;
	curr = table->seats_array;
	n_philo = philo()->philo->n_philo;
	t_to_die = philo()->philo->t_to_die;
	while (1)
	{
		curr = table->seats_array;
		i = 0;
		while (i < n_philo)
		{
			if (return_time() - get_last_meal(curr[i]) >= t_to_die)
			{
				print_msg(curr[i].seat_number, "died");
				pthread_mutex_lock(&philo()->death);
				philo()->is_dead = true;
				pthread_mutex_unlock(&philo()->death);
				return (NULL);
			}
			i++;
		}
		usleep(500);
	}
	// if (table->meals_required != -1 && check_if_all_ate(table))
	// 	return (NULL);
	// if (!is_critical_time())
	return (NULL);
}


void	run(void)
{
	t_seats	*curr = philo()->table->seats_array;
	size_t	n_philo = philo()->philo->n_philo;
	size_t		counter = 0;
	pthread_t	mod = 0;
	while (counter < n_philo)
	{
		if (counter == 0)
			philo()->time = return_time();
		if ((counter + 1) % 2)
		{
			curr[counter].last_meal = return_time();
			pthread_create(&curr[counter].philosopher_ID, NULL, start, &curr[counter]);
		}
		else
		{
			curr[counter].last_meal = return_time();
			pthread_create(&curr[counter].philosopher_ID, NULL, start, &curr[counter]);
		}
		counter++;	
	}
	counter = 0;
	curr = philo()->table->seats_array;
	pthread_create(&mod, NULL, moderator, NULL);
	while (counter < philo()->table->size)
	{
		pthread_join(curr[counter].philosopher_ID, NULL);
		counter++;
	}
	pthread_join(mod, NULL);
}

