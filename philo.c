/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoentifi <zoentifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:57:36 by zoentifi          #+#    #+#             */
/*   Updated: 2025/05/24 22:27:11 by zoentifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// This function represents the routine (task) our workers (threads) will execute.
void *worker_routine(void *arg)
{
	(void)arg;
	// All workers (threads) inside the factory (process) will print the same address (PID)
	printf("Worker ID->%lu: My factory's address (PID) is %d\n", pthread_self(), getpid());
	return (NULL);
}
int main(void)
{
	pthread_t worker1;
	pthread_t worker2;
	// Let's create two workers (threads) in the same factory (process).
	// Hiring (creating) the first worker.
	if (pthread_create(&worker1, NULL, worker_routine, NULL) != 0)
	return (1);
	// Hiring (creating) the second worker.
	if (pthread_create(&worker2, NULL, worker_routine, NULL) != 0)
	return (2);
	// Wait for both workers to finish their shift (tasks).
	pthread_join(worker1, NULL);
	pthread_join(worker2, NULL);
	return (0);
}

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

// void	*eat(void *arg)
// {
// 	int *i = arg;
// 	int c = 0;
// 	while (1)
// 	{
// 		if (c >= 60)
// 			break;
// 		printf("the %d is eating ...\n", *i);
// 		c++;
// 	}
// 	return (NULL);
// }

// void	ft_sleep(int time)
// {
// 	while (time--)
// 		;
// }

// int main(int argc, char **argv)
// {
// 	if (argc != 5)
// 	{
// 		write(2, "Error: Invalid number of arguments\n", 36);
// 		return (1);
// 	}
// 	int num_philosophers = atoi(argv[1]); // overflow wa9ila khaso thandla dyal atoi
// 	// int time_to_die = atoi(argv[2]);
// 	int time_to_eat = atoi(argv[3]);
// 	int time_to_sleep = atoi(argv[4]);
// 	if (num_philosophers <= 0 || time_to_eat <= 0 || time_to_sleep <= 0)
// 	{
// 		write(2, "Error: Invalid argument values\n", 32);
// 		return (1);
// 	}
// 	int i = 0;
// 	// while (i < num_philosophers)
// 	// {
// 	// 	printf("hani hna\n");
// 		pthread_t	thread;
// 		// int *thread_return = NULL;
// 		/*int thread_return = */
// 		pthread_create(&thread, NULL, eat, &i);
// 		ft_sleep(time_to_eat);
// 		// sleep(5);
// 		pthread_join(thread, NULL);
// 	// 	i++;
// 	// }
// 	return (0);
// }
