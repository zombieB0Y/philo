/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoentifi <zoentifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:02:56 by zm                #+#    #+#             */
/*   Updated: 2025/05/30 15:53:41 by zoentifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philosophers	*init_table(void)
{
	t_philosophers	*table;

	table = gc_malloc(sizeof(t_philosophers));
	if (!table)
		return NULL;
	memset(table, 0, sizeof(t_philosophers));
	return (table);
}

t_philo	*init_status(char **argv)
{
	int num_philosophers = atoi(argv[1]);
	int time_to_die = atoi(argv[2]);
	int time_to_eat = atoi(argv[3]);
	int time_to_sleep = atoi(argv[4]);
	pthread_mutex_init(&philo()->death, NULL);
	pthread_mutex_init(&philo()->write, NULL);
	pthread_mutex_init(&philo()->time_mutex, NULL);
	pthread_mutex_init(&philo()->meal, NULL);
	pthread_mutex_init(&philo()->sleep, NULL);
	t_philo	*philo = gc_malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->n_philo = num_philosophers;
	philo->t_to_die = time_to_die;
	philo->t_to_eat = time_to_eat;
	philo->t_to_sleep = time_to_sleep;
	return (philo);
}
