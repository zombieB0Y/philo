/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoentifi <zoentifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:57:36 by zoentifi          #+#    #+#             */
/*   Updated: 2025/05/26 21:42:53 by zoentifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	a = 0;
// pthread_mutex_t	mutex;
// void	*run(void *arg)
// {
// 	long long i = 0;
// 	while (i < 1000000)
// 	{
// 		pthread_mutex_lock(&mutex);
// 		a++;
// 		pthread_mutex_unlock(&mutex);
// 		i++;
// 	}
// 	return NULL;
// }

// int main()
// {
// 	pthread_t	alo1 = 0;
// 	pthread_t	alo2;
// 	pthread_create(&alo1, NULL, run, NULL);
// 	printf("%ld\n", alo1);
// 	pthread_create(&alo2, NULL, run, NULL);
// 	pthread_join(alo1, NULL);
// 	pthread_join(alo2, NULL);
// 	printf("total drink %d\n", a);
// 	return 0;
// }

// This function represents the routine (task) our workers (threads) will execute.
void *worker_routine(void *arg)
{
	(void)arg;
	// All workers (threads) inside the factory (process) will print the same address (PID)
	printf("Worker ID->%lu: My factory's address (PID) is %d\n", pthread_self(), getpid());
	return (NULL);
}

t_status *philo(void)
{
	static t_status status;
	return (&status);
}


int main(int argc, char **argv)
{
	t_philo	*philo;

	philo = init_status(argv);
	(void)argc;
	t_philosophers	*table;

	table = init_table();
	if (!table)
		return (1);
	start_the_simulation(table, philo);
	gc_collect();
	
	return (0);
}

// int main(void)
// {
// 	pthread_t worker1;
// 	pthread_t worker2;
// 	// Let's create two workers (threads) in the same factory (process).
// 	// Hiring (creating) the first worker.
// 	if (pthread_create(&worker1, NULL, worker_routine, NULL) != 0)
// 	return (1);
// 	// Hiring (creating) the second worker.
// 	if (pthread_create(&worker2, NULL, worker_routine, NULL) != 0)
// 	return (2);
// 	// Wait for both workers to finish their shift (tasks).
// 	pthread_join(worker1, NULL);
// 	pthread_join(worker2, NULL);
// 	return (0);
// }

// void *make_coffee(void *arg)
// {
// 	(void)arg;
// 	printf("Making coffee...\n");
// 	sleep(2);
// 	printf("Coffee ready!\n");
// 	return (NULL);
// }

// void *make_pastry(void *arg)
// {
// 	(void)arg;
// 	printf("Baking pastry...\n");
// 	sleep(3);
// 	printf("Pastry ready!\n");
// 	return (NULL);
// }

// int main(void)
// {
// 	pthread_t coffee_thread;
// 	pthread_t pastry_thread;

// 	pthread_create(&coffee_thread, NULL, make_coffee, NULL);
// 	pthread_create(&pastry_thread, NULL, make_pastry, NULL);
	
// 	//Before handing the order to customer, i nees to WAIT both threads
// 	pthread_join(coffee_thread, NULL);
// 	pthread_join(pastry_thread, NULL);
	
// 	printf("\n\n\tThx for coming to Starbucks!\n"
// 		"\there's the ☕️ 'n 🥐\n\n\n");
// 	return (0);
// }


// void	ft_sleep(int time)
// {
// 	while (time--)
// 		;
// }

