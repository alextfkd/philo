/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:54:26 by marvin            #+#    #+#             */
/*   Updated: 2025/10/08 03:20:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#define IMMINENT_THRES 30
#define EATING_USLEEP 100
#define SLEEPING_USLEEP 100

int	died_routine(t_pargs **pargs)
{
	statechange_and_log_died(*pargs);
	return (0);
}

int	eating_routine(t_pargs **pargs)
{
	time_t		elapsed_time;
	int			utte;

	pthread_mutex_lock((*pargs)->info->data_mutex);
	utte = (*pargs)->info->utte;
	pthread_mutex_unlock((*pargs)->info->data_mutex);
	elapsed_time = elapsed_us(get_tv(), (*pargs)->pstatemodified_tv);
	if (elapsed_time > utte)
	{
		put_fork_if_possible(&((*pargs)->r_fork), &((*pargs)->l_fork), *pargs);
		statechange_and_log_sleep(*pargs);
		return (0);
	}
	if (utte - elapsed_time < IMMINENT_THRES + EATING_USLEEP)
		return (0);
	usleep(EATING_USLEEP);
	return (0);
}

int	initial_routine(t_pargs **pargs)
{
	usleep((400 / (*pargs)->info->n_philo) * ((*pargs)->id) / 2);
	if ((*pargs)->id % 2 == 0)
	{
		usleep(80);
		(*pargs)->lastmeal_tv = get_tv();
	}
	if (get_fork_if_possible(
			&((*pargs)->r_fork),
			&((*pargs)->l_fork), *pargs) == 1
	)
	{
		(*pargs)->n_eat++;
		statechange_and_log_eat(*pargs);
		return (0);
	}
	statechange_and_log_think(*pargs);
	return (0);
}

int	thinking_routine(t_pargs **pargs)
{
	time_t		elapsed_time;
	time_t		usec_to_die;
	int			uttd;

	pthread_mutex_lock((*pargs)->info->data_mutex);
	uttd = (*pargs)->info->uttd;
	pthread_mutex_unlock((*pargs)->info->data_mutex);
	elapsed_time = elapsed_us(get_tv(), (*pargs)->lastmeal_tv);
	usec_to_die = uttd - elapsed_time;
	if (100 <= usec_to_die)
		usleep(50);
	if (get_fork_if_possible(
			&((*pargs)->r_fork),
			&((*pargs)->l_fork), *pargs) == 1
	)
	{
		pthread_mutex_lock((*pargs)->info->data_mutex);
		(*pargs)->n_eat++;
		pthread_mutex_unlock((*pargs)->info->data_mutex);
		statechange_and_log_eat(*pargs);
		return (0);
	}
	return (0);
}

int	sleeping_routine(t_pargs **pargs)
{
	time_t		elapsed_time;
	int			utts;

	pthread_mutex_lock((*pargs)->info->data_mutex);
	utts = (*pargs)->info->utts;
	pthread_mutex_unlock((*pargs)->info->data_mutex);
	elapsed_time = elapsed_us(get_tv(), (*pargs)->pstatemodified_tv);
	if (elapsed_time > utts)
	{
		statechange_and_log_think(*pargs);
		thinking_routine(pargs);
	}
	if (utts - elapsed_time < IMMINENT_THRES + SLEEPING_USLEEP)
		return (0);
	else
		usleep(SLEEPING_USLEEP);
	return (0);
}
