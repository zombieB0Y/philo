/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zm <zm@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:17:11 by zm                #+#    #+#             */
/*   Updated: 2025/05/25 14:26:14 by zm               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	gc_register(void *ptr)
{
	t_GCNode	*node;

	if (!ptr)
		return ;
	node = malloc(sizeof(t_GCNode));
	if (!node)
		return ;
	node->ptr = ptr;
	node->next = philo()->g_head;
	philo()->g_head = node;
}

void	*gc_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc((size_t)size);
	if (!ptr)
		return (NULL);
	gc_register(ptr);
	return (ptr);
}

void	gc_collect(void)
{
	t_GCNode	*current;
	t_GCNode	*next;

	current = philo()->g_head;
	while (current)
	{
		next = current->next;
		free(current->ptr);
		free(current);
		current = next;
	}
	philo()->g_head = NULL;
}
