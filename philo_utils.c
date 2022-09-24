/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgolda <kgolda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 18:02:18 by kgolda            #+#    #+#             */
/*   Updated: 2022/01/30 20:31:24 by kgolda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philo_status(struct timeval time_cur, t_philo *philo, char *str)
{
	long long int	time;

	if (pthread_mutex_lock(&philo->printer) != OK)
		(prn_error(ERR_MUTEX));
	if (philo->main->died == NO)
	{
		gettimeofday(&time_cur, NULL);
		if (str == EATING)
			philo->last_time_eat = (time_cur.tv_sec * 1000000 \
			+ time_cur.tv_usec) / 1000;
		time = ((time_cur.tv_sec * 1000000 + time_cur.tv_usec) \
		- philo->main->start) / 1000;
		printf("%lld %d %s\n", time, philo->id, str);
	}
	if (pthread_mutex_unlock(&philo->printer) != OK)
		(prn_error(ERR_MUTEX));
}

void	unlock_mutex_fork(t_philo *philo)
{
	if (pthread_mutex_unlock(philo->fork_l) != 0
		|| pthread_mutex_unlock(philo->fork_r) != OK)
		(prn_error(ERR_MUTEX));
	philo->eat_count++;
}

int	changed_usleep(long int time)
{
	struct timeval	t1;
	struct timeval	t2;

	gettimeofday(&t1, NULL);
	gettimeofday(&t2, NULL);
	usleep(time * 900);
	while (((t2.tv_sec * 1000000 + t2.tv_usec) - \
			(t1.tv_sec * 1000000 + t1.tv_usec)) < time * 1000)
	{
		usleep(100);
		gettimeofday(&t2, NULL);
	}
	return (0);
}
