/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_watcher.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgolda <kgolda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 17:59:54 by kgolda            #+#    #+#             */
/*   Updated: 2022/01/30 20:31:17 by kgolda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_eat_count(t_main *main)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < main->number_of_philosopher)
	{
		if (main->philo[i].eat_count >= main->times_must_eat)
			j++;
		i++;
	}
	if (j == main->number_of_philosopher)
	{
		pthread_mutex_lock(&main->printer);
		main->died = YES;
		return (1);
	}
	return (0);
}

int	check_eat_time(struct timeval cur_time, t_main *main, int i)
{
	long long int	t;

	t = ((cur_time.tv_sec * 1000000 + cur_time.tv_usec) / \
	1000 - main->philo[i].last_time_eat);
	if (t >= main->time_to_die)
	{
		pthread_mutex_lock(&main->printer);
		printf("%lld %d died\n", (((cur_time.tv_sec * 1000000 + \
		cur_time.tv_usec) - main->start) / 1000) + 1, i + 1);
		main->died = YES;
		return (DIED);
	}
	if (main->times_must_eat > 0)
	{
		if (check_eat_count(main) == 1)
			return (1);
	}
	return (0);
}

void	*watcher_thread(void *param)
{
	t_main			*main;
	struct timeval	cur_time;
	int				i;

	main = (t_main *)param;
	gettimeofday(&cur_time, NULL);
	i = -1;
	while (++i < main->number_of_philosopher)
		main->philo[i].last_time_eat = \
		(cur_time.tv_sec * 1000000 + cur_time.tv_usec) / 1000;
	while (main->died == NO)
	{
		gettimeofday(&cur_time, NULL);
		i = 0;
		while (i < main->number_of_philosopher && main->died == NO)
		{
			if (check_eat_time(cur_time, main, i) != 0)
				return (0);
			i++;
		}
		usleep(10);
	}
	return (0);
}
