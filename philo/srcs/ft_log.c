/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 01:13:41 by marvin            #+#    #+#             */
/*   Updated: 2025/09/25 09:54:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_output(long ms, int philo_id, char *msg)
{
	printf("%ld %d %s\n", ms, philo_id, msg);
}

char	*tv2str(t_tv tv)
{
	char	*sec_str;
	char	*usec_str;
	char	*ptr;
	char	*tv_str;

	sec_str = ft_ltoa(tv.tv_sec);
	usec_str = ft_ltoa(tv.tv_sec + 1000000);
	ptr = usec_str;
	ptr += 4 * sizeof(char);
	while (*ptr)
		*ptr++ = '\0';
	usec_str++;
	tv_str = ft_strjoin(sec_str, usec_str);
	free(sec_str);
	usec_str--;
	free(usec_str);
	printf("TEST: tv2str -> %s\n", tv_str);
	return (tv_str);
}

//log_output(subtract_tv_as_msec(get_tv(), (*pargs)->info->start_tv), (*pargs)->id, LOG_DIED);

void	log_output_tv(t_tv curtv, t_tv initv, int philo_id, char *msg)
{
	t_tv	tv;
	char	*tv_str;

	tv.tv_sec = curtv.tv_sec - initv.tv_sec;
	tv.tv_usec = curtv.tv_usec - initv.tv_usec;
	if (tv.tv_usec < 0)
	{
		tv.tv_sec--;
		tv.tv_usec += 1000000;
	}
	tv_str = tv2str(tv);
	printf("TEST2: tv2str -> %s\n", tv_str);
	(void)philo_id;
	(void)msg;
	//ft_strjoin(tv2str)

}

int	thread_safe_write_nl(int fd, char *s, int len)
{
	pthread_mutex_t	mutex;
	int				res;

	res = 0;
	pthread_mutex_lock(&mutex);
	res += write(fd, s, len);
	res += write(fd, "\n", 1);
	pthread_mutex_unlock(&mutex);
	return (res);
}

/*
void	log_state(int ts, int x, t_pstate pstate)
{
	if (pstate == STATE_TAKEFORK)
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

void	log_state(int ts, int x, t_pstate pstate)
{
	if (pstate == P)
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
*/

