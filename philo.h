/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoentifi <zoentifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:57:29 by zoentifi          #+#    #+#             */
/*   Updated: 2025/05/26 16:19:53 by zoentifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdbool.h>

typedef struct s_philo
{
	int		t_to_die;
	int		n_philo;
	int		t_to_eat;
	int		t_to_sleep;
}			t_philo;
// Node to track allocated pointers
typedef struct t_GCNode
{
	void				*ptr;
	struct t_GCNode		*next;
}						t_GCNode;

typedef struct s_seats
{
	pthread_t		philosopher_ID;
	pthread_mutex_t	fork;
	int				seat_number;
	t_philo			*philo;
	struct s_seats	*next;
}					t_seats;

typedef struct s_philosophers
{
	t_seats		*head;
	t_seats		*tail;
	size_t		size;
}				t_philosophers;



typedef struct s_status
{
	t_GCNode    *g_head;
	t_philosophers  *table;
	t_philo         *philo;
	bool		is_dead;
}               t_status;
// -------------------------
t_philosophers	*init_table(void);
void	add_a_seat(t_philosophers *table, t_seats *philosopher);
t_seats	*create_philosopher(t_philosophers *table, int	ID);
void	run(void);
void	*start(void	*arg);
void    start_the_simulation(t_philosophers *table, t_philo *philo);
t_status        *philo(void);
t_philo	*init_status(char **argv);
void	*gc_malloc(size_t size);
void	gc_collect(void);

#endif