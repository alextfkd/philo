/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 01:24:07 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/10/17 16:53:48 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	if_philo_starved(t_pargs **pargs);
static int	philo_loop_routine(t_pargs **pargs);
static void	sync_start_tv(t_pargs *pargs);

void	*philo_thread_action(void *args)
{
	t_pargs	*pargs;

	pargs = (t_pargs *)args;
	if (pargs == NULL)
		return (NULL);
	pargs->pstate = PHILO_WAITING_FOR_START;
	while (acquire_common_state(pargs) == WAITING_FOR_START)
		usleep(5);
	pargs->pstate = PHILO_INITIAL_STATE;
	sync_start_tv(pargs);
	while (pargs->pstate != PHILO_DIED)
	{
		if (acquire_common_state(pargs) == STOP_PHILO_SIM)
			break ;
		else if (pargs->pstate == PHILO_FAILURE)
			break ;
		if (philo_loop_routine(&pargs) == 1)
			break ;
	}
	modify_common_state(pargs, STOP_PHILO_SIM);
	return (0);
}

static void	sync_start_tv(t_pargs *pargs)
{
	pthread_mutex_lock(pargs->info->data_mutex);
	pargs->start_tv = pargs->info->start_tv;
	pargs->lastmeal_tv = pargs->info->start_tv;
	pthread_mutex_unlock(pargs->info->data_mutex);
}

static int	philo_loop_routine(t_pargs **pargs)
{
	int	fail_flag;

	fail_flag = 0;
	if (if_philo_starved(pargs) == 1)
		return (fail_flag);
	if ((*pargs)->pstate == PHILO_DIED)
		fail_flag = died_routine(pargs);
	else if ((*pargs)->pstate == PHILO_INITIAL_STATE)
		fail_flag = initial_routine(pargs);
	else if ((*pargs)->pstate == PHILO_EATING)
		fail_flag = eating_routine(pargs);
	else if ((*pargs)->pstate == PHILO_THINKING)
		fail_flag = thinking_routine(pargs);
	else if ((*pargs)->pstate == PHILO_SLEEPING)
		fail_flag = sleeping_routine(pargs);
	else
		fail_flag = 1;
	return (fail_flag);
}

static int	if_philo_starved(t_pargs **pargs)
{
	int	uttd;

	uttd = (*pargs)->uttd;
	if (elapsed_us(get_tv(), (*pargs)->lastmeal_tv) > uttd)
	{
		statechange_and_log_died(*pargs);
		return (1);
	}
	return (0);
}
