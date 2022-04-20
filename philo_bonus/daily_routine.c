/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daily_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mypark <mypark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 17:01:11 by mypark            #+#    #+#             */
/*   Updated: 2022/04/20 11:33:44 by mypark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "constant.h"
#include "utils.h"
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

static void	philo_put_forks(t_philo *philo)
{
	sem_post(philo->info->forks_sem);
	sem_post(philo->info->forks_sem);
}

static void	philo_sleeping(t_philo *philo)
{
	int	time;
	int	interval;

	print_msg(MSG_SLEEPING, philo);
	time = gettime_mili(&philo->info->start_tv);
	interval = time + philo->info->time_to_sleep - philo->eaten_time;
	if (philo->info->time_to_sleep > 0)
		usleep(philo->info->time_to_sleep * MILI_TO_MICRO);
	else
		usleep(1);
}

static void	philo_eating(t_philo *philo)
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
	}
	philo->eat_count++;
	if (philo->eat_count >= info->number_of_time_must_eat)
		exit(IMFULL);
}

static void	philo_get_forks(t_philo *philo)
{
	sem_t	*forks_sem;

	forks_sem = philo->info->forks_sem;
	if (philo->id % 2 == 0)
	{
		sem_wait(forks_sem);
		print_msg(MSG_GOT_FORK, philo);
		sem_wait(forks_sem);
		print_msg(MSG_GOT_FORK, philo);
	}
	else
	{
		sem_wait(forks_sem);
		print_msg(MSG_GOT_FORK, philo);
		sem_wait(forks_sem);
		print_msg(MSG_GOT_FORK, philo);
	}
}

void	daily_routine(t_philo	*philo)
{
	while (1)
	{
		print_msg(MSG_THINKING, philo);
		philo_get_forks(philo);
		philo_eating(philo);
		philo_put_forks(philo);
		philo_sleeping(philo);
	}
}
