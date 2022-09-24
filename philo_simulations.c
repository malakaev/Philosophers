/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_simulations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgolda <kgolda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 17:56:47 by kgolda            #+#    #+#             */
/*   Updated: 2022/01/30 20:30:40 by kgolda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat_manager(t_philo *philo)
{
	struct timeval	cur_time;

	gettimeofday(&cur_time, NULL);
	if (philo->main->died == YES)
		return (-1);
	if (philo->id % 2 != 0)
	{
		if (philo->main->number_of_philosopher % 2 != 0
			&& philo->id == philo->main->number_of_philosopher)
			usleep(700);
		pthread_mutex_lock(philo->fork_l);
		print_philo_status(cur_time, philo, "has taken a fork");
		pthread_mutex_lock(philo->fork_r);
		print_philo_status(cur_time, philo, "has taken a fork");
	}
	else
	{
		usleep(500);
		pthread_mutex_lock(philo->fork_r);
		print_philo_status(cur_time, philo, "has taken a fork");
		pthread_mutex_lock(philo->fork_l);
		print_philo_status(cur_time, philo, "has taken a fork");
	}
	return (0);
}

void	*philos_simultn(void *phil_id)
{
	struct timeval	time_start;
	struct timeval	time_curent;
	t_philo			*philo;
	int				i;

	i = 0;
	philo = (t_philo *)phil_id;
	gettimeofday(&time_start, NULL);
	philo->main->start = (time_start.tv_sec * 1000000 + time_start.tv_usec);
	time_curent = time_start;
	while (philo->main->died == NO)
	{
		if (eat_manager(philo) != 0)
			return (0);
		print_philo_status(time_curent, philo, EATING);
		changed_usleep(philo->main->time_to_eat);
		unlock_mutex_fork(philo);
		print_philo_status(time_curent, philo, SLEEPING);
		changed_usleep(philo->main->time_to_sleep);
		print_philo_status(time_curent, philo, THINKING);
		usleep(10);
		i++;
	}
	return (0);
}

int	philo_thread_make(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->number_of_philosopher && main->died == NO)
	{
		if ((pthread_create(main->thread + i, NULL, philos_simultn, \
		main->philo + i)) != OK)
			return (prn_error(ERR_THREAD_CREAT));
		i++;
	}
	if ((pthread_create(&main->watcher, NULL, watcher_thread, main)) != OK)
		return (prn_error(ERR_THREAD_CREAT));
	return (0);
}
