/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zm <zm@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:57:36 by zoentifi          #+#    #+#             */
/*   Updated: 2025/05/31 04:11:07 by zm               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_status *philo(void)
{
	static t_status status;
	return (&status);
}

// #define BOLD_CYAN "\033[1;36m"
// #define RESET "\033[0m"

// int main()
// {
//     struct timeval start, end;

// 	pthread_mutex_init(&philo()->time_mutex, NULL);
//     gettimeofday(&start, NULL); // Get the current time before sleeping
//     // usleep(500000);  // Expected sleep: 500 milliseconds (0.5 seconds)
//     slp(500);
//     gettimeofday(&end, NULL);  // Get the time after sleeping

//     long seconds = end.tv_sec - start.tv_sec;
//     long microseconds = end.tv_usec - start.tv_usec;

//     double elapsedMilliseconds = (seconds * 1000.0) + (microseconds / 1000.0);

//     printf("Expected sleep duration: "BOLD_CYAN"\t500 milliseconds\n"RESET);
//     printf("Actual sleep duration: "BOLD_CYAN"\t\t%.2f milliseconds\n\n"RESET, elapsedMilliseconds);

//     return 0;
// }

int main(int argc, char **argv)
{
	t_philo	*arg;

	arg = init_status(argv);
	(void)argc;
	t_philosophers	*table = NULL;
	start_the_simulation(table, arg);
	gc_collect();
	pthread_mutex_destroy(&philo()->meal);
	pthread_mutex_destroy(&philo()->death);
	pthread_mutex_destroy(&philo()->write);
	
	return (0);
}
