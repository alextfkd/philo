/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 01:42:05 by marvin            #+#    #+#             */
/*   Updated: 2025/10/10 01:59:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static pthread_t	*create_empty_threads(int n)
{
	pthread_t	*threads;

	if (n <= 0)
		return (NULL);
	threads = (pthread_t *)malloc(sizeof(pthread_t) * n);
	if (threads == NULL)
		return (NULL);
	memset(threads, '\0', sizeof(pthread_t) * n);
	return (threads);
}

pthread_t	*create_pthreads_arr(int n, t_pargs **pargs)
{
	pthread_t	*threads;
	int			i;

	threads = create_empty_threads(n);
	if (threads == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		pthread_create(&(threads[i]), NULL, philo_thread_action, pargs[i]);
		i++;
	}
	return (threads);
}
