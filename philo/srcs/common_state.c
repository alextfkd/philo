/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_state.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 05:39:09 by marvin            #+#    #+#             */
/*   Updated: 2025/10/10 01:51:14 by marvin           ###   ########.fr       */
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
