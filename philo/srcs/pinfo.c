/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pinfo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 02:15:09 by marvin            #+#    #+#             */
/*   Updated: 2025/09/21 02:15:20 by marvin           ###   ########.fr       */
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
	pinfo->must_eat = -1;
	if (argc == 6)
		pinfo->must_eat = ft_atoi(argv[5]);
	return (pinfo);
}
