/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mypark <mypark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 15:04:02 by mypark            #+#    #+#             */
/*   Updated: 2022/04/28 16:16:46 by mypark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "philo.h"
#include "constant.h"
#include "utils.h"

static int	print_one_philo(t_info *info)
{
	printf(MSG_THINKING, gettime_mili(&info->start_tv), 0);
	printf(MSG_DIED, gettime_mili(&info->start_tv), 0);
	return (1);
}

static void	clear_all(t_info *info, pid_t *philo_pids)
{
	free(philo_pids);
	sem_close(info->forks_sem);
	sem_close(info->print_sem);
	sem_unlink(info->forks_sem);
	sem_unlink(info->print_sem);
}

static int	kill_philos(t_info *info, pid_t *philo_pids)
{
	int	i;

	i = -1;
	while (++i < info->number_of_philos)
		kill(philo_pids[i], 15);
	return (0);
}

static int	monitor_death(t_info *info, pid_t *philo_pids)
{
	int	i;
	int	ws;

	i = -1;
	while (++i < info->number_of_philos)
	{
		waitpid(-1, &ws, 0);
		if (calc_exit_status(ws) != IMFULL)
			return (kill_philos(info, philo_pids));
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	info;
	pid_t	*philo_pids;
	int		parent;

	if (input_to_info(&info, argc, argv) == 0)
		return (1);
	if (info.number_of_philos == 1 && print_one_philo(&info))
		return (0);
	generate_semaphores(&info);
	philo_pids = generate_childs(&info);
	parent = (info.philo_id == info.number_of_philos);
	if (parent)
		monitor_death(&info, philo_pids);
	else
		proc_philo(&info);
	clear_all(&info, philo_pids);
	return (0);
}
