/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 01:13:41 by marvin            #+#    #+#             */
/*   Updated: 2025/09/22 14:42:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_output(int ts, int x, char *msg)
{
	printf("%d %d %s\n", ts, x, msg);
}

void	log_state(int ts, int x, int state)
{
	if (state == STATE_TAKEFORK)
		printf("%d %d %s\n", ts, x, LOG_TAKEFORK);
	else if (state == STATE_EAT)
		printf("%d %d %s\n", ts, x, LOG_EATSTART);
	else if (state == STATE_SLEEP)
		printf("%d %d %s\n", ts, x, LOG_SLEEPSTART);
	else if (state == STATE_THINK)
		printf("%d %d %s\n", ts, x, LOG_THINKSTART);
	else if (state == STATE_DIED)
		printf("%d %d %s\n", ts, x, LOG_DIED);
	else
		printf("ERROR\n");
}

