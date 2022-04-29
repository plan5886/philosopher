/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mypark <mypark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 13:29:53 by mypark            #+#    #+#             */
/*   Updated: 2022/04/29 20:46:38 by mypark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "constant.h"
#include "utils.h"
#include <unistd.h>
#include <stdio.h>

void	*monitor(void *arg)
{
	t_philo			*philo;
	t_global_info	*info;
	int				time_to_die;
	int				interval;
	int				i;

	info = (t_global_info *)arg;
	while (1)
	{
		i = 0;
		while (i < info->number_of_philos)
		{
			philo = &info->philos[i];
			pthread_mutex_lock(&info->mutexes->philos[philo->id]);
			interval = gettime_mili(&philo->eaten_time);
			time_to_die = philo->time_to_die;
			pthread_mutex_unlock(&info->mutexes->philos[philo->id]);
			if (interval > time_to_die)
			{
				pthread_mutex_lock(&info->mutexes->grave);
				if (info->grave == 0)
				{
					pthread_mutex_lock(&info->mutexes->terminal_print);
					printf(MSG_DIED, gettime_mili(&info->start_tv), philo->id + 1);
					pthread_mutex_unlock(&info->mutexes->terminal_print);
				}
				info->grave = 1;
				pthread_mutex_unlock(&info->mutexes->grave);
				return (FT_NULL);
			}
			i++;
		}
		usleep(500);
	}
	return (FT_NULL);
}
