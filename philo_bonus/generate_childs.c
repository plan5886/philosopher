/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_childs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mypark <mypark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 05:56:23 by mypark            #+#    #+#             */
/*   Updated: 2022/04/21 06:37:37 by mypark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "philo.h"
#include "constant.h"

pid_t	*generate_childs(t_info *info)
{
	pid_t	*philo_pids;
	int		num;

	philo_pids = malloc(sizeof(pid_t) * info->number_of_philos);
	if (philo_pids == FT_NULL)
		return (FT_NULL);
	num = -1;
	while (++num < info->number_of_philos)
	{
		philo_pids[num] = fork();
		if (philo_pids[num] == -1)
		{
			printf("FORK ERROR\n");
			// kill childs
			exit(ERROR);
		}
		if (philo_pids[num] == 0)
			break;
	}
	info->philo_id = num;
	return (philo_pids);
}