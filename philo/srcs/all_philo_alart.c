/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_philo_alart.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 05:39:09 by marvin            #+#    #+#             */
/*   Updated: 2025/10/02 06:57:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_all_philo_alart	check_alart(t_pinfo *info)
{
	t_all_philo_alart	res;

	if (info == NULL)
		return (ALART_FAILURE);
	pthread_mutex_lock(info->philo_alart_mutex);
	res = info->all_philo_alart;
	pthread_mutex_unlock(info->philo_alart_mutex);
	return (res);
}

t_all_philo_alart	check_all_sign(t_pargs *pargs)
{
	return ((check_alart(pargs->info)));
}

void	modify_philo_alart(t_pargs **pargs, t_all_philo_alart alart)
{
	if (pargs == NULL || *pargs == NULL)
		return ;
	pthread_mutex_lock((*pargs)->info->philo_alart_mutex);
	(*pargs)->info->all_philo_alart = alart;
	pthread_mutex_unlock((*pargs)->info->philo_alart_mutex);
	return ;
}
