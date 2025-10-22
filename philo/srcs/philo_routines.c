/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:54:26 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/10/22 02:29:50 by tkatsuma         ###   ########.fr       */
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
	int		res;
	t_pargs	*pa;

	pa = (*pargs);
	if ((*pargs)->n_philo % 2 == 0 && ((*pargs)->id % 2 == 0))
		usleep(ft_min((*pargs)->uttd / 5, 100 * (*pargs)->n_philo));
	if ((*pargs)->n_philo % 2 == 1)
		usleep(pa->uttd / 2 / (pa->n_philo + 1) * (pa->id - 1));
	if ((*pargs)->n_philo % 2 == 1 && ((*pargs)->id % 2 == 0))
		usleep(200 * (*pargs)->n_philo);
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
	time_t		thinking_time;
	int			uttd;

	uttd = (*pargs)->uttd;
	elapsed_time = elapsed_us(get_tv(), (*pargs)->lastmeal_tv);
	thinking_time = elapsed_us(get_tv(), (*pargs)->pstatemodified_tv);
	if ((*pargs)->n_philo % 2 == 1 && thinking_time < (*pargs)->utte)
		if ((*pargs)->lastmeal_tv.tv_usec != (*pargs)->start_tv.tv_usec)
			return (usleep((*pargs)->utte - thinking_time), 0);
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
		return (0);
	}
	if (utts - elapsed_time < (*pargs)->uthres)
		auto_sleep(utts - elapsed_time);
	return (0);
}
