/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_monitors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mypark <mypark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 04:24:01 by mypark            #+#    #+#             */
/*   Updated: 2022/04/28 17:11:35 by mypark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "constant.h"
#include "utils.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	is_died(t_philo *philo)
{
	int		curr_time;
	t_info	*info;

	info = philo->info;
	curr_time = gettime_mili(&info->start_tv);
	if (curr_time - philo->eaten_time > info->time_to_die)
		return (1);
	return (0);
}

static void	set_grave(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&info->monitor_mutex);
	if (info->grave == 0)
	{
		pthread_mutex_lock(&info->print_mutex);
		printf(MSG_DIED, gettime_mili(&info->start_tv), philo->id + 1);
		pthread_mutex_unlock(&info->print_mutex);
	}
	info->grave = 1;
	pthread_mutex_unlock(&info->monitor_mutex);
}

static void	*monitor(void *arg)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)arg;
	info = philo->info;
	ft_spinlock(&info->start);
	while (1)
	{
		if (info->grave || philo->eat_count == info->number_of_time_must_eat)
			break ;
		if (is_died(philo))
		{
			set_grave(info, philo);
			break ;
		}
		usleep(1000);
	}
	return (FT_NULL);
}

int	generate_monitors(t_info *info)
{
	int	i;

	pthread_mutex_init(&info->monitor_mutex, NULL);
	info->monitor_tid = malloc(sizeof(pthread_t) * info->number_of_philos);
	if (check_error(info->monitor_tid))
		return (0);
	i = -1;
	while (++i < info->number_of_philos)
	{
		if (pthread_create(&info->monitor_tid[i], FT_NULL, \
						monitor, &info->philos[i]))
			return (0);
	}
	return (1);
}
