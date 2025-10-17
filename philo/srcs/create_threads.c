/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 01:42:05 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/10/17 22:29:50 by tkatsuma         ###   ########.fr       */
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
