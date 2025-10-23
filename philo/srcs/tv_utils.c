/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tv_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:58:45 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/10/23 05:58:56 by tkatsuma         ###   ########.fr       */
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
		if (write(1, "tv2str: tv.tv_sec > LONG_MAX - 1000000", 38) < 0)
			return (1);
		if (write(1, "|| tv.tv_sec < 0\n", 17) < 0)
			return (1);
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

void	auto_sleep(int remaining)
{
	if (remaining > 20000)
		usleep(remaining / 2);
	else if (remaining > 2000)
		usleep(1000);
	else if (remaining > 1000)
		usleep(500);
	else if (remaining > 200)
		usleep(100);
	else
		return ;
}
