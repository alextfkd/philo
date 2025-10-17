/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 13:17:27 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/10/17 22:29:50 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	_start_philo_simulation(int uwait, t_pinfo *pinfo);
static void	_all_pthread_join(
				t_pinfo *pinfo,
				pthread_t *threads,
				pthread_t log_thread
				);
static int	free_and_exit(
				t_pargs **pargs_arr,
				t_fork **fork_arr,
				pthread_t *p_threads,
				t_pinfo *pinfo
				);

int	main(int argc, char **argv)
{
	pthread_t	*p_threads;
	pthread_t	log_thread;
	t_pargs		**pargs_arr;
	t_pinfo		*pinfo;
	t_fork		**fork_arr;

	pinfo = create_pinfo(argc, argv);
	if (pinfo == NULL)
		return (error_msg_on_validation(), 1);
	fork_arr = create_fork_arr(pinfo->n_philo);
	if (fork_arr == NULL)
		return (free_pinfo(pinfo), 1);
	pargs_arr = create_pargs_arr(pinfo->n_philo, pinfo, fork_arr);
	pthread_create(&(log_thread), NULL, _log_routine, pinfo);
	p_threads = create_pthreads_arr(pinfo->n_philo, pargs_arr);
	_start_philo_simulation(300, pinfo);
	_all_pthread_join(pinfo, p_threads, log_thread);
	return (free_and_exit(pargs_arr, fork_arr, p_threads, pinfo));
}

static int	free_and_exit(
	t_pargs **pargs_arr,
	t_fork **fork_arr,
	pthread_t *p_threads,
	t_pinfo *pinfo
)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	while (i < pinfo->n_philo + 1)
		res += pinfo->exit_status[i++];
	free_pargs_arr(pargs_arr);
	free_fork_arr(fork_arr);
	free_pinfo(pinfo);
	free(p_threads);
	if (res > 0)
		return (1);
	return (0);
}

static void	_start_philo_simulation(int uwait, t_pinfo *pinfo)
{
	usleep(uwait);
	pthread_mutex_lock(pinfo->data_mutex);
	pinfo->common_state = ALL_PHILO_LIVE;
	pinfo->start_tv = get_tv();
	pthread_mutex_unlock(pinfo->data_mutex);
}

static void	_all_pthread_join(
	t_pinfo *pinfo,
	pthread_t *threads,
	pthread_t log_thread
)
{
	int	i;

	i = 0;
	while (i < pinfo->n_philo)
	{
		pthread_join(threads[i], (void *)(&pinfo->exit_status[i]));
		i++;
	}
	pthread_join(log_thread, (void *)(&pinfo->exit_status[i]));
}
