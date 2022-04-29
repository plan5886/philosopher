/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mypark <mypark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 11:49:48 by mypark            #+#    #+#             */
/*   Updated: 2022/04/29 17:44:05 by mypark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

int	clear_all(t_global_info *info, t_philo *philos, pthread_t *tids)
{
	if (philos)
		free(philos);
	if (tids)
		free(tids);
	if (info)
	{
		if (info->forks)
			free(info->forks);
		if (info->mutexes)
		{
			if (info->mutexes->forks)
				free(info->mutexes->forks);
			if (info->mutexes->philos)
				free(info->mutexes->philos);
			free(info->mutexes);
		}
	}
	return (1);
}
