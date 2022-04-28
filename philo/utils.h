/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mypark <mypark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 15:05:36 by mypark            #+#    #+#             */
/*   Updated: 2022/04/28 11:38:30 by mypark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "philo.h"
# include <sys/time.h>

int		check_error(void *ret);
int		gettime_mili(struct timeval *start_tv);
int		ft_atou(const char *str);
void	print_msg(char *fmt, t_philo *philo);
void	ft_spinlock(int *flag);

#endif