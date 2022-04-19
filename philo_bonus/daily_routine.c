/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daily_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mypark <mypark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 17:01:11 by mypark            #+#    #+#             */
/*   Updated: 2022/04/19 07:35:52 by mypark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "constant.h"
#include "utils.h"
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

static int	philo_put_forks(t_philo *philo)
{
	*philo->left_fork = 0;
	*philo->right_fork = 0;
	pthread_mutex_unlock(philo->left_mutex);
	pthread_mutex_unlock(philo->right_mutex);
	return (1);
}

static int	philo_sleeping(t_philo *philo)
{
	int	time;
	int	interval;

	print_msg(MSG_SLEEPING, philo);
	time = gettime_mili(&philo->info->start_tv);
	interval = time + philo->info->time_to_sleep - philo->eaten_time;
	if (philo->info->grave)
		return (0);
	if (philo->info->time_to_sleep > 0)
		usleep(philo->info->time_to_sleep * MILI_TO_MICRO);
	else
		usleep(1);
	return (1);
}

static int	philo_eating(t_philo *philo)
{
	int		curr_time;
	int		interval;
	t_info	*info;

	info = philo->info;
	print_msg(MSG_EATING, philo);
	philo->eaten_time = gettime_mili(&info->start_tv);
	interval = 0;
	while (interval < info->time_to_eat)
	{
		curr_time = gettime_mili(&info->start_tv);
		interval = curr_time - philo->eaten_time;
		if (info->grave)
		{
			philo_put_forks(philo);
			return (0);
		}
	}
	philo->eat_count++;
	if (philo->eat_count >= info->number_of_time_must_eat)
	{
		philo_put_forks(philo);
		return (0);
	}
	return (1);
}

static int	philo_get_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_mutex);
		print_msg(MSG_GOT_FORK, philo);
		*philo->left_fork = 1;
		if (philo->info->grave && philo_put_forks(philo))
			return (0);
		pthread_mutex_lock(philo->right_mutex);
		print_msg(MSG_GOT_FORK, philo);
		*philo->right_fork = 1;
	}
	else
	{
		pthread_mutex_lock(philo->right_mutex);
		print_msg(MSG_GOT_FORK, philo);
		*philo->right_fork = 1;
		if (philo->info->grave && philo_put_forks(philo))
			return (0);
		pthread_mutex_lock(philo->left_mutex);
		print_msg(MSG_GOT_FORK, philo);
		*philo->left_fork = 1;
	}
	if (philo->info->grave && philo_put_forks(philo))
		return (0);
	return (1);
}

void	*daily_routine(void *arg)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)arg;
	info = philo->info;
	while (1)
	{
		print_msg(MSG_THINKING, philo);
		if (info->grave || philo_get_forks(philo) == 0)
			break ;
		if (info->grave || philo_eating(philo) == 0)
			break ;
		philo_put_forks(philo);
		if (info->grave || philo_sleeping(philo) == 0)
			break ;
	}
	philo_put_forks(philo);
	return (FT_NULL);
}
