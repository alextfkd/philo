/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 13:17:27 by marvin            #+#    #+#             */
/*   Updated: 2025/09/26 15:20:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*create_id_msg(int id, char *msg)
{
	char	*strid;
	char	*space_strid;
	char	*space_strid_space;
	char	*s3_msg;
	char	*s3_msgnl;

	strid = ft_itoa(id);
	if (strid == NULL)
		return (NULL);
	space_strid = ft_strjoin(" ", strid);
	if (space_strid == NULL)
		return (free(strid), NULL);
	free(strid);
	space_strid_space = ft_strjoin(space_strid, " ");
	if (space_strid_space == NULL)
		return (free(space_strid), NULL);
	free(space_strid);
	s3_msg = ft_strjoin(space_strid_space, msg);
	if (s3_msg == NULL)
		return (free(space_strid_space), NULL);
	s3_msgnl = ft_strjoin(s3_msg, "\n");
	if (s3_msg == NULL)
		return (free(s3_msg), NULL);
	free(s3_msg);
	return (s3_msgnl);
}

t_pargs	*create_pargs(int id, t_pinfo *info)
{
	t_pargs	*pargs;

	if (info == NULL)
		return (NULL);
	pargs = (t_pargs *)malloc(sizeof(t_pargs));
	if (pargs == NULL)
		return (NULL);
	pargs->id = id;
	pargs->info = info;
	gettimeofday(&(pargs->lastmeal_tv), NULL);
	pargs->pstatemodified_tv.tv_sec = pargs->lastmeal_tv.tv_sec;
	pargs->pstatemodified_tv.tv_usec = pargs->lastmeal_tv.tv_usec;
	pargs->l_fork = NULL;
	pargs->r_fork = NULL;
	pargs->initial_flag = 1;
	pargs->msg_died = create_id_msg(id, LOG_DIED);
	pargs->msg_eat = create_id_msg(id, LOG_EATSTART);
	pargs->msg_sleep = create_id_msg(id, LOG_SLEEPSTART);
	pargs->msg_think = create_id_msg(id, LOG_THINKSTART);
	pargs->msg_fork = create_id_msg(id, LOG_TAKEFORK);
	pargs->pstate = PHILO_WAITING_FOR_START;
	return (pargs);
}


int	is_philo_died(t_pargs **pargs)
{
	if (elapsed_us(get_tv(), (*pargs)->info->start_tv) > (*pargs)->info->uttd)
		return (1);
	return (0);
}

int	check_if_alive(t_pargs **pargs)
{
	if (elapsed_us(get_tv(), (*pargs)->lastmeal_tv) > ((*pargs)->info->uttd))
	{
		statechange_and_log_died(*pargs);
		return (0);
	}
	//log_output(subtract_tv_as_msec(get_tv(), (*pargs)->info->start_tv), (*pargs)->id, LOG_EATSTART);
	return (1);
}

int	died_routine(t_pargs **pargs)
{
	statechange_and_log_died(*pargs);
	return (0);
}
int	eating_routine(t_pargs **pargs)
{
	if (elapsed_us(get_tv(), (*pargs)->pstatemodified_tv) > ((*pargs)->info->utte))
	{
		put_fork_if_possible(&((*pargs)->r_fork), &((*pargs)->l_fork), *pargs);
		statechange_and_log_sleep(*pargs);
		return (0);
	}
	usleep(1); // 失敗した場合、少し待つ
	return (0);
}

int	initial_routine(t_pargs **pargs)
{
	if ((*pargs)->id % 2 == 0)
		usleep(500);
		//usleep(500 * ((*pargs)->id / 2));
	if (get_fork_if_possible(&((*pargs)->r_fork), &((*pargs)->l_fork), *pargs) == 1)
	{
		statechange_and_log_eat(*pargs);
	}
	else
	{
		statechange_and_log_think(*pargs);
	    usleep(10); // 失敗した場合、少し待つ
	}
	return (0);
}

int	thinking_routine(t_pargs **pargs)
{
	if (get_fork_if_possible(&((*pargs)->r_fork), &((*pargs)->l_fork), *pargs) == 1)
	{
		statechange_and_log_eat(*pargs);
	}
	else
	{
	    usleep(10); // 失敗した場合、少し待つ
	}
	(*pargs)->initial_flag = 0;
	return (0);
}

int	sleeping_routine(t_pargs **pargs)
{
	if (elapsed_us(get_tv(), (*pargs)->pstatemodified_tv) > ((*pargs)->info->utts))
	{
		statechange_and_log_think(*pargs);
		thinking_routine(pargs);
	}
	return (0);
}

int	failure_routine(t_pargs **pargs)
{
	(void)pargs;
	return (0);
}

void	loop_routine(t_pargs **pargs)
{
	if ((*pargs)->pstate == PHILO_DIED) 
		died_routine(pargs);
	else if ((*pargs)->pstate == PHILO_INITIAL_STATE) 
		initial_routine(pargs);
	else if ((*pargs)->pstate == PHILO_EATING) 
		eating_routine(pargs);
	else if ((*pargs)->pstate == PHILO_THINKING) 
		thinking_routine(pargs);
	else if ((*pargs)->pstate == PHILO_SLEEPING) 
		sleeping_routine(pargs);
	else if ((*pargs)->pstate == PHILO_FAILURE) 
		failure_routine(pargs);
	else
		failure_routine(pargs);
	if (check_if_alive(pargs) == 0)
		return ;
	//usleep(10);
}

t_all_philo_sign	check_all_sign_from_info(t_pinfo *info)
{
	t_all_philo_sign	res;

	pthread_mutex_lock(&(info->all_philo_sign_mutex));
	res = info->all_philo_sign;
	pthread_mutex_unlock(&(info->all_philo_sign_mutex));
	return (res);
}

t_all_philo_sign	check_all_sign(t_pargs *pargs)
{
	return ((check_all_sign_from_info(pargs->info)));
}

void	modify_all_sign(t_pargs **pargs, t_all_philo_sign sign)
{
	pthread_mutex_lock(&((*pargs)->info->all_philo_sign_mutex));
	(*pargs)->info->all_philo_sign = sign;
	pthread_mutex_unlock(&((*pargs)->info->all_philo_sign_mutex));
	return ;
}

//int	start_routine(t_pargs *pargs)
void	*start_routine(void *args)
{
	t_pargs	*pargs;

	pargs = (t_pargs *)args;
	if (pargs == NULL)
		return (NULL);
	printf("THREAD: id -> [%d]\nright fork ptr -> %p\nleft fork ptr -> %p\n",
		pargs->id, pargs->r_fork, pargs->l_fork);
	printf("start_routine, id -> %d, rfork %d, lfork %d\n", (pargs)->id, (pargs)->r_fork->fid, (pargs)->l_fork->fid);
	pargs->pstate = PHILO_WAITING_FOR_START;
	while (check_all_sign(pargs) == ALL_PHILO_WAIT_FOR_START)
	{
		usleep(5);
	}
	gettimeofday(&(pargs->info->start_tv), NULL);
	pargs->lastmeal_tv.tv_sec = pargs->info->start_tv.tv_sec;
	pargs->lastmeal_tv.tv_usec = pargs->info->start_tv.tv_usec;
	pargs->pstate = PHILO_INITIAL_STATE;
	//msleep(100 * pargs->id);
	while (pargs->pstate != PHILO_DIED && pargs->pstate != PHILO_FAILURE)
	{
		if (check_all_sign(pargs) == ANY_PHILO_DIED)
			break ;
		loop_routine(&pargs);
	}
	modify_all_sign(&pargs, ANY_PHILO_DIED);
	//printf("id %d pargs->info->tv.tv_usec %ld\n", pargs->id, get_us_ts() - pargs->info->tv.tv_usec);
	return (NULL);
}

void	*log_routine(void *args)
{
	t_pinfo	*info;
	
	info = (t_pinfo *)args;
	while (check_all_sign_from_info(info) == ALL_PHILO_WAIT_FOR_START)
	{
		usleep(100);
	}
	while (check_all_sign_from_info(info) == ALL_PHILO_LIVE)
	{
		pthread_mutex_lock(&(info->log_mutex));
		write(1, info->log_buf, ft_strlen(info->log_buf));
		free(info->log_buf);
		info->log_buf = (char *)malloc(sizeof(char) * 1);
		info->log_buf[0] = '\0';
		pthread_mutex_unlock(&(info->log_mutex));
		usleep(100);
	}
	pthread_mutex_lock(&(info->log_mutex));
	write(1, info->log_buf, ft_strlen(info->log_buf));
	free(info->log_buf);
	//info->log_buf = (char *)malloc(sizeof(char) * 1);
	//info->log_buf[0] = '\0';
	pthread_mutex_unlock(&(info->log_mutex));
	return (NULL);
}

//int pthread_mutex_init(pthread_mutex_t *mutex, pthread_mutexattr_t *attr);
void	free_pargs_arr(t_pargs **pargs_arr)
{
	int	i;

	if (pargs_arr == NULL)
		return ;
	i = 0;
	while (pargs_arr[i] != NULL)
	{
		free(pargs_arr[i]);
		i++;
	}
	free(pargs_arr);
}

// 
t_pargs	**create_empty_pargs_arr(int n)
{
	t_pargs		**pargs_arr;

	pargs_arr = (t_pargs **)malloc(sizeof(t_pargs) * n);
	if (pargs_arr == NULL)
		return (NULL);
	memset(pargs_arr, '\0', sizeof(t_pargs) * n);
	return (pargs_arr);
}

t_pargs	**create_pargs_arr(int n, t_pinfo *info, t_fork **fork_arr)
{
	t_pargs		**pargs_arr;
	t_pargs		*pargs;
	int			i;
	int			id;
	
	if (n <= 0 || info == NULL)
		return (NULL);
	pargs_arr = create_empty_pargs_arr(n + 1);
	if (pargs_arr == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		id = i + 1;
		pargs = create_pargs(id, info);
		pargs->r_fork = (fork_arr[i]);
		if (n > 1)
			pargs->l_fork = (fork_arr[(i + n - 1) % n]);
		if (pargs == NULL)
		{
			free_pargs_arr(pargs_arr);
			return (NULL);
		}
		pargs_arr[i++] = pargs;
	}
	return (pargs_arr);
}

pthread_t	*create_pthreads_arr(int n, t_pargs **pargs)
{
	pthread_t	*threads;
	int			i;

	threads = create_empty_threads(n);
	if (threads == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		pthread_create(&(threads[i]), NULL, start_routine, pargs[i]);
		i++;
	}
	return (threads);
}

int	main(int argc, char **argv)
{
	pthread_t	*threads;
	pthread_t	log_thread;
	t_pargs		**pargs_arr;
	t_pinfo		*pinfo;
	int			i;

	pinfo = create_pinfo(argc, argv);
	if (pinfo == NULL)
		return (1);
	print_pinfo(pinfo);

	t_fork **fork_arr;
	fork_arr = create_fork_arr(pinfo->n_philo);
	//printf("started time -> %ld\n", pinfo->tv.tv_sec);
	i = 0;
	while (i < pinfo->n_philo)
	{
		printf("ptr -> %p, fid -> %d\n", fork_arr[i], fork_arr[i]->fid);
		i++;
	}
	pargs_arr = create_pargs_arr(pinfo->n_philo, pinfo, fork_arr);
		
	pthread_create(&(log_thread), NULL, log_routine, pinfo);
	threads = create_pthreads_arr(pinfo->n_philo, pargs_arr);
	usleep(300);
	pthread_mutex_lock(&(pinfo->all_philo_sign_mutex));
	pinfo->all_philo_sign = ALL_PHILO_LIVE;
	pthread_mutex_unlock(&(pinfo->all_philo_sign_mutex));
	i = 0;
	while (i < pinfo->n_philo)
	{
		pthread_join(threads[i++], NULL);
		//pthread_detach(threads[i++]);
	}
	pthread_join(log_thread, NULL);
	free_pargs_arr(pargs_arr);
	free(pinfo);
	free(threads);
	return (0);
}
