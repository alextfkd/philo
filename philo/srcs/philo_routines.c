/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:54:26 by marvin            #+#    #+#             */
/*   Updated: 2025/10/03 23:02:15 by tkatsuma         ###   ########.fr       */
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
	static int	utte;

	if (utte == 0)
		utte = (*pargs)->info->utte;
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
	if ((*pargs)->id % 2 == 0)
	{
		usleep(400);
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
	static int	uttd;

	if (uttd == 0)
		uttd = (*pargs)->info->uttd;
	elapsed_time = elapsed_us(get_tv(), (*pargs)->lastmeal_tv);
	usec_to_die = uttd - elapsed_time;
	if (get_fork_if_possible(
			&((*pargs)->r_fork),
			&((*pargs)->l_fork), *pargs) == 1
	)
	{
		(*pargs)->n_eat++;
		statechange_and_log_eat(*pargs);
		return (0);
	}
	if (20 < usec_to_die && usec_to_die < 40)
		usleep(10);
	if (usec_to_die >= 40)
		usleep(20);
	return (0);
}

int	sleeping_routine(t_pargs **pargs)
{
	time_t		elapsed_time;
	static int	utts;

	if (utts == 0)
		utts = (*pargs)->info->utts;
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
