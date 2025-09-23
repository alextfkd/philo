/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 07:47:20 by marvin            #+#    #+#             */
/*   Updated: 2025/09/22 07:47:51 by marvin           ###   ########.fr       */
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
