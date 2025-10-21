/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:54:26 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/10/21 05:35:07 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#define IMMINENT_THRES 30
#define EATING_USLEEP 100
#define SLEEPING_USLEEP 100

int	died_routine(t_pargs **pargs)
{
	int	res;

	pthread_mutex_lock((*pargs)->info->data_mutex);
	res = statechange_and_log_died(*pargs);
	if (res == 1)
		(*pargs)->pstate = PHILO_FAILURE;
	pthread_mutex_unlock((*pargs)->info->data_mutex);
	return (res);
}

int	eating_routine(t_pargs **pargs)
{
	int			res;
	time_t		elapsed_time;
	int			utte;

	utte = (*pargs)->utte;
	elapsed_time = elapsed_us(get_tv(), (*pargs)->pstatemodified_tv);
	if (elapsed_time > utte)
	{
		pthread_mutex_lock((*pargs)->info->data_mutex);
		res = put_fork_if_possible(
				&((*pargs)->r_fork), &((*pargs)->l_fork), *pargs);
		if (res == -1)
			return(pthread_mutex_unlock((*pargs)->info->data_mutex), 1);
		res = statechange_and_log_sleep(*pargs);
		if (res != 0)
			return(pthread_mutex_unlock((*pargs)->info->data_mutex), 1);
		return(pthread_mutex_unlock((*pargs)->info->data_mutex), 0);
	}
	if (utte - elapsed_time < IMMINENT_THRES + EATING_USLEEP)
		return (0);
	usleep(EATING_USLEEP);
	return (0);
}

int	initial_routine(t_pargs **pargs)
{
	int	res;

	(*pargs)->lastmeal_tv = get_tv();
	if ((*pargs)->id % 2 == 0)
		usleep(100 * (*pargs)->n_philo);
	//pthread_mutex_lock((*pargs)->info->data_mutex);
	res = get_fork_if_possible(
			&((*pargs)->r_fork), &((*pargs)->l_fork), *pargs);
	if (res == 1)
	{
		(*pargs)->n_eat++;
		pthread_mutex_lock((*pargs)->info->data_mutex);
		res = statechange_and_log_eat(*pargs);
		pthread_mutex_unlock((*pargs)->info->data_mutex);
		return(res);
	}
	pthread_mutex_lock((*pargs)->info->data_mutex);
	res = statechange_and_log_think(*pargs);
	if (res == -1)
		return(pthread_mutex_unlock((*pargs)->info->data_mutex), 1);
	return(pthread_mutex_unlock((*pargs)->info->data_mutex), 0);
}

int	thinking_routine(t_pargs **pargs)
{
	int			res;
	time_t		elapsed_time;
	int			uttd;

	uttd = (*pargs)->uttd;
	elapsed_time = elapsed_us(get_tv(), (*pargs)->lastmeal_tv);
	if (100 <= uttd - elapsed_time)
		usleep(50);
	res = get_fork_if_possible(
			&((*pargs)->r_fork), &((*pargs)->l_fork), *pargs);
	if (res == 1)
	{
		(*pargs)->n_eat++;
		pthread_mutex_lock((*pargs)->info->data_mutex);
		res = statechange_and_log_eat(*pargs);
		return(pthread_mutex_unlock((*pargs)->info->data_mutex), res);
	}
	return (0);
}

int	sleeping_routine(t_pargs **pargs)
{
	time_t		elapsed_time;
	int			utts;
	int			res;

	utts = (*pargs)->utts;
	elapsed_time = elapsed_us(get_tv(), (*pargs)->pstatemodified_tv);
	if (elapsed_time > utts)
	{
		pthread_mutex_lock((*pargs)->info->data_mutex);
		res = statechange_and_log_think(*pargs);
		if (res == 1)
			return(pthread_mutex_unlock((*pargs)->info->data_mutex), 1);
		return(pthread_mutex_unlock((*pargs)->info->data_mutex), 0);
	}
	if (utts - elapsed_time < IMMINENT_THRES + SLEEPING_USLEEP)
		return (0);
	else
		usleep(SLEEPING_USLEEP);
	return (0);
}
