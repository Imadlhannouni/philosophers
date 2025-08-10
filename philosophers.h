/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhannou <ilhannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 13:39:53 by ilhannou          #+#    #+#             */
/*   Updated: 2025/08/10 17:04:35 by ilhannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo 
{
	pthread_t		thread;
	int				id;
	int				is_eating;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	long			numb_of_eat;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	struct s_main	*main;
}	t_philo;

typedef struct s_main
{
	int					numb_time_eat;
	int					numb_philo;
	int					dead_flag;
	int					philosophers_finished; 
	size_t				start_time;
	pthread_mutex_t		*forks; //aray of forks
	pthread_mutex_t		eat_mutex; 
	pthread_mutex_t		dead_mutex;
	pthread_mutex_t		finished_mutex;
	t_philo				*philos;
}	t_main;

typedef struct s_args
{
	int				numb_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			numb_time_eat;
}	t_args;


void	free_all(t_main *main);
void	*monitor(void *arg);
void	*routine(void *arg);
size_t	get_time(void);
int		check_death(t_philo *philo);
void	precise_sleep(size_t time_in_ms);

#endif
