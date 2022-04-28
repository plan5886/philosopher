/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_to_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mypark <mypark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 19:54:46 by mypark            #+#    #+#             */
/*   Updated: 2022/04/19 05:10:06 by mypark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"
#include <stdio.h>

static int	check_input_error(int *target, char *input)
{
	*target = ft_atou(input);
	if (*target < 0)
	{
		printf("INPUT ERROR\n");
		return (1);
	}
	return (0);
}

int	input_to_info(t_info *info, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("INPUT ERROR\n");
		return (0);
	}
	if (check_input_error(&info->number_of_philos, argv[1]))
		return (0);
	if (check_input_error(&info->time_to_die, argv[2]))
		return (0);
	if (check_input_error(&info->time_to_eat, argv[3]))
		return (0);
	if (check_input_error(&info->time_to_sleep, argv[4]))
		return (0);
	info->number_of_time_must_eat = 2147483647;
	if (argv[5] && check_input_error(&info->number_of_time_must_eat, argv[5]))
		return (0);
	if (info->number_of_philos == 0)
	{
		printf("INPUT ERROR\n");
		return (0);
	}
	info->grave = 0;
	info->start = 0;
	return (1);
}
