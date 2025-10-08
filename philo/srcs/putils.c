/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 07:47:20 by marvin            #+#    #+#             */
/*   Updated: 2025/10/07 12:44:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_pinfo(t_pinfo *pinfo)
{
	if (pinfo == NULL)
	{
		printf("ERROR: NO pinfo!!!");
		return ;
	}
	printf("philo: 	       %d\n", pinfo->n_philo);
	printf("time to die:   %d\n", pinfo->ttd);
	printf("time to eat:   %d\n", pinfo->tte);
	printf("time to sleep: %d\n", pinfo->tts);
	printf("n must eat:    %d\n", pinfo->must_eat);
}

void	free_str_set_null(char **str)
{
	if (*str != NULL)
	{
		free(*str);
		*str = NULL;
	}
	return ;
}

void	free_pargs(t_pargs *pargs)
{
	if (pargs == NULL)
		return ;
	if (pargs->msg_died != NULL)
		free(pargs->msg_died);
	if (pargs->msg_eat != NULL)
		free(pargs->msg_eat);
	if (pargs->msg_fork != NULL)
		free(pargs->msg_fork);
	if (pargs->msg_sleep != NULL)
		free(pargs->msg_sleep);
	if (pargs->msg_think != NULL)
		free(pargs->msg_think);
	free(pargs);
}

void	free_pargs_arr(t_pargs **pargs_arr)
{
	int	i;

	if (pargs_arr == NULL)
		return ;
	i = 0;
	while (pargs_arr[i] != NULL)
	{
		free_pargs(pargs_arr[i]);
		i++;
	}
	free(pargs_arr);
}

void	free_pinfo(t_pinfo *pinfo)
{
	pthread_mutex_lock(pinfo->log_mutex);
	if (pinfo->log_buf != NULL)
		free(pinfo->log_buf);
	pthread_mutex_unlock(pinfo->log_mutex);
	pthread_mutex_destroy(pinfo->data_mutex);
	pthread_mutex_destroy(pinfo->log_mutex);
	pthread_mutex_destroy(pinfo->philo_alart_mutex);
	free(pinfo->data_mutex);
	free(pinfo->log_mutex);
	free(pinfo->philo_alart_mutex);
	free(pinfo);
}
