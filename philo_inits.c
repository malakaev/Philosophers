/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_inits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgolda <kgolda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 17:59:54 by kgolda            #+#    #+#             */
/*   Updated: 2022/01/28 18:01:50 by kgolda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->number_of_philosopher)
	{
		if (pthread_mutex_init(main->philo[i].fork_r, NULL) != 0)
			return (prn_error(ERR_MUTEX));
		if (i > 0)
			main->philo[i].fork_l = main->philo[i - 1].fork_r;
		i++;
	}
	main->philo[0].fork_l = main->philo[i - 1].fork_r;
	return (0);
}

int	init_mutex(t_main *main)
{
	int	i;

	if (pthread_mutex_init(&main->printer, NULL) != OK)
		return (ERR);
	i = 0;
	while (i < main->number_of_philosopher)
	{
		if (pthread_mutex_init(&main->fork[i], NULL) != OK)
			return (ERR);
		i++;
	}
	i = 0;
	while (i < main->number_of_philosopher)
	{
		main->philo[i].fork_l = main->fork + i;
		if (i > 0)
			main->philo[i].fork_r = main->fork + (i - 1);
		i++;
	}
	main->philo[0].fork_r = main->fork + (main->number_of_philosopher - 1);
	return (OK);
}

int	init_data(t_main *main)
{
	int	i;

	i = 0;
	main->died = NO;
	if (init_mutex(main) != OK)
		return (prn_error(ERR_MUTEX));
	while (i < main->number_of_philosopher)
	{
		main->philo[i].id = i + 1;
		main->philo[i].eat_count = 0;
		main->philo[i].printer = main->printer;
		main->philo[i].main = main;
		i++;
	}
	return (0);
}
