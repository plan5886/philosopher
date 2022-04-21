/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mypark <mypark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 08:15:04 by mypark            #+#    #+#             */
/*   Updated: 2022/04/21 10:47:39 by mypark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"
#include "constant.h"
#include <stdio.h>
#include <stdlib.h>

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

static void	*self_monitor(void *arg)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)arg;
	info = philo->info;
	while (1)
	{
		if (is_died(philo))
		{
			sem_wait(info->print_sem);
			printf(MSG_DIED, gettime_mili(&info->start_tv), philo->id + 1);
			exit(DIED);
		}
	}
	return (FT_NULL);
}

static void	init_philo(t_philo *philo, t_info *info)
{
	philo->id = info->philo_id;
	philo->info = info;
	philo->eaten_time = gettime_mili(&info->start_tv);
	philo->eat_count = 0;
}

void	proc_philo(t_info *info)
{
	t_philo		*philo;
	pthread_t	tid;

	philo = malloc(sizeof(philo));
	if (philo == FT_NULL)
	{
		printf("CHILD MALLOC ERROR\n");
		exit(ERROR);
	}
	init_philo(philo, info);
	pthread_create(&tid, FT_NULL, self_monitor, philo);
	daily_routine(philo);
}
