/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 01:13:41 by marvin            #+#    #+#             */
/*   Updated: 2025/09/26 14:54:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_tv	get_tv(void)
{
	t_tv	tv;

	gettimeofday(&tv, NULL);
	return (tv);
}

void	takefork_and_log(t_pargs *pargs)
{
	t_tv	tv;
	time_t	ms;
	char	*ms_str;
	char	*out;
	char	*tmp;

	pthread_mutex_lock(&(pargs->info->log_mutex));
	tv = get_tv();
	ms = elapsed_us(tv, pargs->info->start_tv);
	ms_str = ft_ltoa(ms / 1000);
	out = ft_strjoin(ms_str, pargs->msg_fork);
	tmp = ft_strjoin(pargs->info->log_buf, out);
	free(pargs->info->log_buf);
	pargs->info->log_buf = tmp;
	tmp = ft_strjoin(pargs->info->log_buf, out);
	free(pargs->info->log_buf);
	pargs->info->log_buf = tmp;
	pthread_mutex_unlock(&(pargs->info->log_mutex));
	//pargs->pstate = PHILO_DIED;
	//pargs->pstatemodified_tv.tv_sec = tv.tv_sec;
	//pargs->pstatemodified_tv.tv_usec = tv.tv_usec;
	free (ms_str);
	free (out);
}

void	statechange_and_log_died(t_pargs *pargs)
{
	t_tv	tv;
	time_t	ms;
	char	*ms_str;
	char	*out;
	char	*tmp;

	pthread_mutex_lock(&(pargs->info->log_mutex));
	tv = get_tv();
	ms = elapsed_us(tv, pargs->info->start_tv);
	ms_str = ft_ltoa(ms / 1000);
	out = ft_strjoin(ms_str, pargs->msg_died);
	tmp = ft_strjoin(pargs->info->log_buf, out);
	free(pargs->info->log_buf);
	pargs->info->log_buf = tmp;
	pthread_mutex_unlock(&(pargs->info->log_mutex));
	pargs->pstate = PHILO_DIED;
	pargs->pstatemodified_tv.tv_sec = tv.tv_sec;
	pargs->pstatemodified_tv.tv_usec = tv.tv_usec;
	free (ms_str);
	free (out);
}

void	statechange_and_log_eat(t_pargs *pargs)
{
	t_tv	tv;
	time_t	ms;
	char	*ms_str;
	char	*out;
	char	*tmp;

	pthread_mutex_lock(&(pargs->info->log_mutex));
	tv = get_tv();
	ms = elapsed_us(tv, pargs->info->start_tv);
	ms_str = ft_ltoa(ms / 1000);
	out = ft_strjoin(ms_str, pargs->msg_eat);
	tmp = ft_strjoin(pargs->info->log_buf, out);
	free(pargs->info->log_buf);
	pargs->info->log_buf = tmp;
	pthread_mutex_unlock(&(pargs->info->log_mutex));
	pargs->pstate = PHILO_EATING;
	pargs->lastmeal_tv.tv_sec = tv.tv_sec;
	pargs->lastmeal_tv.tv_usec = tv.tv_usec;
	pargs->pstatemodified_tv.tv_sec = tv.tv_sec;
	pargs->pstatemodified_tv.tv_usec = tv.tv_usec;
	free (ms_str);
	free (out);
}

void	statechange_and_log_sleep(t_pargs *pargs)
{
	t_tv	tv;
	time_t	ms;
	char	*ms_str;
	char	*out;
	char	*tmp;

	pthread_mutex_lock(&(pargs->info->log_mutex));
	tv = get_tv();
	ms = elapsed_us(tv, pargs->info->start_tv);
	ms_str = ft_ltoa(ms / 1000);
	out = ft_strjoin(ms_str, pargs->msg_sleep);
	tmp = ft_strjoin(pargs->info->log_buf, out);
	free(pargs->info->log_buf);
	pargs->info->log_buf = tmp;
	pthread_mutex_unlock(&(pargs->info->log_mutex));
	pargs->pstate = PHILO_SLEEPING;
	pargs->pstatemodified_tv.tv_sec = tv.tv_sec;
	pargs->pstatemodified_tv.tv_usec = tv.tv_usec;
	free (ms_str);
	free (out);
}

void	statechange_and_log_think(t_pargs *pargs)
{
	t_tv	tv;
	time_t	ms;
	char	*ms_str;
	char	*out;
	char	*tmp;

	pthread_mutex_lock(&(pargs->info->log_mutex));
	tv = get_tv();
	ms = elapsed_us(tv, pargs->info->start_tv);
	ms_str = ft_ltoa(ms / 1000);
	out = ft_strjoin(ms_str, pargs->msg_think);
	tmp = ft_strjoin(pargs->info->log_buf, out);
	free(pargs->info->log_buf);
	pargs->info->log_buf = tmp;
	pthread_mutex_unlock(&(pargs->info->log_mutex));
	pargs->pstate = PHILO_THINKING;
	pargs->pstatemodified_tv.tv_sec = tv.tv_sec;
	pargs->pstatemodified_tv.tv_usec = tv.tv_usec;
	free (ms_str);
	free (out);
}

void	log_output(long ms, int philo_id, char *msg, pthread_mutex_t *mutex)
{
	char	*ms_str;
	char	*id_str;
	int		len;
	char	*out;
	char	*ptr;
	char	*ptr2;

	len = 0;
	ms_str = ft_ltoa(ms / 1000);
	len += ft_strlen(ms_str);
	id_str = ft_itoa(philo_id);
	len += ft_strlen(id_str);
	len += ft_strlen(msg);
	len += 4;
	out = (char *)malloc(sizeof(char) * len);
	ptr = out;
	ptr2 = ms_str;
	while (*ptr2)
		*ptr++ = *ptr2++;
	//ptr -= sizeof(char) * 3;
	*ptr++ = ' ';
	ptr2 = id_str;
	while (*ptr2)
		*ptr++ = *ptr2++;
	*ptr++ = ' ';
	ptr2 = msg;
	while (*ptr2)
		*ptr++ = *ptr2++;
	*ptr++ = '\n';
	*ptr = '\0';
	pthread_mutex_lock(mutex);
	write(1, out, len);
	pthread_mutex_unlock(mutex);
	free (ms_str);
	free (id_str);
	free (out);
	//printf("%ld %d %s\n", ms, philo_id, msg);
}

time_t	tv2time_t(t_tv tv)
{
	time_t	usec;

	if (tv.tv_sec > LONG_MAX - 1000000 || tv.tv_sec < 0)
	{
		write(2, "tv2str: tv.tv_sec > LONG_MAX - 1000000 || tv.tv_sec < 0\n", 56);
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

void	log_output_tv(t_tv curtv, t_tv initv, int philo_id, char *msg)
{
	t_tv	tv;
	//char	*tv_str;

	tv.tv_sec = curtv.tv_sec - initv.tv_sec;
	tv.tv_usec = curtv.tv_usec - initv.tv_usec;
	if (tv.tv_usec < 0)
	{
		tv.tv_sec--;
		tv.tv_usec += 1000000;
	}
	tv2time_t(tv);
	return ;
	(void)philo_id;
	(void)msg;

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

