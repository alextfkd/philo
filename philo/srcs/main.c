/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 13:17:27 by marvin            #+#    #+#             */
/*   Updated: 2025/09/23 12:37:53 by marvin           ###   ########.fr       */
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
	pargs->info = info;
	pargs->l_fork = NULL;
	pargs->r_fork = NULL;
	pargs->pstate = PHILO_READY;
	return (pargs);
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
		pargs->r_fork = &((*fork_arr)[i]);
		if (n > 1)
			pargs->l_fork = &((*fork_arr)[(i + n - 1) % n]);
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
	t_tv		tv;

	pinfo = create_pinfo(argc, argv);
	if (pinfo == NULL)
		return (1);
	print_pinfo(pinfo);

	t_fork **fork_arr;
	fork_arr = create_fork_arr(pinfo->n_philo);
	gettimeofday(&tv, NULL);
	printf("time -> %ld\n", tv.tv_sec);
	i = 0;
	while (i < pinfo->n_philo)
		printf("ptr -> %p\n", fork_arr[i++]);
	pargs_arr = create_pargs_arr(pinfo->n_philo, pinfo, fork_arr);
	threads = create_pthreads_arr(pinfo->n_philo, pargs_arr);
	i = 0;
	while (i < pinfo->n_philo)
	{
		pthread_join(threads[i], NULL);
		pthread_detach(threads[i++]);
	}
	free_pargs_arr(pargs_arr);
	free(pinfo);
	free(threads);
	return (0);
}
