/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 13:17:27 by marvin            #+#    #+#             */
/*   Updated: 2025/10/10 03:01:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	_log_loop(t_pinfo *info)
{
	pthread_mutex_lock(info->log_mutex);
	write(1, info->log_buf, ft_strlen(info->log_buf));
	free_str_set_null(&(info->log_buf));
	info->log_buf = (char *)malloc(sizeof(char) * 1);
	info->log_buf[0] = '\0';
	pthread_mutex_unlock(info->log_mutex);
	usleep(50);
}

void	*log_routine(void *args)
{
	t_pinfo	*info;
	char	*pdied;

	info = (t_pinfo *)args;
	while (get_cstate(info) == WAITING_FOR_START)
		usleep(100);
	while (get_cstate(info) == ALL_PHILO_LIVE && info->pfull != info->n_philo)
		_log_loop(info);
	if (info->pfull == info->n_philo)
		modify_common_state2(info, STOP_PHILO_SIM);
	pthread_mutex_lock(info->log_mutex);
	pdied = ft_strnstr(info->log_buf, "died", ft_strlen(info->log_buf));
	if (pdied != NULL)
	{
		write(1, info->log_buf, pdied - info->log_buf + 4);
		write(1, "\n", 1);
	}
	else
		write(1, info->log_buf, ft_strlen(info->log_buf));
	free_str_set_null(&(info->log_buf));
	pthread_mutex_unlock(info->log_mutex);
	return (NULL);
}

void	start_philo_simulation(int uwait, t_pinfo *pinfo)
{
	usleep(uwait);
	pthread_mutex_lock(pinfo->data_mutex);
	pinfo->common_state = ALL_PHILO_LIVE;
	pinfo->start_tv = get_tv();
	pthread_mutex_unlock(pinfo->data_mutex);
}

void	all_pthread_join(
	t_pinfo *pinfo,
	pthread_t *threads,
	pthread_t log_thread
)
{
	int	i;

	i = 0;
	while (i < pinfo->n_philo)
	{
		pthread_join(threads[i++], NULL);
	}
	pthread_join(log_thread, NULL);
}

int	main(int argc, char **argv)
{
	pthread_t	*threads;
	pthread_t	log_thread;
	t_pargs		**pargs_arr;
	t_pinfo		*pinfo;
	t_fork		**fork_arr;

	pinfo = create_pinfo(argc, argv);
	if (pinfo == NULL)
	{
		error_msg_on_validation();
		exit (1);
	}
	fork_arr = create_fork_arr(pinfo->n_philo);
	pargs_arr = create_pargs_arr(pinfo->n_philo, pinfo, fork_arr);
	pthread_create(&(log_thread), NULL, log_routine, pinfo);
	threads = create_pthreads_arr(pinfo->n_philo, pargs_arr);
	start_philo_simulation(300, pinfo);
	all_pthread_join(pinfo, threads, log_thread);
	free_pargs_arr(pargs_arr);
	free_fork_arr(fork_arr);
	free_pinfo(pinfo);
	free(threads);
	return (0);
}
