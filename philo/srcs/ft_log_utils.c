/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 05:18:09 by marvin            #+#    #+#             */
/*   Updated: 2025/10/10 05:19:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*create_ts_id_msg(t_pargs *pargs, t_tv tv, char *msg)
{
	time_t	ms;
	char	*ms_str;
	char	*res;

	if (pargs == NULL || msg == NULL)
		return (NULL);
	ms = elapsed_us(tv, pargs->start_tv);
	if (ms == 0)
		return (NULL);
	ms_str = ft_ltoa(ms / 1000);
	if (ms_str == NULL)
		return (NULL);
	res = ft_strjoin(ms_str, msg);
	if (res == NULL)
		return (NULL);
	free(ms_str);
	return (res);
}

int	append_log_buf(t_pargs *pargs, char *ts_id_msg)
{
	char	*tmp_buf;

	if (pargs == NULL || pargs->info == NULL || ts_id_msg == NULL)
		return (1);
	pthread_mutex_lock(pargs->info->log_mutex);
	if (pargs->info->log_buf == NULL)
		return (pthread_mutex_unlock(pargs->info->log_mutex), 1);
	tmp_buf = ft_strjoin(pargs->info->log_buf, ts_id_msg);
	free(ts_id_msg);
	if (tmp_buf == NULL)
		return (pthread_mutex_unlock(pargs->info->log_mutex), 1);
	free(pargs->info->log_buf);
	pargs->info->log_buf = tmp_buf;
	pthread_mutex_unlock(pargs->info->log_mutex);
	return (0);
}
