/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pinfo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 02:15:09 by marvin            #+#    #+#             */
/*   Updated: 2025/10/03 23:10:06 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	_info_atoi_argv(t_pinfo *pinfo, char **argv)
{
	pinfo->n_philo = ft_atoi(argv[1]);
	pinfo->ttd = ft_atoi(argv[2]);
	pinfo->tte = ft_atoi(argv[3]);
	pinfo->tts = ft_atoi(argv[4]);
	pinfo->uttd = pinfo->ttd * 1000;
	pinfo->utte = pinfo->tte * 1000;
	pinfo->utts = pinfo->tts * 1000;
	pinfo->pfull = 0;
	return (0);
}

static int	_set_mutexes(t_pinfo *pinfo)
{
	size_t	musize;

	musize = sizeof(pthread_mutex_t);
	pinfo->philo_alart_mutex = (pthread_mutex_t *)malloc(musize);
	if (pinfo->philo_alart_mutex == NULL)
		return (-1);
	pthread_mutex_init(pinfo->philo_alart_mutex, NULL);
	pinfo->log_mutex = (pthread_mutex_t *)malloc(musize);
	if (pinfo->log_mutex == NULL)
		return (-1);
	pthread_mutex_init(pinfo->log_mutex, NULL);
	pinfo->log_buf = (char *)malloc(sizeof(char) * 1);
	if (pinfo->log_buf == NULL)
		return (-1);
	pinfo->log_buf[0] = '\0';
	pinfo->all_philo_alart = ALL_PHILO_WAIT_FOR_START;
	return (0);
}

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
	_info_atoi_argv(pinfo, argv);
	_set_mutexes(pinfo);
	gettimeofday(&(pinfo->start_tv), NULL);
	pinfo->must_eat = -1;
	if (argc == 6)
		pinfo->must_eat = ft_atoi(argv[5]);
	return (pinfo);
}
