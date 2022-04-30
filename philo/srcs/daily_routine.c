/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daily_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mypark <mypark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 17:01:11 by mypark            #+#    #+#             */
/*   Updated: 2022/04/30 11:54:51 by mypark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "constant.h"
#include "utils.h"
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

static int	philo_sleeping(t_philo *philo, t_personal_info *personal)
{
	print_msg(MSG_SLEEPING, philo);
	if (personal->time_to_sleep > 0)
		usleep(personal->time_to_sleep * MILI_TO_MICRO);
	else
		usleep(1);
	return (0);
}

static int	philo_eating(t_philo *philo, t_personal_info *personal)
{
	int				interval;
	int				ret;
	struct timeval	tv;
	pthread_mutex_t	*curr_philo;

	curr_philo = &philo->info->mutexes->philos[philo->id];
	personal->number_of_time_must_eat--;
	ret = (personal->number_of_time_must_eat == 0);
	pthread_mutex_lock(curr_philo);
	gettimeofday(&philo->eaten_time, NULL);
	philo->number_of_time_must_eat = personal->number_of_time_must_eat;
	pthread_mutex_unlock(curr_philo);
	gettimeofday(&tv, NULL);
	print_msg(MSG_EATING, philo);
	interval = 0;
	while (interval < personal->time_to_eat)
		interval = gettime_mili(&tv);
	return (ret);
}

void	dup_input_info(t_philo *philo, t_personal_info *info, t_mutexes *mu)
{
	pthread_mutex_lock(&mu->input_info);
	info->number_of_philos = philo->info->number_of_philos;
	info->number_of_time_must_eat = philo->info->number_of_time_must_eat;
	info->time_to_die = philo->info->time_to_die;
	info->time_to_eat = philo->info->time_to_eat;
	info->time_to_sleep = philo->info->time_to_sleep;
	pthread_mutex_unlock(&mu->input_info);
	pthread_mutex_lock(&mu->philos[philo->id]);
	info->philo_id = philo->id;
	pthread_mutex_unlock(&mu->philos[philo->id]);
}

void	*daily_routine(void *arg)
{
	t_philo			*philo;
	t_mutexes		*mu;
	t_personal_info	personal;

	philo = (t_philo *)arg;
	mu = philo->info->mutexes;
	dup_input_info(philo, &personal, mu);
	pthread_mutex_lock(&mu->start_signal);
	pthread_mutex_unlock(&mu->start_signal);
	while (1)
	{
		print_msg(MSG_THINKING, philo);
		if (check_grave(philo) || philo_get_forks(philo, &personal))
			break ;
		if (check_grave(philo) \
			|| (philo_eating(philo, &personal) \
			&& philo_put_forks(philo, &personal)))
			break ;
		philo_put_forks(philo, &personal);
		if (check_grave(philo) || philo_sleeping(philo, &personal))
			break ;
	}
	return (FT_NULL);
}
