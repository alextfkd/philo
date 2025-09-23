/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 01:09:27 by marvin            #+#    #+#             */
/*   Updated: 2025/09/21 01:10:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
Converts the initial portion of the string pointed to by nptr to int.
'-' -> negative int, '+' -> positive int, '--' -> 0.
*/
int	ft_atoi(const char *nptr)
{
	long	res;
	long	sign;

	res = 0;
	sign = 1;
	while (ft_isspace(*nptr) != 0)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	while (ft_isdigit(*nptr) != 0)
	{
		res = 10 * res + (*nptr - '0');
		nptr++;
	}
	return ((int)(res * sign));
}
