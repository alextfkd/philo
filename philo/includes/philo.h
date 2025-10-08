/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 00:30:49 by marvin            #+#    #+#             */
/*   Updated: 2025/10/08 04:11:24 by marvin           ###   ########.fr       */
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

typedef struct timeval	t_tv;

typedef enum e_all_philo_alart
{
	ALL_PHILO_WAIT_FOR_START,
	ALL_PHILO_LIVE,
	ANY_PHILO_DIED,
	ANY_PHILO_FAILED,
	ALART_FAILURE,
}	t_all_philo_alart;

typedef struct s_pinfo
{
	int						n_philo;
	int						ttd;
	int						tte;
	int						tts;
	int						uttd;
	int						utte;
	int						utts;
	int						must_eat;
	int						pfull;
	enum e_all_philo_alart	all_philo_alart;
	pthread_mutex_t			*philo_alart_mutex;
	pthread_mutex_t			*log_mutex;
	pthread_mutex_t			*data_mutex;
	char					*log_buf;
	struct timeval			start_tv;
}	t_pinfo;

typedef enum e_fstate
{
	FORK_AVALIABLE,
	FORK_OCCUPIED,
	FORK_FAILURE,
}	t_fstate;

typedef enum e_pstate
{
	PHILO_WAITING_FOR_START,
	PHILO_INITIAL_STATE,
	PHILO_EATING,
	PHILO_THINKING,
	PHILO_SLEEPING,
	PHILO_DIED,
	PHILO_FAILURE,
}	t_pstate;

typedef struct s_fork
{
	enum e_fstate	fstate;
	int				*owner;
	int				fid;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_pargs
{
	int				id;
	int				n_eat;
	char			*msg_sleep;
	char			*msg_eat;
	char			*msg_think;
	char			*msg_fork;
	char			*msg_died;
	struct timeval	lastmeal_tv;
	struct timeval	pstatemodified_tv;
	enum e_pstate	pstate;
	struct s_fork	*r_fork;
	struct s_fork	*l_fork;
	struct s_pinfo	*info;
}	t_pargs;

size_t				ft_strlen(const char *s);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_ltoa(long ln);
char				*ft_itoa(int n);

t_tv				get_tv(void);
int					ft_isspace(char c);
int					ft_isdigit(char c);
int					ft_is_alphasign(const char *str);
void				log_state(int ts, int x, int state);

t_pinfo				*create_pinfo(int argc, char **argv);

int					ft_atoi(const char *nptr);

int					validate_args(int argc, char **argv);

pthread_t			*create_pthreads_arr(int n, t_pargs **pargs);
void				free_fork_arr(t_fork **fork_arr);
t_fork				*create_fork(int fid);
t_fork				**create_fork_arr(int n);
void				print_pinfo(t_pinfo *pinfo);
int					get_fork_if_possible(
						t_fork **rfork,
						t_fork **lfork,
						t_pargs *pargs
						);
int					put_fork_if_possible(
						t_fork **rfork,
						t_fork **lfork,
						t_pargs *pargs
						);

char				*tv2str(t_tv tv);

time_t				tv2time_t(t_tv tv);
time_t				elapsed_us(t_tv current_tv, t_tv initial_tv);

void				takefork_and_log(t_pargs *pargs);
void				statechange_and_log_died(t_pargs *pargs);
void				statechange_and_log_eat(t_pargs *pargs);
void				statechange_and_log_sleep(t_pargs *pargs);
void				statechange_and_log_think(t_pargs *pargs);
int					lock_fork_mutex(t_fork *rfork, t_fork *lfork);
void				unlock_fork_mutex(t_fork *rfork, t_fork *lfork);
int					died_routine(t_pargs **pargs);
int					eating_routine(t_pargs **pargs);
int					initial_routine(t_pargs **pargs);
int					thinking_routine(t_pargs **pargs);
int					sleeping_routine(t_pargs **pargs);
void				*start_routine(void *args);
void				loop_routine(t_pargs **pargs);
char				*create_id_msg(int id, char *msg);
void				free_pargs_arr(t_pargs **pargs_arr);
t_all_philo_alart	check_alart(t_pinfo *info);
t_all_philo_alart	check_all_sign(t_pargs *pargs);
void				modify_philo_alart(
						t_pargs **pargs,
						t_all_philo_alart alart
						);
void				modify_philo_alart2(t_pinfo *info, t_all_philo_alart alart);
t_pargs				**create_pargs_arr(int n, t_pinfo *info, t_fork **fork_arr);
void				free_str_set_null(char **str);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(
						const char *big,
						const char *little,
						size_t len
						);
void				free_pinfo(t_pinfo *pinfo);
void				error_msg_on_validation(void);
#endif