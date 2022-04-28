/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_philos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mypark <mypark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 17:21:09 by mypark            #+#    #+#             */
/*   Updated: 2022/04/28 15:36:40 by mypark           ###   ########.fr       */
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

static int	allocate_mutexes(t_info *info)
{
	int	num;
	int	i;

	num = info->number_of_philos;
	info->mutexes = malloc(sizeof(pthread_mutex_t) * num);
	if (info->mutexes == FT_NULL)
		return (0);
	i = -1;
	while (++i < num)
	{
		if (pthread_mutex_init(&info->mutexes[i], FT_NULL))
			return (0);
	}
	if (pthread_mutex_init(&info->print_mutex, FT_NULL))
		return (0);
	return (1);
}

static int	generate_threads(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->number_of_philos)
		if (pthread_create(&info->tid[i], \
						FT_NULL, daily_routine, &info->philos[i]))
			return (0);
	return (1);
}

int	generate_philos(t_info *info)
{
	info->tid = malloc(sizeof(pthread_t) * info->number_of_philos);
	if (check_error(info->tid))
		return (0);
	info->forks = malloc(sizeof(int) * info->number_of_philos);
	if (check_error(info->forks))
		return (0);
	memset(info->forks, 0, info->number_of_philos * 4);
	if (allocate_mutexes(info) == 0)
		return (0);
	info->philos = allocate_philos(info);
	if (check_error(info->philos))
		return (0);
	if (generate_threads(info) == 0)
		return (0);
	return (1);
}
