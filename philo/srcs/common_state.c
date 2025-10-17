/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 22:23:40 by tkatsuma          #+#    #+#           */
/*   Updated: 2025/10/17 22:26:00 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_common_state	get_cstate(t_pinfo *info)
{
	t_common_state	res;

	if (info == NULL)
		return (ALART_FAILURE);
	pthread_mutex_lock(info->data_mutex);
	res = info->common_state;
	pthread_mutex_unlock(info->data_mutex);
	return (res);
}

t_common_state	acquire_common_state(t_pargs *pargs)
{
	return ((get_cstate(pargs->info)));
}

void	modify_common_state(t_pargs *pargs, t_common_state cstate)
{
	if (pargs == NULL)
		return ;
	modify_common_state2((*pargs).info, cstate);
	return ;
}

void	modify_common_state2(t_pinfo *info, t_common_state cstate)
{
	if (info == NULL)
		return ;
	pthread_mutex_lock(info->data_mutex);
	info->common_state = cstate;
	pthread_mutex_unlock(info->data_mutex);
	return ;
}
