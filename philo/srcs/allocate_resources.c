/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_resources.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mypark <mypark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 11:43:23 by mypark            #+#    #+#             */
/*   Updated: 2022/04/29 20:56:42 by mypark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "constant.h"
#include "utils.h"
#include <pthread.h>
#include <stdlib.h>

static void	init_philo(t_philo *philo, int id, t_global_info *info)
{
	philo->id = id;
	philo->info = info;
	philo->number_of_philos = info->number_of_philos;
	philo->time_to_die = info->time_to_die;
	philo->time_to_eat = info->time_to_eat;
	philo->time_to_sleep = info->time_to_sleep;
	philo->number_of_time_must_eat = info->number_of_time_must_eat;
}

static void	init_philos(t_global_info *info, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < info->number_of_philos)
	{
		init_philo(&philos[i], i, info);
		i++;
	}
}

static int	init_mutexes(t_global_info *info)
{
	t_mutexes	*mu;
	int			i;

	mu = info->mutexes;
	if (pthread_mutex_init(&mu->grave, NULL))
		return (0);
	if (pthread_mutex_init(&mu->terminal_print, NULL))
		return (0);
	if (pthread_mutex_init(&mu->start_signal, NULL))
		return (0);
	i = 0;
	while (i < info->number_of_philos)
	{
		if (pthread_mutex_init(&mu->philos[i], NULL))
			return (0);
		if (pthread_mutex_init(&mu->forks[i], NULL))
			return (0);
		i++;
	}
	return (1);
}

int	allocate_resources(t_global_info *info, t_philo **philos, pthread_t **tids)
{
	*philos = malloc(sizeof(t_philo) * info->number_of_philos);
	if (*philos == FT_NULL)
		return (0);
	*tids = malloc(sizeof(pthread_t) * info->number_of_philos + 1);
	if (*tids == FT_NULL && clear_all(FT_NULL, *philos, FT_NULL))
		return (0);
	info->mutexes = malloc(sizeof(t_mutexes));
	if (info->mutexes == FT_NULL && clear_all(FT_NULL, *philos, *tids))
		return (0);
	info->mutexes->forks = FT_NULL;
	info->mutexes->philos = malloc(sizeof(pthread_mutex_t) \
									* info->number_of_philos);
	if (info->mutexes->philos == FT_NULL && clear_all(info, *philos, *tids))
		return (0);
	info->mutexes->forks = malloc(sizeof(pthread_mutex_t) \
									* info->number_of_philos);
	if (info->mutexes->forks == FT_NULL && clear_all(info, *philos, *tids))
		return (0);
	info->forks = malloc(sizeof(int) * info->number_of_philos);
	if (info->forks == FT_NULL && clear_all(info, *philos, *tids))
		return (0);
	if (init_mutexes(info) == 0 && clear_all(info, *philos, *tids))
		return (0);
	info->philos = *philos;
	init_philos(info, *philos);
	return (1);
}
