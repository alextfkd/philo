/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 01:41:10 by marvin            #+#    #+#             */
/*   Updated: 2025/10/07 11:56:49 by marvin           ###   ########.fr       */
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
	{
		pthread_mutex_destroy(&(fork_arr[i]->mutex));
		free(fork_arr[i]);
		i++;
	}
	free(fork_arr);
	return ;
}

t_fork	*create_fork(int fid)
{
	t_fork			*fork;
	int				mutex_res;

	fork = (t_fork *)malloc(sizeof(t_fork));
	if (fork == NULL)
		return (NULL);
	memset(fork, '\0', sizeof(t_fork));
	fork->fid = fid;
	fork->fstate = FORK_AVALIABLE;
	fork->owner = NULL;
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

	fork_arr = (t_fork **)malloc(sizeof(t_fork *) * (n + 1));
	if (fork_arr == NULL)
		return (NULL);
	memset(fork_arr, '\0', sizeof(t_fork *) * (n + 1));
	i = 0;
	while (i < n)
	{
		fork = create_fork(i);
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

int	get_fork_if_possible(t_fork **rfork, t_fork **lfork, t_pargs *pargs)
{
	int			res;
	t_fstate	rfstate;
	t_fstate	lfstate;

	res = 0;
	if (rfork == NULL || lfork == NULL || pargs == NULL)
		return (-1);
	if (lock_fork_mutex(*rfork, *lfork) != 0)
		return (-1);
	rfstate = (*rfork)->fstate;
	lfstate = (*lfork)->fstate;
	if (rfstate == FORK_AVALIABLE && lfstate == FORK_AVALIABLE)
	{
		(*rfork)->owner = &(pargs->id);
		(*lfork)->owner = &(pargs->id);
		(*rfork)->fstate = FORK_OCCUPIED;
		(*lfork)->fstate = FORK_OCCUPIED;
		takefork_and_log(pargs);
		res = 1;
	}
	unlock_fork_mutex(*rfork, *lfork);
	return (res);
}

int	put_fork_if_possible(t_fork **rfork, t_fork **lfork, t_pargs *pargs)
{
	int			res;
	t_fstate	rfstate;
	t_fstate	lfstate;

	res = 0;
	if (rfork == NULL || lfork == NULL || pargs == NULL)
		return (-1);
	if (lock_fork_mutex(*rfork, *lfork) != 0)
		return (-1);
	rfstate = (*rfork)->fstate;
	lfstate = (*lfork)->fstate;
	if (rfstate == FORK_OCCUPIED && lfstate == FORK_OCCUPIED)
	{
		(*rfork)->owner = NULL;
		(*lfork)->owner = NULL;
		(*rfork)->fstate = FORK_AVALIABLE;
		(*lfork)->fstate = FORK_AVALIABLE;
		res = 1;
	}
	unlock_fork_mutex(*rfork, *lfork);
	return (res);
}
