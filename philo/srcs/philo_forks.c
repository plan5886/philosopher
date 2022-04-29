/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mypark <mypark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 15:24:07 by mypark            #+#    #+#             */
/*   Updated: 2022/04/29 17:32:13 by mypark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"
#include "constant.h"
#include <pthread.h>
#include <stdio.h>

static int	calc_right(int left, int num)
{
	if (left + 1 == num)
		return (0);
	return (left + 1);
}

int	philo_put_forks(t_philo *philo)
{
	int				left;
	int				right;
	int				num;
	pthread_mutex_t	*curr_philo;

	curr_philo = &philo->info->mutexes->philos[philo->id];
	pthread_mutex_lock(curr_philo);
	left = philo->id;
	num = philo->number_of_philos;
	pthread_mutex_unlock(curr_philo);
	right = calc_right(left, num);
	pthread_mutex_unlock(&philo->info->mutexes->forks[left]);
	pthread_mutex_unlock(&philo->info->mutexes->forks[right]);
	return (0);
}

static int	philo_get_forks_in_order(t_philo *philo, int first, int second)
{
	pthread_mutex_lock(&philo->info->mutexes->forks[first]);
	print_msg(MSG_GOT_FORK, philo);
	if (check_grave(philo))
	{
		pthread_mutex_unlock(&philo->info->mutexes->forks[first]);
		return (1);
	}
	pthread_mutex_lock(&philo->info->mutexes->forks[second]);
	print_msg(MSG_GOT_FORK, philo);
	return (0);
}

int	philo_get_forks(t_philo *philo)
{
	int				left;
	int				right;
	int				num;
	pthread_mutex_t	*curr_philo;

	curr_philo = &philo->info->mutexes->philos[philo->id];
	pthread_mutex_lock(curr_philo);
	left = philo->id;
	num = philo->number_of_philos;
	pthread_mutex_unlock(curr_philo);
	right = calc_right(left, num);
	if (philo->id % 2 == 0 && philo_get_forks_in_order(philo, left, right))
		return (1);
	else if (philo->id % 2 && philo_get_forks_in_order(philo, right, left))
		return (1);
	if (check_grave(philo))
		philo_put_forks(philo);
	return (0);
}
