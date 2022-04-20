/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_semaphores.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mypark <mypark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 05:56:23 by mypark            #+#    #+#             */
/*   Updated: 2022/04/20 11:33:10 by mypark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include "philo.h"
#include "constant.h"

static void	check_sem_open_error(sem_t *ret)
{
	if (ret == SEM_FAILED)
	{
		printf("SEM OEPN ERROR\n");
		exit(ERROR);
	}
}

void	generate_semaphores(t_info *info)
{
	int fork_counts;

	sem_unlink("forks");
	sem_unlink("print");
	fork_counts = 2 * info->number_of_philos;
	info->forks_sem = sem_open("forks", O_CREAT, 0777, fork_counts);
	check_sem_open_error(info->forks_sem);
	info->print_sem = sem_open("print", O_CREAT, 0777, 1);
	check_sem_open_error(info->print_sem);
}
