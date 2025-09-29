/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 01:41:10 by marvin            #+#    #+#             */
/*   Updated: 2025/09/26 09:36:35 by marvin           ###   ########.fr       */
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

	fork_arr = (t_fork **)malloc(sizeof(t_fork*) * (n + 1));
	if (fork_arr == NULL)
		return (NULL);
	memset(fork_arr, '\0', sizeof(t_fork*) * (n + 1));
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


int get_fork_if_possible(t_fork **rfork, t_fork **lfork, t_pargs *pargs)
{
	int			res;
	t_fstate	rfstate;
	t_fstate	lfstate;

	//printf("getfork, id -> %d, rfork %d, lfork %d\n", pargs->id, pargs->r_fork->fid, pargs->l_fork->fid);

	//usleep(2000000);
	//write(1, "getfork", 7);
	res = 0;
	if (rfork == NULL || lfork == NULL || pargs == NULL)
		return (-1);
	if ((*rfork)->fid > (*lfork)->fid)
	{
		if (pthread_mutex_lock(&((*rfork)->mutex)) == -1)
			return (-1);
		if (pthread_mutex_lock(&((*lfork)->mutex)) == -1)
		{
			pthread_mutex_unlock(&((*rfork)->mutex));
			return (-1);
		}
	}
	else
	{
		if (pthread_mutex_lock(&((*lfork)->mutex)) == -1)
			return (-1);
		if (pthread_mutex_lock(&((*rfork)->mutex)) == -1)
		{
			pthread_mutex_unlock(&((*lfork)->mutex));
			return (-1);
		}
	}
	rfstate = (*rfork)->fstate;
	lfstate = (*lfork)->fstate;
	if (rfstate == FORK_AVALIABLE && lfstate == FORK_AVALIABLE)
	{
		(*rfork)->owner = &(pargs->id);
		(*lfork)->owner = &(pargs->id);
		(*rfork)->fstate = FORK_OCCUPIED;
		(*lfork)->fstate = FORK_OCCUPIED;
		//write(1, "getfork is DONE", 7);
		res = 1;
		takefork_and_log(pargs);
	}
	if ((*rfork)->fid > (*lfork)->fid)
	{
		pthread_mutex_unlock(&((*lfork)->mutex));
		pthread_mutex_unlock(&((*rfork)->mutex));
	}
	else
	{
		pthread_mutex_unlock(&((*rfork)->mutex));
		pthread_mutex_unlock(&((*lfork)->mutex));
	}
	return (res);
}

int put_fork_if_possible(t_fork **rfork, t_fork **lfork, t_pargs *pargs)
{
	int			res;
	t_fstate	rfstate;
	t_fstate	lfstate;

	res = 0;
	//printf("XXXXXXXXXX");
	//write(1, "putfork", 7);
	if (rfork == NULL || lfork == NULL || pargs == NULL)
		return (-1);
	if ((*rfork)->fid > (*lfork)->fid)
	{
		if (pthread_mutex_lock(&((*rfork)->mutex)) == -1)
			return (-1);
		if (pthread_mutex_lock(&((*lfork)->mutex)) == -1)
		{
			pthread_mutex_unlock(&((*rfork)->mutex));
			return (-1);
		}
	}
	else
	{
		if (pthread_mutex_lock(&((*lfork)->mutex)) == -1)
			return (-1);
		if (pthread_mutex_lock(&((*rfork)->mutex)) == -1)
		{
			pthread_mutex_unlock(&((*lfork)->mutex));
			return (-1);
		}
	}
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
	if ((*rfork)->fid > (*lfork)->fid)
	{
		pthread_mutex_unlock(&((*lfork)->mutex));
		pthread_mutex_unlock(&((*rfork)->mutex));
	}
	else
	{
		pthread_mutex_unlock(&((*rfork)->mutex));
		pthread_mutex_unlock(&((*lfork)->mutex));
	}
	return (res);
}
