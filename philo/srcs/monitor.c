/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mypark <mypark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 13:29:53 by mypark            #+#    #+#             */
/*   Updated: 2022/04/30 13:00:39 by mypark           ###   ########.fr       */
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
	int				interval;
	int				must_eat;
	int				i;
	int				done;

	usleep(500);
	info = (t_global_info *)arg;
	while (1)
	{
		i = -1;
		done = 0;
		while (++i < info->number_of_philos)
		{
			philo = &info->philos[i];
			pthread_mutex_lock(&info->mutexes->philos[philo->id]);
			interval = gettime_mili(&philo->eaten_time);
			must_eat = philo->number_of_time_must_eat;
			pthread_mutex_unlock(&info->mutexes->philos[philo->id]);
			if (must_eat == 0)
			{
				done++;
				continue;
			}
			if (interval > info->time_to_die)
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
		}
		if (done == info->number_of_philos)
			return (FT_NULL);
		usleep(500);
	}
	return (FT_NULL);
}
