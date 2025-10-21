/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 01:13:41 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/10/21 10:24:39 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	takefork_and_log(t_pargs *pargs)
{
	t_tv	tv;

	if (append_log_buf2(pargs, pargs->msg_fork, &tv) != 0)
		return (1);
	if (append_log_buf2(pargs, pargs->msg_fork, &tv) != 0)
		return (1);
	return (0);
}

int	statechange_and_log_died(t_pargs *pargs)
{
	if (append_log_buf2(
			pargs,
			pargs->msg_died,
			&(pargs->pstatemodified_tv)
		) != 0
	)
		return (1);
	pargs->pstate = PHILO_DIED;
	return (0);
}

int	statechange_and_log_eat(t_pargs *pargs)
{
	if (append_log_buf2(
			pargs,
			pargs->msg_eat,
			&(pargs->pstatemodified_tv)
		) != 0
	)
		return (1);
	pthread_mutex_lock(pargs->info->data_mutex);
	if (pargs->info->must_eat == pargs->n_eat)
		pargs->info->pfull++;
	pthread_mutex_unlock(pargs->info->data_mutex);
	pargs->pstate = PHILO_EATING;
	pargs->lastmeal_tv = pargs->pstatemodified_tv;
	return (0);
}

int	statechange_and_log_sleep(t_pargs *pargs)
{
	if (append_log_buf2(
			pargs,
			pargs->msg_sleep,
			&(pargs->pstatemodified_tv)
		) != 0
	)
		return (1);
	pargs->pstate = PHILO_SLEEPING;
	return (0);
}

int	statechange_and_log_think(t_pargs *pargs)
{
	if (append_log_buf2(
			pargs,
			pargs->msg_think,
			&(pargs->pstatemodified_tv)
		) != 0
	)
		return (1);
	pargs->pstate = PHILO_THINKING;
	return (0);
}
