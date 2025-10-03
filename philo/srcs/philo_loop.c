/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 01:24:07 by marvin            #+#    #+#             */
/*   Updated: 2025/10/03 23:04:21 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_if_alive(t_pargs **pargs)
{
	if (elapsed_us(get_tv(), (*pargs)->lastmeal_tv) > ((*pargs)->info->uttd))
	{
		statechange_and_log_died(*pargs);
		return (0);
	}
	return (1);
}

static int	failure_routine(t_pargs **pargs)
{
	(void)pargs;
	return (0);
}

void	loop_routine(t_pargs **pargs)
{
	if ((*pargs)->pstate == PHILO_DIED)
		died_routine(pargs);
	else if ((*pargs)->pstate == PHILO_INITIAL_STATE)
		initial_routine(pargs);
	else if ((*pargs)->pstate == PHILO_EATING)
		eating_routine(pargs);
	else if ((*pargs)->pstate == PHILO_THINKING)
		thinking_routine(pargs);
	else if ((*pargs)->pstate == PHILO_SLEEPING)
		sleeping_routine(pargs);
	else if ((*pargs)->pstate == PHILO_FAILURE)
		failure_routine(pargs);
	else
		failure_routine(pargs);
	if (check_if_alive(pargs) == 0)
		return ;
}

void	*start_routine(void *args)
{
	t_pargs	*pargs;

	pargs = (t_pargs *)args;
	if (pargs == NULL)
		return (NULL);
	pargs->pstate = PHILO_WAITING_FOR_START;
	while (check_all_sign(pargs) == ALL_PHILO_WAIT_FOR_START)
	{
		usleep(5);
	}
	gettimeofday(&(pargs->info->start_tv), NULL);
	pargs->lastmeal_tv.tv_sec = pargs->info->start_tv.tv_sec;
	pargs->lastmeal_tv.tv_usec = pargs->info->start_tv.tv_usec;
	pargs->pstate = PHILO_INITIAL_STATE;
	while (pargs->pstate != PHILO_DIED && pargs->pstate != PHILO_FAILURE)
	{
		if (check_all_sign(pargs) == ANY_PHILO_DIED)
			break ;
		loop_routine(&pargs);
	}
	modify_philo_alart(&pargs, ANY_PHILO_DIED);
	return (NULL);
}
