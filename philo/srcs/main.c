/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 13:17:27 by marvin            #+#    #+#             */
/*   Updated: 2025/09/25 09:56:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_pargs	*create_pargs(int id, t_pinfo *info)
{
	t_pargs	*pargs;

	if (info == NULL)
		return (NULL);
	pargs = (t_pargs *)malloc(sizeof(t_pargs));
	if (pargs == NULL)
		return (NULL);
	pargs->id = id;
	pargs->initial_flag = 1;
	pargs->info = info;
	gettimeofday(&(pargs->lastmeal_tv), NULL);
	pargs->l_fork = NULL;
	pargs->r_fork = NULL;
	pargs->pstate = PHILO_READY;
	pargs->any_philo_died = NULL;
	return (pargs);
}

t_tv	get_tv(void)
{
	t_tv	tv;

	gettimeofday(&tv, NULL);
	return (tv);
}

// returns tv1 - tv2 in usec;
time_t	subtract_tv_as_usec(t_tv tv1, t_tv tv2)
{
	t_tv	tv_res;
	time_t	res;

	if (tv1.tv_sec >= tv2.tv_sec && tv1.tv_usec >= tv2.tv_usec)
	{
		tv_res.tv_sec = tv1.tv_sec - tv2.tv_sec;
		tv_res.tv_usec = tv1.tv_usec - tv2.tv_usec;
	}
	else if (tv1.tv_sec >= tv2.tv_sec && tv1.tv_usec < tv2.tv_usec)
	{
		tv_res.tv_sec = tv1.tv_sec - tv2.tv_sec - 1;
		tv_res.tv_usec = tv1.tv_usec - tv2.tv_usec + 1000000;
	}
	else
		return (long)(-1);
	res = (tv_res.tv_sec % 1000) * 1000000 + tv_res.tv_usec;
	return (res);
}

time_t	subtract_tv_as_msec(t_tv tv1, t_tv tv2)
{
	t_tv	tv_res;
	time_t	res;

	if (tv1.tv_sec >= tv2.tv_sec && tv1.tv_usec >= tv2.tv_usec)
	{
		tv_res.tv_sec = tv1.tv_sec - tv2.tv_sec;
		tv_res.tv_usec = tv1.tv_usec - tv2.tv_usec;
	}
	else if (tv1.tv_sec >= tv2.tv_sec && tv1.tv_usec < tv2.tv_usec)
	{
		tv_res.tv_sec = tv1.tv_sec - tv2.tv_sec - 1;
		tv_res.tv_usec = tv1.tv_usec - tv2.tv_usec + 1000000;
	}
	else
		return (long)(-1);
	res = (tv_res.tv_sec % 1000) * 1000 + tv_res.tv_usec / 1000;
	return (res);
}

int	check_if_alive(t_pargs **pargs)
{
	//(void)pargs;
	log_output_tv(get_tv(), (*pargs)->info->start_tv, (*pargs)->id, LOG_DIED);
	if (subtract_tv_as_msec(get_tv(), (*pargs)->lastmeal_tv) > ((*pargs)->info->ttd))
	{
		log_output(subtract_tv_as_msec(get_tv(), (*pargs)->info->start_tv), (*pargs)->id, LOG_DIED);
		//write(1, "died\n", 5);
		(*pargs)->pstate = PHILO_DIED;
		return (0);
	}
	usleep(1000);
	//log_output(subtract_tv_as_msec(get_tv(), (*pargs)->info->start_tv), (*pargs)->id, LOG_EATSTART);
	return (0);
}

int	died_routine(t_pargs **pargs)
{
	write(1, "died\n", 5);
	log_output(subtract_tv_as_msec(get_tv(), (*pargs)->lastmeal_tv) > ((*pargs)->info->ttd), (*pargs)->id, LOG_DIED);
	//usleep(1000);
	return (0);
}
int	eating_routine(t_pargs **pargs)
{
	if (subtract_tv_as_msec(get_tv(), (*pargs)->lastpstatechange_tv) > ((*pargs)->info->tte))
	{
		put_fork_if_possible(&((*pargs)->r_fork), &((*pargs)->l_fork), *pargs);
		log_output(subtract_tv_as_msec(get_tv(), (*pargs)->info->start_tv), (*pargs)->id, LOG_SLEEPSTART);
		(*pargs)->pstate = PHILO_SLEEPING;
		gettimeofday(&((*pargs)->lastpstatechange_tv), NULL);
	}
	return (0);
}
int	thinking_routine(t_pargs **pargs)
{
	//printf("thinking, id -> %d, rfork %d, lfork %d\n", (*pargs)->id, (*pargs)->r_fork->fid, (*pargs)->l_fork->fid);
	if (get_fork_if_possible(&((*pargs)->r_fork), &((*pargs)->l_fork), *pargs) == 1)
	{
		log_output(subtract_tv_as_msec(get_tv(), (*pargs)->info->start_tv), (*pargs)->id, LOG_TAKEFORK);
		log_output(subtract_tv_as_msec(get_tv(), (*pargs)->info->start_tv), (*pargs)->id, LOG_EATSTART);
		(*pargs)->pstate = PHILO_EATING;
		gettimeofday(&((*pargs)->lastmeal_tv), NULL);
		(*pargs)->lastpstatechange_tv.tv_sec = (*pargs)->lastmeal_tv.tv_sec;
		(*pargs)->lastpstatechange_tv.tv_usec = (*pargs)->lastmeal_tv.tv_usec;
	}
	else
	{
		if ((*pargs)->initial_flag == 1)
			log_output(subtract_tv_as_msec(get_tv(), (*pargs)->info->start_tv), (*pargs)->id, LOG_THINKSTART);
	    usleep(100); // 失敗した場合、少し待つ
	}
	(*pargs)->initial_flag = 0;
	return (0);
}
int	sleeping_routine(t_pargs **pargs)
{
	if (subtract_tv_as_msec(get_tv(), (*pargs)->lastpstatechange_tv) > ((*pargs)->info->tts))
	{
		log_output(subtract_tv_as_msec(get_tv(), (*pargs)->info->start_tv), (*pargs)->id, LOG_THINKSTART);
		(*pargs)->pstate = PHILO_THINKING;
		gettimeofday(&((*pargs)->lastpstatechange_tv), NULL);
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
	check_if_alive(pargs);
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
	pargs->pstate = PHILO_READY;
	while (pargs->info->start_sign == 0)
	{
		usleep(10);
		//loop_routine(&pargs);
	}
	gettimeofday(&(pargs->info->start_tv), NULL);
	//tv2str(pargs->info->start_tv);
	pargs->lastmeal_tv.tv_sec = pargs->info->start_tv.tv_sec;
	pargs->lastmeal_tv.tv_usec = pargs->info->start_tv.tv_usec;
	*(pargs->any_philo_died) = 0;
	pargs->pstate = PHILO_THINKING;
	//msleep(100 * pargs->id);
	while (pargs->pstate != PHILO_DIED && pargs->pstate != PHILO_FAILURE && *(pargs->any_philo_died) == 0)
	{
		loop_routine(&pargs);
	}
	*(pargs->any_philo_died) = 1;
	//printf("id %d pargs->info->tv.tv_usec %ld\n", pargs->id, get_us_ts() - pargs->info->tv.tv_usec);
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
	int			philo_died_flag;
	
	if (n <= 0 || info == NULL)
		return (NULL);
	pargs_arr = create_empty_pargs_arr(n + 1);
	philo_died_flag = 0;
	if (pargs_arr == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		id = i + 1;
		pargs = create_pargs(id, info);
		pargs->any_philo_died = &philo_died_flag;
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
	t_pargs		**pargs_arr;
	t_pinfo		*pinfo;
	int			i;

	pinfo = create_pinfo(argc, argv);
	if (pinfo == NULL)
		return (1);
	pinfo->start_sign = 0;
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
	threads = create_pthreads_arr(pinfo->n_philo, pargs_arr);
	pinfo->start_sign = 1;
	i = 0;
	while (i < pinfo->n_philo)
	{
		pthread_join(threads[i++], NULL);
		//pthread_detach(threads[i++]);
	}
	free_pargs_arr(pargs_arr);
	free(pinfo);
	free(threads);
	return (0);
}
