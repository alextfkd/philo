/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 01:41:10 by marvin            #+#    #+#             */
/*   Updated: 2025/09/23 12:04:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_fork_arr(t_fork **fork_arr)
{
	int	i;

	if (fork_arr == NULL)
		return ;
	i = 0;
	while (fork_arr[i] != NULL)
		free(fork_arr[i++]);
	free(fork_arr);
	return ;
}

t_fork	*create_fork(void)
{
	t_fork			*fork;
	int				mutex_res;

	fork = (t_fork *)malloc(sizeof(t_fork));
	if (fork == NULL)
		return (NULL);
	memset(fork, '\0', sizeof(t_fork));
	fork->fstate = FORK_AVALIABLE;
	mutex_res = pthread_mutex_init(&(fork->mutex), NULL);
	if (mutex_res == -1)
	{
		free (fork);
		return (NULL);
	}
	return (fork);
}

// Fork Array has n + 1 length, ending with NULL pointer.
t_fork	**create_fork_arr(int n)
{
	t_fork	**fork_arr;
	t_fork	*fork;
	int		i;

	fork_arr = (t_fork **)malloc(sizeof(t_fork*) * (n + 1));
	if (fork_arr == NULL)
		return (NULL);
	memset(fork_arr, '\0', sizeof(t_fork*) * (n + 1));
	i = 0;
	while (i < n)
	{
		fork = create_fork();
		if (fork == NULL)
		{
			free_fork_arr(fork_arr);
			return (NULL);
		}
		fork_arr[i] = fork;
		i++;
	}
	return (fork_arr);
}

int	fork_status_set(t_fork **fork, t_fstate fstate)
{
	int	res;

	res = pthread_mutex_lock(&((*fork)->mutex));
	if (res == -1)
		return (-1);
	(*fork)->fstate = fstate;
	res = pthread_mutex_unlock(&((*fork)->mutex));
	if (res == -1)
		return (-1);
	return (0);
}

t_fstate	fork_status_check(t_fork **fork)
{
	int			res;
	t_fstate	fstate;

	res = pthread_mutex_lock(&((*fork)->mutex));
	if (res == -1)
		return (FORK_OCCUPIED);
	fstate = (*fork)->fstate;
	res = pthread_mutex_unlock(&((*fork)->mutex));
	if (res == -1)
		return (FORK_OCCUPIED);
	return (fstate);
}
