/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mypark <mypark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 17:03:26 by mypark            #+#    #+#             */
/*   Updated: 2022/04/19 07:46:17 by mypark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constant.h"
#include "philo.h"
#include <stdio.h>
#include <sys/time.h>

int	gettime_mili(struct timeval *start_tv)
{
	struct timeval	tv;
	int				mili_time;

	gettimeofday(&tv, NULL);
	mili_time = (tv.tv_sec - start_tv->tv_sec) * SEC_TO_MILI \
			+ (tv.tv_usec - start_tv->tv_usec) / MICRO_TO_MILI;
	return (mili_time);
}

int	check_error(void *ret)
{
	if (ret == FT_NULL)
	{
		printf("ERROR\n");
		return (1);
	}
	return (0);
}

void	print_msg(char *fmt, t_philo *philo)
{
	int	time;

	pthread_mutex_lock(&philo->info->print_mutex);
	if (philo->info->grave == 0)
	{
		time = gettime_mili(&philo->info->start_tv);
		printf(fmt, time, philo->id + 1);
	}
	pthread_mutex_unlock(&philo->info->print_mutex);
}
