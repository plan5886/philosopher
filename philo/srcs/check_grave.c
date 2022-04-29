/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_grave.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mypark <mypark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 15:34:06 by mypark            #+#    #+#             */
/*   Updated: 2022/04/29 17:35:53 by mypark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

int	check_grave(t_philo *philo)
{
	int	grave;

	pthread_mutex_lock(&philo->info->mutexes->grave);
	grave = philo->info->grave;
	pthread_mutex_unlock(&philo->info->mutexes->grave);
	return (grave);
}
