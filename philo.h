/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoentifi <zoentifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:57:29 by zoentifi          #+#    #+#             */
/*   Updated: 2025/06/17 21:58:15 by zoentifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int					t_to_die;
	int					n_philo;
	int					t_to_eat;
	int					t_to_sleep;
	int					n_meals;
}						t_philo;
// Node to track allocated pointers
typedef struct t_GCNode
{
	void				*ptr;
	struct t_GCNode		*next;
}						t_GCNode;

typedef struct s_seats
{
	pthread_t			philosopher_ID;
	pthread_mutex_t		my_fork;
	int					num_meals;
	int					seat_number;
	long long			last_meal;
	t_philo				*philo;
	struct s_seats	*next;
}						t_seats;

typedef struct s_philosophers
{
	t_seats		*head;
	t_seats		*tail;
	size_t		size;
}						t_philosophers;

typedef struct timeval	t_timeval;

typedef struct s_glm
{
	long long	last;
	int			num_meals;
}				t_glm;

typedef struct s_status
{
	t_GCNode			*g_head;
	t_philosophers		*table;
	t_philo				*philo;
	bool				is_dead;
	bool				error;
	bool				num_meals_active;
	pthread_mutex_t		death;
	pthread_mutex_t		write;
	pthread_t			mod;
	pthread_mutex_t		time_mutex;
	long long			time;
	pthread_mutex_t		meal;
}						t_status;
// -------------------------
t_philosophers			*init_table(void);
void					add_a_seat(t_philosophers *table, t_seats *philosopher);
t_seats					*create_philosopher(t_philosophers *table, int ID);
void					run(void);
void					*start(void *arg);
void					slp(int time);
int						is_dead(void);
void					print_msg(size_t seat_number, char *stat);
void					start_the_simulation(t_philosophers *table,
							t_philo *philo);
int						ft_atoi(const char *str);
int	ft_isdigit(int c);
t_status				*philo(void);
long long				return_time(void);
t_philo					*init_status(int ac, char **argv);
bool					lone_philo(void);
void					*gc_malloc(size_t size);
void					gc_collect(void);

#endif