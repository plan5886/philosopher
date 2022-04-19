/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mypark <mypark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 15:05:36 by mypark            #+#    #+#             */
/*   Updated: 2022/04/19 07:52:07 by mypark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <sys/time.h>

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
	int				grave;
	int				*forks;
	pthread_mutex_t	*mutexes;
	pthread_mutex_t	monitor_mutex;
	pthread_mutex_t	print_mutex;
	pthread_t		*tid;
	pthread_t		*monitor_tid;
	t_philo			*philos;
};

struct s_philo
{
	int				id;
	int				*left_fork;
	int				*right_fork;
	pthread_mutex_t	*left_mutex;
	pthread_mutex_t	*right_mutex;
	t_info			*info;
	int				eaten_time;
	int				eat_count;
};

t_philo	*generate_philos(t_info *info);
int		generate_monitors(t_info *info);
int		input_to_info(t_info *info, int argc, char **argv);
void	*daily_routine(void *arg);

#endif