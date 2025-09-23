/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 01:42:05 by marvin            #+#    #+#             */
/*   Updated: 2025/09/22 01:42:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_t	*create_empty_threads(int n)
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
