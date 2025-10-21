/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:40:16 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/10/21 10:39:10 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	lock_fork_mutex(t_fork *rfork, t_fork *lfork)
{
	if (rfork == NULL || lfork == NULL)
		return (-1);
	if ((rfork)->fid > (lfork)->fid)
	{
		if (pthread_mutex_lock(&((rfork)->mutex)) == -1)
			return (-1);
		if (pthread_mutex_lock(&((lfork)->mutex)) == -1)
		{
			pthread_mutex_unlock(&((rfork)->mutex));
			return (-1);
		}
	}
	else
	{
		if (pthread_mutex_lock(&((lfork)->mutex)) == -1)
			return (-1);
		if (pthread_mutex_lock(&((rfork)->mutex)) == -1)
		{
			pthread_mutex_unlock(&((lfork)->mutex));
			return (-1);
		}
	}
	return (0);
}

void	unlock_fork_mutex(t_fork *rfork, t_fork *lfork)
{
	if ((rfork)->fid > (lfork)->fid)
	{
		pthread_mutex_unlock(&((lfork)->mutex));
		pthread_mutex_unlock(&((rfork)->mutex));
	}
	else
	{
		pthread_mutex_unlock(&((rfork)->mutex));
		pthread_mutex_unlock(&((lfork)->mutex));
	}
}

void	lock_log_data_mutex(t_pargs *pargs)
{
	pthread_mutex_lock(pargs->info->log_mutex);
	pthread_mutex_lock(pargs->info->data_mutex);
}

void	unlock_data_log_mutex(t_pargs *pargs)
{
	pthread_mutex_unlock(pargs->info->data_mutex);
	pthread_mutex_unlock(pargs->info->log_mutex);
}
