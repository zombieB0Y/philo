/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoentifi <zoentifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:04:49 by zm                #+#    #+#             */
/*   Updated: 2025/06/17 22:04:16 by zoentifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	slp(int time)
{
	long long	(i) = return_time();
	while ((return_time() - i) < time)
	{
		if (is_dead())
			return ;
		usleep(500);
	}
}

int	is_dead()
{
	pthread_mutex_lock(&philo()->death);
	if (philo()->is_dead)
		return (pthread_mutex_unlock(&philo()->death), 1);
	return (pthread_mutex_unlock(&philo()->death),0);
}
t_glm	get_last_meal(t_seats *curr)
{
	t_glm	help;

	pthread_mutex_lock(&philo()->meal);
	help.num_meals = curr->num_meals;
	help.last = curr->last_meal;
	pthread_mutex_unlock(&philo()->meal);
	return (help);
}

void    start_the_simulation(t_philosophers *table, t_philo *arg)
{
	int	i;

	i = 0;
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
	pthread_mutex_t	*my_fork = &seat->my_fork;
	pthread_mutex_t	*next_fork = &seat->next->my_fork;
	pthread_mutex_t	*meal = &philo()->meal;
	if (seat->seat_number % 2)
	{
		pthread_mutex_lock(next_fork);
		print_msg(seat->seat_number, "has taken a fork");
		pthread_mutex_lock(my_fork);
		print_msg(seat->seat_number, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(my_fork);
		print_msg(seat->seat_number, "has taken a fork");
		pthread_mutex_lock(next_fork);
		print_msg(seat->seat_number, "has taken a fork");

	}
	if (is_dead())
	{
		pthread_mutex_unlock(my_fork);
		pthread_mutex_unlock(next_fork);
		return ;
	}
	print_msg(seat->seat_number, "is eating");
	pthread_mutex_lock(meal);
	seat->num_meals++;
	seat->last_meal = return_time();
	pthread_mutex_unlock(meal);
	slp(seat->philo->t_to_eat);
	pthread_mutex_unlock(my_fork);
	pthread_mutex_unlock(next_fork);
}

t_seats	*create_philosopher(t_philosophers *table , int ID)
{
	t_seats	*philosopher;

	philosopher = gc_malloc(sizeof(t_seats));
	if (!philosopher)
		return (NULL);
	philosopher->next = table->head;
	philosopher->philosopher_ID = 0;
	pthread_mutex_init(&philosopher->my_fork, NULL);
	philosopher->seat_number = ID + 1;
	philosopher->num_meals = 0;
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
	print_msg(seat->seat_number, "is sleeping");
	if (!is_dead())
		slp(seat->philo->t_to_sleep);
}

void	think(t_seats *seat)
{
	print_msg(seat->seat_number, "is thinking");
	if (philo()->philo->n_philo % 2 != 0)
		slp(1);
	if (is_dead())
		return ;
}


void	*start(void	*arg)
{
	t_seats	*seat = (t_seats *)arg;
	while (!is_dead())
	{
		eat(seat);
		ft_sleep(seat);
		if (!is_dead())
			think(seat);
	}
	return (NULL);
}

void	*moderator(void *arg)
{
	t_philosophers	*table = philo()->table;
	long long		t_to_die;
	t_seats			*curr;

	(void)arg;
	curr = table->head;
	t_to_die = philo()->philo->t_to_die;
	curr = table->head;
	t_glm	help;
	while (1)
	{
		help = get_last_meal(curr);
		if (return_time() - help.last > t_to_die)
		{
			print_msg(curr->seat_number, "died");
			pthread_mutex_lock(&philo()->death);
			philo()->is_dead = true;
			pthread_mutex_unlock(&philo()->death);
			return (NULL);
		}
		if (philo()->num_meals_active
			&& help.num_meals >= philo()->philo->n_meals)
			{
				pthread_mutex_lock(&philo()->death);
				philo()->is_dead = true;
				pthread_mutex_unlock(&philo()->death);
				return (NULL);
			}
		curr = curr->next;
	}
	return (NULL);
}


void	run(void)
{
	t_seats	*curr = philo()->table->head;
	size_t	n_philo = philo()->philo->n_philo;
	size_t		counter = 0;
	philo()->time = return_time();
	while (counter < n_philo)
	{
		curr->last_meal = return_time();
		pthread_create(&curr->philosopher_ID, NULL, start, curr);
		curr = curr->next;
		counter++;	
	}
	counter = 0;
	curr = philo()->table->head;
	pthread_create(&philo()->mod, NULL, moderator, NULL);
	while (counter < n_philo)
	{
		pthread_join(curr->philosopher_ID, NULL);
		curr = curr->next;
		counter++;
	}
	pthread_join(philo()->mod, NULL);
}

