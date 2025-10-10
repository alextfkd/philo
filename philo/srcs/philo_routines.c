/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:54:26 by marvin            #+#    #+#             */
/*   Updated: 2025/10/10 06:26:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#define IMMINENT_THRES 30
#define EATING_USLEEP 100
#define SLEEPING_USLEEP 100

int	died_routine(t_pargs **pargs)
{
	int	res;

	res = statechange_and_log_died(*pargs);
	if (res == 1)
		(*pargs)->pstate = PHILO_FAILURE;
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
		res = put_fork_if_possible(
				&((*pargs)->r_fork), &((*pargs)->l_fork), *pargs);
		if (res == -1)
			return (1);
		res = statechange_and_log_sleep(*pargs);
		if (res != 0)
			return (1);
		return (0);
	}
	if (utte - elapsed_time < IMMINENT_THRES + EATING_USLEEP)
		return (0);
	usleep(EATING_USLEEP);
	return (0);
}

int	initial_routine(t_pargs **pargs)
{
	int	res;

	usleep((400 / (*pargs)->n_philo) * ((*pargs)->id) / 2);
	if ((*pargs)->id % 2 == 0)
	{
		usleep(80);
		(*pargs)->lastmeal_tv = get_tv();
	}
	res = get_fork_if_possible(
			&((*pargs)->r_fork), &((*pargs)->l_fork), *pargs);
	if (res == -1)
		return (1);
	if (res == 1)
	{
		(*pargs)->n_eat++;
		res = statechange_and_log_eat(*pargs);
		return (res);
	}
	res = statechange_and_log_think(*pargs);
	if (res == -1)
		return (1);
	return (0);
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
	if (res == -1)
		return (1);
	if (res == 1)
	{
		(*pargs)->n_eat++;
		res = statechange_and_log_eat(*pargs);
		return (res);
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
		res = statechange_and_log_think(*pargs);
		if (res == 1)
			return (1);
		return (thinking_routine(pargs));
	}
	if (utts - elapsed_time < IMMINENT_THRES + SLEEPING_USLEEP)
		return (0);
	else
		usleep(SLEEPING_USLEEP);
	return (0);
}
