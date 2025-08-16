/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhannou <ilhannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 13:39:53 by ilhannou          #+#    #+#             */
/*   Updated: 2025/08/16 12:05:08 by ilhannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <stdlib.h>
/* get_time_in_ms() returns current epoch milliseconds (using gettimeofday) */

typedef struct s_philo 
{
	pthread_t		thread;
	int				id;
	int				is_eating;
	time_t			last_meal;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	long			numb_of_eat;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	struct s_main	*main;
}	t_philo;

typedef struct s_main
{
	int				numb_time_eat;
	int				numb_philo;
	int				dead_flag;
	int				philosophers_finished;
	time_t			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	finished_mutex;
	pthread_mutex_t	print_mutex;
	t_philo			*philos;
}	t_main;

typedef struct s_args
{
	int				numb_philo;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	long			numb_time_eat;
}	t_args;


/* parsing */
int		parse_args(int ac, char **av, t_args *args);
long	ft_atol(const char *s);

/* init */
int		init_all(t_main **out, t_args *args);
void	assign_forks(t_main *main, int i);

/* time utils */
time_t	get_time_in_ms(void);
void	philo_sleep(t_philo *p);
void	sim_start_delay(time_t start_time);
void	sleep_for(t_philo *p, time_t ms);

/* monitor & routine helpers */
int		check_death(t_philo *philo);
void	set_dead(t_main *main);
int		all_finished(t_main *main);
void	mark_finished(t_philo *philo);

/* actions */
void	take_forks(t_philo *p);
void	start_eating(t_philo *p);
void	drop_forks(t_philo *p);
void	philo_sleep(t_philo *p);
void	philo_think(t_philo *p);
void	log_action(t_philo *p, const char *msg);

/* threads */
void	*routine(void *arg);
void	*monitor(void *arg);

/* free */
void	free_all(t_main *main);


#endif
