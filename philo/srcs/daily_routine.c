/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daily_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mypark <mypark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 17:01:11 by mypark            #+#    #+#             */
/*   Updated: 2022/04/29 20:52:34 by mypark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "constant.h"
#include "utils.h"
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

static int	philo_sleeping(t_philo *philo)
{
	int				time_to_sleep;
	pthread_mutex_t	*curr_philo;

	print_msg(MSG_SLEEPING, philo);
	curr_philo = &philo->info->mutexes->philos[philo->id];
	pthread_mutex_lock(curr_philo);
	time_to_sleep = philo->time_to_sleep;
	pthread_mutex_unlock(curr_philo);
	if (time_to_sleep > 0)
		usleep(time_to_sleep * MILI_TO_MICRO);
	else
		usleep(1);
	return (0);
}

static int	philo_eating(t_philo *philo)
{
	int				time_to_eat;
	int				interval;
	int				ret;
	struct timeval	tv;
	pthread_mutex_t	*curr_philo;

	curr_philo = &philo->info->mutexes->philos[philo->id];
	print_msg(MSG_EATING, philo);
	pthread_mutex_lock(curr_philo);
	gettimeofday(&philo->eaten_time, NULL);
	time_to_eat = philo->time_to_eat;
	pthread_mutex_unlock(curr_philo);
	gettimeofday(&tv, NULL);
	interval = 0;
	while (interval < time_to_eat)
		interval = gettime_mili(&tv);
	pthread_mutex_lock(curr_philo);
	philo->number_of_time_must_eat--;
	ret = (philo->number_of_time_must_eat == 0);
	pthread_mutex_unlock(curr_philo);
	return (ret);
}

void	*daily_routine(void *arg)
{
	t_philo			*philo;
	t_global_info	*info;

	philo = (t_philo *)arg;
	info = philo->info;
	pthread_mutex_lock(&info->mutexes->start_signal);
	pthread_mutex_unlock(&info->mutexes->start_signal);
	while (1)
	{
		print_msg(MSG_THINKING, philo);
		if (check_grave(philo) || philo_get_forks(philo))
			break ;
		if (check_grave(philo) || philo_eating(philo))
			break ;
		philo_put_forks(philo);
		if (check_grave(philo) || philo_sleeping(philo))
			break ;
	}
	return (FT_NULL);
}
