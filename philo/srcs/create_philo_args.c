/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 05:47:59 by marvin            #+#    #+#             */
/*   Updated: 2025/10/10 04:22:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_pargs	**create_empty_pargs_arr(int n);
static t_pargs	*create_pargs(int id, t_pinfo *info);
static t_pargs	*validate_pargs(t_pargs *pargs);
static void		_init_pargs(int id, t_pargs *pargs, t_pinfo *info);

t_pargs	**create_pargs_arr(int n, t_pinfo *info, t_fork **fork_arr)
{
	t_pargs		**pargs_arr;
	t_pargs		*pargs;
	int			i;
	int			id;

	if (n <= 0 || info == NULL)
		return (NULL);
	pargs_arr = create_empty_pargs_arr(n);
	if (pargs_arr == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		id = i + 1;
		pargs = create_pargs(id, info);
		if (pargs == NULL)
			return (free_pargs_arr(pargs_arr), NULL);
		pargs->r_fork = (fork_arr[i]);
		if (n > 1)
			pargs->l_fork = (fork_arr[(i + n - 1) % n]);
		pargs_arr[i++] = pargs;
	}
	return (pargs_arr);
}

static t_pargs	**create_empty_pargs_arr(int n)
{
	t_pargs		**pargs_arr;

	pargs_arr = (t_pargs **)malloc(sizeof(t_pargs) * n);
	if (pargs_arr == NULL)
		return (NULL);
	memset(pargs_arr, '\0', sizeof(t_pargs) * n);
	return (pargs_arr);
}

static t_pargs	*create_pargs(int id, t_pinfo *info)
{
	t_pargs	*pargs;

	if (info == NULL)
		return (NULL);
	pargs = (t_pargs *)malloc(sizeof(t_pargs));
	if (pargs == NULL)
		return (NULL);
	memset(pargs, '\0', sizeof(t_pargs));
	_init_pargs(id, pargs, info);
	pargs->msg_died = create_id_msg(id, LOG_DIED);
	pargs->msg_eat = create_id_msg(id, LOG_EATSTART);
	pargs->msg_sleep = create_id_msg(id, LOG_SLEEPSTART);
	pargs->msg_think = create_id_msg(id, LOG_THINKSTART);
	pargs->msg_fork = create_id_msg(id, LOG_TAKEFORK);
	return (validate_pargs(pargs));
}

static	void	_init_pargs(int id, t_pargs *pargs, t_pinfo *info)
{
	pthread_mutex_lock(info->data_mutex);
	pargs->n_philo = info->n_philo;
	pargs->id = id;
	pargs->info = info;
	pargs->l_fork = NULL;
	pargs->r_fork = NULL;
	pargs->n_eat = 0;
	pargs->uttd = info->uttd;
	pargs->utte = info->utte;
	pargs->utts = info->utts;
	gettimeofday(&(pargs->lastmeal_tv), NULL);
	pargs->pstatemodified_tv = pargs->lastmeal_tv;
	pargs->pstate = PHILO_WAITING_FOR_START;
	pargs->start_tv = info->start_tv;
	pthread_mutex_unlock(info->data_mutex);
}

static t_pargs	*validate_pargs(t_pargs *pargs)
{
	if ((pargs->msg_died == NULL)
		|| (pargs->msg_eat == NULL)
		|| (pargs->msg_sleep == NULL)
		|| (pargs->msg_think == NULL)
		|| (pargs->msg_fork == NULL)
	)
	{
		free_pargs(pargs);
		return (NULL);
	}
	return (pargs);
}
