/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mypark <mypark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 15:05:36 by mypark            #+#    #+#             */
/*   Updated: 2022/04/30 11:04:25 by mypark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <sys/time.h>

typedef struct s_global_info	t_global_info;
typedef struct s_philo			t_philo;

typedef struct s_mutexes
{
	pthread_mutex_t	*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	grave;
	pthread_mutex_t	start_signal;
	pthread_mutex_t	terminal_print;
	pthread_mutex_t	input_info;
}				t_mutexes;

struct s_global_info
{
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_time_must_eat;
	struct timeval	start_tv;
	int				grave;
	int				*forks;
	t_mutexes		*mutexes;
	t_philo			*philos;
};

struct s_philo
{
	int				id;
	struct timeval	eaten_time;
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_time_must_eat;
	t_global_info	*info;
};

typedef struct s_personal_info
{
	int	number_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_time_must_eat;
	int	philo_id;
}				t_personal_info;

int		philo_get_forks(t_philo *philo, t_personal_info *personal);
int		philo_put_forks(t_philo *philo, t_personal_info *personal);
int		input_to_info(t_global_info *info, int argc, char **argv);
void	*daily_routine(void *arg);
int		allocate_resources(\
	t_global_info *info, \
	t_philo **philos, \
	pthread_t **tids\
);
void	*monitor(void *arg);

#endif