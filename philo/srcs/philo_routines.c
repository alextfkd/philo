/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:54:26 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/10/21 10:11:17 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#define IMMINENT_THRES 30
#define EATING_USLEEP 300
#define SLEEPING_USLEEP 300

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
	if (utte - elapsed_time < (*pargs)->uthres)
		auto_sleep(utte - elapsed_time);
	return (0);
}

int	initial_routine(t_pargs **pargs)
{
	int	res;

	usleep(ft_min((*pargs)->uttd / 5, 100 * (*pargs)->id));
	if ((*pargs)->id % 2 == 0)
		usleep(ft_min((*pargs)->uttd / 5, 100 * (*pargs)->n_philo));
	res = get_fork_if_possible(
			&((*pargs)->r_fork), &((*pargs)->l_fork), *pargs);
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
	if (uttd - elapsed_time < (*pargs)->uthres)
		auto_sleep(uttd - elapsed_time);
	res = get_fork_if_possible(
			&((*pargs)->r_fork), &((*pargs)->l_fork), *pargs);
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
		usleep(500);
		return (0);
	}
	if (utts - elapsed_time < (*pargs)->uthres)
		auto_sleep(utts - elapsed_time);
	return (0);
}
