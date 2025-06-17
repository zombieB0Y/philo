/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoentifi <zoentifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:02:56 by zm                #+#    #+#             */
/*   Updated: 2025/06/17 16:06:49 by zoentifi         ###   ########.fr       */
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

bool	check_arg(char **av)
{
	int i;
	int	j;

	i = 1;
	j = 0;
	while (1)
	{
		if (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (false);
			j++;
		}
		else
		{
			i++;
			j = 0;
			if (i > 4)
				break ;
		}
	}
	return (true);
}

bool	lone_philo(void)
{
	print_msg(1, "has taken a fork");
	slp(philo()->philo->t_to_die);
	print_msg(1, "died");
	gc_collect();
	return (true);
}

t_philo	*init_status(int ac, char **argv)
{
	int num_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;

	if (ac > 4 && check_arg(argv))
	{
		num_philosophers = ft_atoi(argv[1]);
		time_to_die = ft_atoi(argv[2]);
		time_to_eat = ft_atoi(argv[3]);
		time_to_sleep = ft_atoi(argv[4]);
	}
	else
	{
		printf("need valid arguments !\n");
		return (NULL);
	}
	pthread_mutex_init(&philo()->death, NULL);
	pthread_mutex_init(&philo()->write, NULL);
	pthread_mutex_init(&philo()->meal, NULL);
	pthread_mutex_init(&philo()->time_mutex, NULL);
	t_philo	*philo = gc_malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->n_philo = num_philosophers;
	philo->t_to_die = time_to_die;
	philo->t_to_eat = time_to_eat;
	philo->t_to_sleep = time_to_sleep;
	return (philo);
}
