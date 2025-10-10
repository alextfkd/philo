/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pinfo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 02:15:09 by marvin            #+#    #+#             */
/*   Updated: 2025/10/10 07:59:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	_fill_pinfo_data(t_pinfo *pinfo, int argc, char **argv);
static int	_set_cstate_data_and_mutex(t_pinfo *pinfo);
static int	_set_logbuf_and_mutex(t_pinfo *pinfo);
static int	_create_result_arr(t_pinfo *pinfo, int n);

t_pinfo	*create_pinfo(int argc, char **argv)
{
	t_pinfo			*pinfo;

	if (argc != 5 && argc != 6)
		return (NULL);
	if (validate_args(argc, argv) != 1)
		return (NULL);
	pinfo = (t_pinfo *)malloc(sizeof(t_pinfo));
	if (pinfo == NULL)
		return (NULL);
	if ((_set_cstate_data_and_mutex(pinfo) == -1)
		|| (_set_logbuf_and_mutex(pinfo) == -1)
	)
	{
		return (free(pinfo), NULL);
	}
	_fill_pinfo_data(pinfo, argc, argv);
	if (_create_result_arr(pinfo, pinfo->n_philo) == -1)
		return (free(pinfo), NULL);
	return (pinfo);
}

static void	_fill_pinfo_data(t_pinfo *pinfo, int argc, char **argv)
{
	pthread_mutex_lock(pinfo->data_mutex);
	gettimeofday(&(pinfo->start_tv), NULL);
	pinfo->n_philo = ft_atoi(argv[1]);
	pinfo->ttd = ft_atoi(argv[2]);
	pinfo->tte = ft_atoi(argv[3]);
	pinfo->tts = ft_atoi(argv[4]);
	pinfo->uttd = pinfo->ttd * 1000;
	pinfo->utte = pinfo->tte * 1000;
	pinfo->utts = pinfo->tts * 1000;
	pinfo->pfull = 0;
	pinfo->must_eat = -1;
	if (argc == 6)
		pinfo->must_eat = ft_atoi(argv[5]);
	pinfo->common_state = WAITING_FOR_START;
	pthread_mutex_unlock(pinfo->data_mutex);
}

static int	_set_cstate_data_and_mutex(t_pinfo *pinfo)
{
	size_t	musize;

	musize = sizeof(pthread_mutex_t);
	pinfo->data_mutex = (pthread_mutex_t *)malloc(musize);
	if (pinfo->data_mutex == NULL)
		return (-1);
	pthread_mutex_init(pinfo->data_mutex, NULL);
	return (0);
}

static int	_set_logbuf_and_mutex(t_pinfo *pinfo)
{
	size_t	musize;

	musize = sizeof(pthread_mutex_t);
	pinfo->log_mutex = (pthread_mutex_t *)malloc(musize);
	if (pinfo->log_mutex == NULL)
		return (-1);
	pthread_mutex_init(pinfo->log_mutex, NULL);
	pthread_mutex_lock(pinfo->log_mutex);
	pinfo->log_buf = (char *)malloc(sizeof(char) * 1);
	if (pinfo->log_buf == NULL)
	{
		pthread_mutex_unlock(pinfo->log_mutex);
		return (-1);
	}
	pinfo->log_buf[0] = '\0';
	pthread_mutex_unlock(pinfo->log_mutex);
	return (0);
}

static int	_create_result_arr(t_pinfo *pinfo, int n)
{
	int	*arr;
	int	i;

	arr = (int *)malloc(sizeof(int) * (n + 2));
	if (arr == NULL)
		return (-1);
	i = 0;
	while (i < n + 2)
		arr[i++] = 0;
	pinfo->exit_status = arr;
	return (0);
}
