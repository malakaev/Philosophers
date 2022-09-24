/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_thread_mutex.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgolda <kgolda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 17:55:53 by kgolda            #+#    #+#             */
/*   Updated: 2022/01/28 18:20:04 by kgolda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	unlock_mutex_forks(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->number_of_philosopher)
	{
		if (pthread_mutex_unlock(main->fork + i) != OK)
			return (prn_error(ERR_MUTEX));
		i++;
	}
	if (pthread_mutex_unlock(&main->printer) != OK)
		return (prn_error(ERR_MUTEX));
	return (OK);
}

int	destroy_threads_and_mutex(t_main *main)
{
	int	i;

	i = 0;
	if (pthread_join(main->watcher, NULL) != OK)
		return (prn_error(ERR_THREAD));
	if (unlock_mutex_forks(main) != OK)
		return (0);
	while (i < main->number_of_philosopher)
	{
		if (pthread_join(main->thread[i], NULL) != OK)
			return (prn_error(ERR_THREAD));
		i++;
	}
	i = 0;
	while (i < main->number_of_philosopher)
	{
		if (pthread_mutex_destroy(main->fork + i) != OK)
			return (prn_error(ERR_MUTEX));
		i++;
	}
	if (pthread_mutex_destroy(&main->printer) != OK)
		return (prn_error(ERR_MUTEX));
	return (OK);
}
