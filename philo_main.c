/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgolda <kgolda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 18:03:43 by kgolda            #+#    #+#             */
/*   Updated: 2022/01/28 19:00:04 by kgolda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	prn_error(const char *err)
{
	int	i;

	i = 0;
	while (err[i] != '\0')
		i++;
	write(1, "Error\n", 6);
	write(1, err, i);
	write(1, "\n", 1);
	return (ERR);
}

int	atoi_for_philo(const char *s)
{
	int				i;
	int				count;
	unsigned int	res;

	i = 0;
	while (s[i] && (s[i] == 32 || (s[i] > 8 && s[i] < 14)))
		i++;
	res = 0;
	count = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = (s[i++] - '0') + res * 10;
		count++;
	}
	if (s[i] != '\0' || count < 1 || res > 2147483647)
		return (ERR);
	return (res);
}

int	parser_arg(int argc, char **argv, t_main *main)
{
	if (argc < 5 || argc > 6)
		return (prn_error(ERR_ARG_NUM));
	main->number_of_philosopher = atoi_for_philo(argv[1]);
	main->time_to_die = atoi_for_philo(argv[2]);
	main->time_to_eat = atoi_for_philo(argv[3]);
	main->time_to_sleep = atoi_for_philo(argv[4]);
	main->times_must_eat = 0;
	if (main->number_of_philosopher <= 0 || main->time_to_die <= 0 || \
	main->time_to_eat <= 0 || main->time_to_sleep < 0)
		return (prn_error(ERR_ARG));
	if (argc == 6)
	{
		main->times_must_eat = atoi_for_philo(argv[5]);
		if (main->times_must_eat <= 0)
			return (prn_error(ERR_ARG));
	}
	return (OK);
}

int	main(int argc, char **argv)
{
	t_main	main;

	if (parser_arg(argc, argv, &main) != OK)
		return (ERR);
	if (init_data(&main) != OK)
		return (ERR);
	if ((philo_thread_make(&main)) != OK)
		return (ERR);
	if (destroy_threads_and_mutex(&main) != OK)
		return (ERR);
	return (0);
}
