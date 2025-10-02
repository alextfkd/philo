/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:54:26 by marvin            #+#    #+#             */
/*   Updated: 2025/10/02 01:04:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	died_routine(t_pargs **pargs)
{
	statechange_and_log_died(*pargs);
	return (0);
}

int	eating_routine(t_pargs **pargs)
{
	if (elapsed_us(
			get_tv(),
			(*pargs)->pstatemodified_tv) > ((*pargs)->info->utte)
	)
	{
		put_fork_if_possible(&((*pargs)->r_fork), &((*pargs)->l_fork), *pargs);
		statechange_and_log_sleep(*pargs);
		return (0);
	}
	usleep(1);
	return (0);
}

int	initial_routine(t_pargs **pargs)
{
	if ((*pargs)->id % 2 == 0)
		usleep(500);
	if (get_fork_if_possible(
			&((*pargs)->r_fork),
			&((*pargs)->l_fork), *pargs) == 1
	)
	{
		statechange_and_log_eat(*pargs);
	}
	else
	{
		statechange_and_log_think(*pargs);
		usleep(10);
	}
	return (0);
}

int	thinking_routine(t_pargs **pargs)
{
	if (get_fork_if_possible(
			&((*pargs)->r_fork),
			&((*pargs)->l_fork), *pargs) == 1
	)
	{
		statechange_and_log_eat(*pargs);
	}
	else
	{
		usleep(10);
	}
	(*pargs)->initial_flag = 0;
	return (0);
}

int	sleeping_routine(t_pargs **pargs)
{
	if (elapsed_us(
			get_tv(),
			(*pargs)->pstatemodified_tv) > ((*pargs)->info->utts)
	)
	{
		statechange_and_log_think(*pargs);
		thinking_routine(pargs);
	}
	return (0);
}
