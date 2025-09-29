/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pinfo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 02:15:09 by marvin            #+#    #+#             */
/*   Updated: 2025/09/26 13:31:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_pinfo	*create_pinfo(int argc, char **argv)
{
	t_pinfo	*pinfo;

	if (argc != 5 && argc != 6)
		return (NULL);
	if (validate_args(argc, argv) != 1)
		return (NULL);
	pinfo = (t_pinfo *)malloc(sizeof(t_pinfo));
	if (pinfo == NULL)
		return (NULL);
	pinfo->n_philo = ft_atoi(argv[1]);
	pinfo->ttd = ft_atoi(argv[2]);
	pinfo->tte = ft_atoi(argv[3]);
	pinfo->tts = ft_atoi(argv[4]);
	pinfo->uttd = ft_atoi(argv[2]) * 1000;
	pinfo->utte = ft_atoi(argv[3]) * 1000;
	pinfo->utts = ft_atoi(argv[4]) * 1000;
	pinfo->log_buf = (char *)malloc(sizeof(char) * 1);
	pinfo->log_buf[0] = '\0';
	pinfo->all_philo_sign = ALL_PHILO_WAIT_FOR_START;
	gettimeofday(&(pinfo->start_tv), NULL);
	pinfo->must_eat = -1;
	if (argc == 6)
		pinfo->must_eat = ft_atoi(argv[5]);
	return (pinfo);
}
