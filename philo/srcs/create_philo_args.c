/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 05:47:59 by marvin            #+#    #+#             */
/*   Updated: 2025/10/03 22:07:39 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	pargs->id = id;
	pargs->info = info;
	pargs->n_eat = 0;
	gettimeofday(&(pargs->lastmeal_tv), NULL);
	pargs->pstatemodified_tv.tv_sec = pargs->lastmeal_tv.tv_sec;
	pargs->pstatemodified_tv.tv_usec = pargs->lastmeal_tv.tv_usec;
	pargs->l_fork = NULL;
	pargs->r_fork = NULL;
	pargs->msg_died = create_id_msg(id, LOG_DIED);
	pargs->msg_eat = create_id_msg(id, LOG_EATSTART);
	pargs->msg_sleep = create_id_msg(id, LOG_SLEEPSTART);
	pargs->msg_think = create_id_msg(id, LOG_THINKSTART);
	pargs->msg_fork = create_id_msg(id, LOG_TAKEFORK);
	pargs->pstate = PHILO_WAITING_FOR_START;
	return (pargs);
}

t_pargs	**create_pargs_arr(int n, t_pinfo *info, t_fork **fork_arr)
{
	t_pargs		**pargs_arr;
	t_pargs		*pargs;
	int			i;
	int			id;

	if (n <= 0 || info == NULL)
		return (NULL);
	pargs_arr = create_empty_pargs_arr(n + 1);
	if (pargs_arr == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		id = i + 1;
		pargs = create_pargs(id, info);
		pargs->r_fork = (fork_arr[i]);
		if (n > 1)
			pargs->l_fork = (fork_arr[(i + n - 1) % n]);
		if (pargs == NULL)
			return (free_pargs_arr(pargs_arr), NULL);
		pargs_arr[i++] = pargs;
	}
	return (pargs_arr);
}
