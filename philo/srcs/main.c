/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mypark <mypark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 15:04:02 by mypark            #+#    #+#             */
/*   Updated: 2022/04/29 21:02:15 by mypark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include "philo.h"
#include "constant.h"
#include "utils.h"

static int	print_one_philo(t_global_info *info)
{
	printf(MSG_THINKING, gettime_mili(&info->start_tv), 1);
	printf(MSG_DIED, gettime_mili(&info->start_tv) + info->time_to_die, 1);
	return (1);
}

static void	join_threads(pthread_t *tids, int num)
{
	int	i;

	i = -1;
	while (++i < num)
		pthread_join(tids[i], NULL);
}

static int	create_threads(pthread_t *tids, \
				t_global_info *info, t_philo *philos)
{
	int	i;
	
	pthread_mutex_lock(&info->mutexes->start_signal);
	i = 0;
	while (i < info->number_of_philos)
	{
		if (pthread_create(&tids[i], NULL, daily_routine, &philos[i]))
			return (0);
		i += 2;
	}
	i = 1;
	while (i < info->number_of_philos)
	{
		if (pthread_create(&tids[i], NULL, daily_routine, &philos[i]))
			return (0);
		i += 2;
	}
	if (pthread_create(&tids[info->number_of_philos], NULL, monitor, info))
		return (0);
	gettimeofday(&info->start_tv, NULL);
	i = -1;
	while (++i < info->number_of_philos)
		gettimeofday(&philos[i].eaten_time, NULL);
	pthread_mutex_unlock(&info->mutexes->start_signal);
	return (1);
}

static void	destroy_mutexes(t_global_info *info)
{
	t_mutexes	*mutexes;
	int			i;

	mutexes = info->mutexes;
	pthread_mutex_destroy(&mutexes->terminal_print);
	pthread_mutex_destroy(&mutexes->grave);
	pthread_mutex_destroy(&mutexes->start_signal);
	i = 0;
	while (i < info->number_of_philos)
	{
		pthread_mutex_destroy(&mutexes->philos[i]);
		pthread_mutex_destroy(&mutexes->forks[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_global_info	info;
	t_philo			*philos;
	pthread_t		*tids;

	info.forks = NULL;
	info.mutexes = NULL;
	if (input_to_info(&info, argc, argv) == 0)
		return (1);
	if (info.number_of_philos == 1 && print_one_philo(&info))
		return (0);
	if (allocate_resources(&info, &philos, &tids) == 0)
	{
		printf("MALLOC ERROR\n");
		return (1);
	}
	if (create_threads(tids, &info, philos) == 0)
	{
		printf("THREAD CREATION ERROR\n");
		return (1);
	}
	join_threads(tids, info.number_of_philos + 1);
	destroy_mutexes(&info);
	clear_all(&info, philos, tids);
	return (0);
}
