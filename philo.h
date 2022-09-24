/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgolda <kgolda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 18:21:22 by kgolda            #+#    #+#             */
/*   Updated: 2022/01/28 19:09:34 by kgolda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

# define ERR_ARG_NUM "Wrong number of arguments. Needs 4 or 5 argumens."
# define ERR_ARG "Wrong argument."
# define ERR_MUTEX "Mutex error."
# define ERR_THREAD_CREAT "Thread creat error."
# define ERR_THREAD "Thread error."
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"

typedef struct s_philosoph
{
	int				id;
	int				eat_count;
	long long int	last_time_eat;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	printer;
	struct timeval	time;
	struct s_main	*main;
}	t_philo;

typedef struct s_main
{
	t_philo			philo[201];
	pthread_t		thread[201];
	pthread_mutex_t	fork[201];
	pthread_t		watcher;
	pthread_mutex_t	printer;
	int				number_of_philosopher;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	long long int	start;
	int				died;
}	t_main;

enum
{
	ERR = -1,
	OK,
	NO,
	YES,
	DIED
};

int		parser_arg(int argc, char **argv, t_main *main);
int		atoi_for_philo(const char *s);
int		prn_error(const char *err);
int		init_forks(t_main *main);
int		init_mutex(t_main *main);
int		init_data(t_main *main);
int		check_eat_count(t_main *main);
int		check_eat_time(struct timeval cur_time, t_main *main, int i);
void	*watcher_thread(void *param);
int		eat_manager(t_philo *philo);
void	*philos_simultn(void *phil_id);
int		philo_thread_make(t_main *main);
void	print_philo_status(struct timeval time_cur, t_philo *philo, char *str);
void	unlock_mutex_fork(t_philo *philo);
int		changed_usleep(long int time);
int		unlock_mutex_forks(t_main *main);
int		destroy_threads_and_mutex(t_main *main);

#endif
