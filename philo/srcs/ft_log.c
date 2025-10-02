/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 01:13:41 by marvin            #+#    #+#             */
/*   Updated: 2025/10/02 16:05:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	takefork_and_log(t_pargs *pargs)
{
	t_tv	tv;
	time_t	ms;
	char	*ms_str;
	char	*out;
	char	*tmp;

	pthread_mutex_lock(pargs->info->log_mutex);
	if (pargs->info->log_buf == NULL)
	{
		pthread_mutex_unlock(pargs->info->log_mutex);
		return ;
	}
	tv = get_tv();
	ms = elapsed_us(tv, pargs->info->start_tv);
	ms_str = ft_ltoa(ms / 1000);
	out = ft_strjoin(ms_str, pargs->msg_fork);
	tmp = ft_strjoin(pargs->info->log_buf, out);
	free(pargs->info->log_buf);
	pargs->info->log_buf = tmp;
	pthread_mutex_unlock(pargs->info->log_mutex);
	free (ms_str);
	free (out);
}

void	statechange_and_log_died(t_pargs *pargs)
{
	t_tv	tv;
	time_t	ms;
	char	*ms_str;
	char	*out;
	char	*tmp;

	pthread_mutex_lock(pargs->info->log_mutex);
	if (pargs->info->log_buf == NULL)
	{
		pthread_mutex_unlock(pargs->info->log_mutex);
		return ;
	}
	tv = get_tv();
	ms = elapsed_us(tv, pargs->info->start_tv);
	ms_str = ft_ltoa(ms / 1000);
	out = ft_strjoin(ms_str, pargs->msg_died);
	tmp = ft_strjoin(pargs->info->log_buf, out);
	free(pargs->info->log_buf);
	pargs->info->log_buf = tmp;
	pthread_mutex_unlock(pargs->info->log_mutex);
	pargs->pstate = PHILO_DIED;
	pargs->pstatemodified_tv.tv_sec = tv.tv_sec;
	pargs->pstatemodified_tv.tv_usec = tv.tv_usec;
	free (ms_str);
	free (out);
}

void	statechange_and_log_eat(t_pargs *pargs)
{
	t_tv	tv;
	char	*ms_str;
	char	*out;
	char	*tmp;

	pthread_mutex_lock(pargs->info->log_mutex);
	if (pargs->info->log_buf == NULL)
	{
		pthread_mutex_unlock(pargs->info->log_mutex);
		return ;
	}
	tv = get_tv();
	ms_str = ft_ltoa(elapsed_us(tv, pargs->info->start_tv) / 1000);
	out = ft_strjoin(ms_str, pargs->msg_eat);
	tmp = ft_strjoin(pargs->info->log_buf, out);
	free(pargs->info->log_buf);
	pargs->info->log_buf = tmp;
	pthread_mutex_unlock(pargs->info->log_mutex);
	pargs->pstate = PHILO_EATING;
	pargs->lastmeal_tv.tv_sec = tv.tv_sec;
	pargs->lastmeal_tv.tv_usec = tv.tv_usec;
	pargs->pstatemodified_tv.tv_sec = tv.tv_sec;
	pargs->pstatemodified_tv.tv_usec = tv.tv_usec;
	free (ms_str);
	free (out);
}

void	statechange_and_log_sleep(t_pargs *pargs)
{
	t_tv	tv;
	time_t	ms;
	char	*ms_str;
	char	*out;
	char	*tmp;

	pthread_mutex_lock(pargs->info->log_mutex);
	if (pargs->info->log_buf == NULL)
	{
		pthread_mutex_unlock(pargs->info->log_mutex);
		return ;
	}
	tv = get_tv();
	ms = elapsed_us(tv, pargs->info->start_tv);
	ms_str = ft_ltoa(ms / 1000);
	out = ft_strjoin(ms_str, pargs->msg_sleep);
	tmp = ft_strjoin(pargs->info->log_buf, out);
	free(pargs->info->log_buf);
	pargs->info->log_buf = tmp;
	pthread_mutex_unlock(pargs->info->log_mutex);
	pargs->pstate = PHILO_SLEEPING;
	pargs->pstatemodified_tv.tv_sec = tv.tv_sec;
	pargs->pstatemodified_tv.tv_usec = tv.tv_usec;
	free (ms_str);
	free (out);
}

void	statechange_and_log_think(t_pargs *pargs)
{
	t_tv	tv;
	time_t	ms;
	char	*ms_str;
	char	*out;
	char	*tmp;

	pthread_mutex_lock(pargs->info->log_mutex);
	if (pargs->info->log_buf == NULL)
	{
		pthread_mutex_unlock(pargs->info->log_mutex);
		return ;
	}
	tv = get_tv();
	ms = elapsed_us(tv, pargs->info->start_tv);
	ms_str = ft_ltoa(ms / 1000);
	out = ft_strjoin(ms_str, pargs->msg_think);
	tmp = ft_strjoin(pargs->info->log_buf, out);
	free(pargs->info->log_buf);
	pargs->info->log_buf = tmp;
	pthread_mutex_unlock(pargs->info->log_mutex);
	pargs->pstate = PHILO_THINKING;
	pargs->pstatemodified_tv.tv_sec = tv.tv_sec;
	pargs->pstatemodified_tv.tv_usec = tv.tv_usec;
	free (ms_str);
	free (out);
}
