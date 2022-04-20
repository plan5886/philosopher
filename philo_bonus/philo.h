/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mypark <mypark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 15:05:36 by mypark            #+#    #+#             */
/*   Updated: 2022/04/20 08:56:50 by mypark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/types.h>

typedef struct s_info	t_info;
typedef struct s_philo	t_philo;

struct s_info
{
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_time_must_eat;
	struct timeval	start_tv;
	int				philo_id;
	sem_t			*forks_sem;
	sem_t			*print_sem;
};

struct s_philo
{
	int		id;
	t_info	*info;
	int		eaten_time;
	int		eat_count;
};

void	proc_philo(t_info *info);
void	generate_semaphores(t_info *info);
pid_t	*generate_childs(t_info *info);
int		generate_monitors(t_info *info);
int		input_to_info(t_info *info, int argc, char **argv);
void	daily_routine(t_philo *philo);

#endif