/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_philos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mypark <mypark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 17:21:09 by mypark            #+#    #+#             */
/*   Updated: 2022/04/19 07:51:35 by mypark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"
#include "constant.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void	init_philo(t_philo *philo, int id, t_info *info)
{
	philo->id = id;
	philo->info = info;
	philo->eaten_time = gettime_mili(&info->start_tv);
	philo->left_mutex = &info->mutexes[id];
	philo->left_fork = &info->forks[id];
	philo->eat_count = 0;
	if (id + 1 == info->number_of_philos)
	{
		philo->right_mutex = &info->mutexes[0];
		philo->right_fork = &info->forks[0];
	}
	else
	{
		philo->right_mutex = &info->mutexes[id + 1];
		philo->right_fork = &info->forks[id + 1];
	}
}

static t_philo	*allocate_philos(t_info *info)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * info->number_of_philos);
	if (philos == FT_NULL)
		return (FT_NULL);
	i = -1;
	while (++i < info->number_of_philos)
		init_philo(&philos[i], i, info);
	return (philos);
}

static pthread_mutex_t	*allocate_mutexes(int num)
{
	pthread_mutex_t	*mu;
	int				i;

	mu = malloc(sizeof(pthread_mutex_t) * num);
	if (mu == FT_NULL)
		return (FT_NULL);
	i = -1;
	while (++i < num)
		pthread_mutex_init(&mu[i], FT_NULL);
	return (mu);
}

t_philo	*generate_philos(t_info *info)
{
	t_philo	*philos;
	int		i;

	info->tid = malloc(sizeof(pthread_t) * info->number_of_philos);
	if (check_error(info->tid))
		return (FT_NULL);
	info->forks = malloc(sizeof(int) * info->number_of_philos);
	if (check_error(info->forks))
		return (FT_NULL);
	memset(info->forks, 0, info->number_of_philos);
	info->mutexes = allocate_mutexes(info->number_of_philos);
	pthread_mutex_init(&info->print_mutex, FT_NULL);
	if (check_error(info->mutexes))
		return (FT_NULL);
	philos = allocate_philos(info);
	if (check_error(philos))
		return (FT_NULL);
	i = -1;
	while (++i < info->number_of_philos)
		pthread_create(&info->tid[i], FT_NULL, daily_routine, &philos[i]);
	return (philos);
}
