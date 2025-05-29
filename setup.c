/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoentifi <zoentifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:04:49 by zm                #+#    #+#             */
/*   Updated: 2025/05/29 17:36:46 by zoentifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	slp(int time)
{
	long long	(i) = return_time();
	while ((return_time() - i) < time)
		usleep(500);
}

int	is_dead()
{
	pthread_mutex_lock(&philo()->death);
	if (philo()->is_dead)
		return (pthread_mutex_unlock(&philo()->death), 1);
	return (pthread_mutex_unlock(&philo()->death),0);
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
	if (is_dead())
		return ;
	pthread_mutex_t	*my_fork = &seat->fork;
	pthread_mutex_t	*next_fork = &seat->next->fork;
	// pthread_mutex_lock(&philo()->meal);
	// seat->last_meal = return_time();
	// pthread_mutex_unlock(&philo()->meal);
	if (seat->seat_number % 2 && !is_dead())
	{
		pthread_mutex_lock(next_fork);
		printf("%lld %d has taken a fork\n", (return_time() - philo()->time), seat->seat_number);
		pthread_mutex_lock(my_fork);
		printf("%lld %d has taken a fork\n", (return_time() - philo()->time), seat->seat_number);
	}
	else if (!is_dead())
	{
		pthread_mutex_lock(my_fork);		
		printf("%lld %d has taken a fork\n", (return_time() - philo()->time), seat->seat_number);
		pthread_mutex_lock(next_fork);
		printf("%lld %d has taken a fork\n", (return_time() - philo()->time), seat->seat_number);
	}
	if (is_dead())
	{
		pthread_mutex_unlock(my_fork);
		pthread_mutex_unlock(next_fork);
		return ;
	}
	printf("%lld %d is eating\n", (return_time() - philo()->time), seat->seat_number);
	slp(seat->philo->t_to_eat);
	pthread_mutex_lock(&philo()->meal);
	seat->last_meal = return_time();
	pthread_mutex_unlock(&philo()->meal);
	if (is_dead())
	{
		pthread_mutex_unlock(my_fork);
		pthread_mutex_unlock(next_fork);
		return ;
	}
	if (seat->seat_number % 2)
	{
		pthread_mutex_unlock(my_fork);
		pthread_mutex_unlock(next_fork);
	}
	else
	{
		pthread_mutex_unlock(next_fork);
		pthread_mutex_unlock(my_fork);
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
	if (is_dead())
		return ;
	printf("%lld %d is sleeping\n", (return_time() - philo()->time), seat->seat_number);
	slp(seat->philo->t_to_sleep);
	if (is_dead())
		return ;
}

void	think(t_seats *seat)
{
	if (is_dead())
		return ;
	printf("%lld %d is thinking\n", (return_time() - philo()->time), seat->seat_number);
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
	t_seats	*curr;
	long long	time_diff;

	(void)arg;
	while (true)
	{
		curr = table->head;
		while (curr)
		{
			time_diff = return_time() - get_last_meal(curr);
			if (time_diff >= philo()->philo->t_to_die)
			{
				pthread_mutex_lock(&philo()->death);
				philo()->is_dead = true;
				pthread_mutex_unlock(&philo()->death);
				// print_state(curr, "died");
				return (NULL);
			}
			curr = curr->next;
		}
		// if (table->meals_required != -1 && check_if_all_ate(table))
		// 	return (NULL);
		// if (!is_critical_time())
			// usleep(100);
	}
	return (NULL);
}


void	run(void)
{
	t_seats	*curr = philo()->table->head;
	size_t		counter = 0;
	pthread_t	mod = 0;
	philo()->time = return_time();
	while (counter < philo()->table->size)
	{
		// pthread_mutex_lock(&philo()->meal);
		curr->last_meal = return_time();
		// pthread_mutex_unlock(&philo()->meal);
		pthread_create(&curr->philosopher_ID, NULL, start, curr);
		curr = curr->next;
		counter++;
	}
	counter = 0;
	curr = philo()->table->head;
	pthread_create(&mod, NULL, moderator, NULL);
	while (counter < philo()->table->size)
	{
		pthread_join(curr->philosopher_ID, NULL);
		curr = curr->next;
		counter++;
	}
	pthread_join(mod, NULL);
}

