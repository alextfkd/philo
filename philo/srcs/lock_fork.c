/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:40:16 by marvin            #+#    #+#             */
/*   Updated: 2025/10/02 00:41:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	lock_fork_mutex(t_fork *rfork, t_fork *lfork)
{
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
