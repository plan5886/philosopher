/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mypark <mypark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 15:04:02 by mypark            #+#    #+#             */
/*   Updated: 2022/04/19 07:51:56 by mypark           ###   ########.fr       */
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

static int	print_one_philo(t_info *info)
{
	printf(MSG_THINKING, gettime_mili(&info->start_tv), 0);
	printf(MSG_DIED, gettime_mili(&info->start_tv), 0);
	return (1);
}

static void	clear_all(t_info *info)
{
	int	i;

	free(info->forks);
	free(info->tid);
	free(info->monitor_tid);
	free(info->philos);
	i = -1;
	while (++i < info->number_of_philos)
		pthread_mutex_destroy(&info->mutexes[i]);
	pthread_mutex_destroy(&info->monitor_mutex);
	pthread_mutex_destroy(&info->print_mutex);
	free(info->mutexes);
}

static void	join_threads(pthread_t *tid, int num)
{
	int	i;

	i = -1;
	while (++i < num)
		pthread_join(tid[i], NULL);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (input_to_info(&info, argc, argv) == 0)
		return (1);
	if (info.number_of_philos == 1 && print_one_philo(&info))
		return (0);
	info.philos = generate_philos(&info);
	if (check_error(info.philos))
		return (1);
	if (generate_monitors(&info) == 0)
		return (1);
	join_threads(info.tid, info.number_of_philos);
	join_threads(info.monitor_tid, info.number_of_philos);
	clear_all(&info);
	return (0);
}
