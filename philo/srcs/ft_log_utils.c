/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 05:18:09 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/10/17 16:54:40 by tkatsuma         ###   ########.fr       */
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
	pthread_mutex_lock(pargs->info->data_mutex);
	if (pargs->info->log_buf == NULL)
	{
		pthread_mutex_unlock(pargs->info->data_mutex);
		return (pthread_mutex_unlock(pargs->info->log_mutex), 1);
	}
	tmp_buf = ft_strjoin(pargs->info->log_buf, ts_id_msg);
	free_str_set_null(&ts_id_msg);
	if (tmp_buf == NULL)
	{
		pthread_mutex_unlock(pargs->info->data_mutex);
		return (pthread_mutex_unlock(pargs->info->log_mutex), 1);
	}
	free_str_set_null(&pargs->info->log_buf);
	pargs->info->log_buf = tmp_buf;
	pthread_mutex_unlock(pargs->info->data_mutex);
	pthread_mutex_unlock(pargs->info->log_mutex);
	return (0);
}

int	_log_loop(t_pinfo *info)
{
	pthread_mutex_lock(info->log_mutex);
	write(1, info->log_buf, ft_strlen(info->log_buf));
	free_str_set_null(&(info->log_buf));
	info->log_buf = (char *)malloc(sizeof(char) * 1);
	if (info->log_buf == NULL)
	{
		pthread_mutex_unlock(info->log_mutex);
		return (1);
	}
	info->log_buf[0] = '\0';
	pthread_mutex_unlock(info->log_mutex);
	usleep(50);
	return (0);
}

void	*_log_routine(void *args)
{
	t_pinfo	*info;
	char	*pdied;

	info = (t_pinfo *)args;
	while (get_cstate(info) == WAITING_FOR_START)
		usleep(100);
	while (get_cstate(info) == ALL_PHILO_LIVE && info->pfull != info->n_philo)
		if (_log_loop(info) != 0)
			break ;
	pthread_mutex_lock(info->log_mutex);
	if (info->pfull == info->n_philo)
	{
		modify_common_state2(info, STOP_PHILO_SIM);
		write(1, info->log_buf, ft_strlen(info->log_buf));
		free_str_set_null(&(info->log_buf));
		pthread_mutex_unlock(info->log_mutex);
		return (0);
	}
	pdied = ft_strnstr(info->log_buf, "died", ft_strlen(info->log_buf));
	write(1, info->log_buf, pdied - info->log_buf + 4);
	write(1, "\n", 1);
	free_str_set_null(&(info->log_buf));
	pthread_mutex_unlock(info->log_mutex);
	return (0);
}
