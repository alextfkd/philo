/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 01:13:41 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/10/21 04:58:25 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	takefork_and_log(t_pargs *pargs)
{
	t_tv	tv;
	char	*ts_id_msg1;
	char	*ts_id_msg2;

	tv = get_tv();
	ts_id_msg1 = create_ts_id_msg(pargs, tv, pargs->msg_fork);
	if (ts_id_msg1 == NULL)
		return (1);
	if (append_log_buf_fork(pargs, ts_id_msg1) != 0)
		return (1);
	ts_id_msg2 = create_ts_id_msg(pargs, tv, pargs->msg_fork);
	if (ts_id_msg2 == NULL)
		return (1);
	if (append_log_buf_fork(pargs, ts_id_msg2) != 0)
		return (1);
	return (0);
}

int	statechange_and_log_died(t_pargs *pargs)
{
	t_tv	tv;
	char	*ts_id_msg;

	tv = get_tv();
	ts_id_msg = create_ts_id_msg(pargs, tv, pargs->msg_died);
	if (ts_id_msg == NULL)
		return (1);
	if (append_log_buf_fork(pargs, ts_id_msg) != 0)
		return (1);
	pargs->pstate = PHILO_DIED;
	pargs->pstatemodified_tv = tv;
	return (0);
}

int	statechange_and_log_eat(t_pargs *pargs)
{
	t_tv	tv;
	char	*ts_id_msg;

	tv = get_tv();
	ts_id_msg = create_ts_id_msg(pargs, tv, pargs->msg_eat);
	if (ts_id_msg == NULL)
		return (1);
	if (append_log_buf_fork(pargs, ts_id_msg) != 0)
		return (1);
	if (pargs->info->must_eat == pargs->n_eat)
		pargs->info->pfull++;
	pargs->pstate = PHILO_EATING;
	pargs->lastmeal_tv = tv;
	pargs->pstatemodified_tv = tv;
	return (0);
}

int	statechange_and_log_sleep(t_pargs *pargs)
{
	t_tv	tv;
	char	*ts_id_msg;

	tv = get_tv();
	ts_id_msg = create_ts_id_msg(pargs, tv, pargs->msg_sleep);
	if (ts_id_msg == NULL)
		return (1);
	if (append_log_buf_fork(pargs, ts_id_msg) != 0)
		return (1);
	pargs->pstate = PHILO_SLEEPING;
	pargs->pstatemodified_tv = tv;
	return (0);
}

int	statechange_and_log_think(t_pargs *pargs)
{
	t_tv	tv;
	char	*ts_id_msg;

	tv = get_tv();
	ts_id_msg = create_ts_id_msg(pargs, tv, pargs->msg_think);
	if (ts_id_msg == NULL)
		return (1);
	if (append_log_buf_fork(pargs, ts_id_msg) != 0)
		return (1);
	pargs->pstate = PHILO_THINKING;
	pargs->pstatemodified_tv = tv;
	return (0);
}
