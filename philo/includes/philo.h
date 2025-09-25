/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 00:30:49 by marvin            #+#    #+#             */
/*   Updated: 2025/09/25 09:54:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <sys/time.h>
# define STATE_TAKEFORK 0
# define STATE_EAT 1
# define STATE_SLEEP 2
# define STATE_THINK 3
# define STATE_DIED 4

# define LOG_TAKEFORK "has taken a fork"
# define LOG_EATSTART "is eating"
# define LOG_SLEEPSTART "is sleeping"
# define LOG_THINKSTART "is thinking"
# define LOG_DIED "died"

typedef struct timeval t_tv;

/*
- number_of_philosophers:
	The number of philosophers and also the number of forks.
- time_to_die (in milliseconds):
	If a philosopher has not started eating within time_to_die
	milliseconds since the start of their last meal or the start of the
	simulation, they die.
- time_to_eat (in milliseconds):
	The time it takes for a philosopher to eat.
	During that time, they will need to hold two forks.
- time_to_sleep (in milliseconds):
	The time a philosopher will spend sleeping.
- number_of_times_each_philosopher_must_eat (optional argument):
	If all philosophers have eaten at least 
	number_of_times_each_philosopher_must_eat times, the simulation stops.
	If not specified, the simulation stops when a philosopher dies.
*/

typedef struct s_pinfo
{
	int				n_philo;
	int				ttd;
	int				tte;
	int 			tts;
	int				must_eat;
	int				start_sign;
	struct timeval	start_tv;
}	t_pinfo;

typedef enum	e_fstate{
	FORK_AVALIABLE,
	FORK_OCCUPIED,
	FORK_FAILURE,
}	t_fstate;

typedef enum	e_pstate{
	PHILO_READY,
	PHILO_EATING,
	PHILO_THINKING,
	PHILO_SLEEPING,
	PHILO_DIED,
	PHILO_FAILURE,
}	t_pstate;

typedef struct	s_fork{
	enum e_fstate	fstate;
	int				*owner;
	int				fid;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_pargs
{
	int				id;
	int				initial_flag;
	int				*any_philo_died;
	struct timeval	lastmeal_tv;
	struct timeval	lastpstatechange_tv;
	enum e_pstate	pstate;
	struct s_fork	*r_fork;
	struct s_fork	*l_fork;
	struct s_pinfo	*info;
}	t_pargs;

size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_ltoa(long ln);

int	ft_isspace(char c);
int	ft_isdigit(char c);
int	ft_is_alphasign(const char *str);
//void	log_output(int ts, int x, char *msg);
void	log_output(long ms, int philo_id, char *msg);
void	log_state(int ts, int x, int state);

t_pinfo	*create_pinfo(int argc, char **argv);

int	ft_atoi(const char *nptr);

int	validate_args(int argc, char **argv);

pthread_t	*create_empty_threads(int n);
void	free_fork_arr(t_fork **fork_arr);
t_fork	*create_fork(int fid);
t_fork	**create_fork_arr(int n);
void	print_pinfo(t_pinfo *pinfo);
int get_fork_if_possible(t_fork **rfork, t_fork **lfork, t_pargs *pargs);
int put_fork_if_possible(t_fork **rfork, t_fork **lfork, t_pargs *pargs);

char	*tv2str(t_tv tv);
void	log_output_tv(t_tv curtv, t_tv initv, int philo_id, char *msg);
#endif