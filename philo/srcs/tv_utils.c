/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tv_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:58:45 by marvin            #+#    #+#             */
/*   Updated: 2025/10/02 15:58:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_tv	get_tv(void)
{
	t_tv	tv;

	gettimeofday(&tv, NULL);
	return (tv);
}

time_t	tv2time_t(t_tv tv)
{
	time_t	usec;

	if (tv.tv_sec > LONG_MAX - 1000000 || tv.tv_sec < 0)
	{
		write(2, "tv2str: tv.tv_sec > LONG_MAX - 1000000 \
			|| tv.tv_sec < 0\n", 56);
		return (0);
	}
	usec = tv.tv_sec * 1000000 + tv.tv_usec;
	return (usec);
}

// Returns elapsed time in usec.
time_t	elapsed_us(t_tv current_tv, t_tv initial_tv)
{
	t_tv	tv;

	tv.tv_sec = current_tv.tv_sec - initial_tv.tv_sec;
	tv.tv_usec = current_tv.tv_usec - initial_tv.tv_usec;
	if (tv.tv_usec < 0)
	{
		tv.tv_sec--;
		tv.tv_usec += 1000000;
	}
	return (tv2time_t(tv));
}
