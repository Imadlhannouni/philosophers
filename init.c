/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhannou <ilhannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 10:19:00 by ilhannou          #+#    #+#             */
/*   Updated: 2025/08/18 17:06:50 by ilhannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	assign_forks(t_main *m, int i)
{
	m->philos[i].l_fork = &m->forks[i];
	m->philos[i].r_fork = &m->forks[(i + 1) % m->numb_philo];
}

static void	init_philo(t_main *m, t_args *a, int i)
{
	m->philos[i].id = i + 1;
	m->philos[i].main = m;
	m->philos[i].is_eating = 0;
	m->philos[i].time_to_die = a->time_to_die;
	m->philos[i].time_to_eat = a->time_to_eat;
	m->philos[i].time_to_sleep = a->time_to_sleep;
	m->philos[i].numb_of_eat = a->numb_time_eat;
	m->philos[i].last_meal = 0;
	assign_forks(m, i);
}

static int	init_base(t_main **out, t_args *a)
{
	int		i;
	t_main	*m;

	m = malloc(sizeof(t_main));
	if (!m)
		return (0);
	m->philos = malloc(sizeof(t_philo) * a->numb_philo);
	m->forks = malloc(sizeof(pthread_mutex_t) * a->numb_philo);
	if (!m->philos || !m->forks)
		return (free(m->philos), free(m->forks), free(m), 0);
	m->dead_flag = 0;
	m->numb_philo = a->numb_philo;
	m->philosophers_finished = 0;
	m->numb_time_eat = a->numb_time_eat;
	pthread_mutex_init(&m->finished_mutex, NULL);
	pthread_mutex_init(&m->eat_mutex, NULL);
	pthread_mutex_init(&m->dead_mutex, NULL);
	pthread_mutex_init(&m->print_mutex, NULL);
	i = 0;
	while (i < a->numb_philo)
		pthread_mutex_init(&m->forks[i++], NULL);
	m->start_time = get_time_in_ms();
	*out = m;
	return (1);
}

static void	init_and_start_philos(t_main *m, t_args *a)
{
	int	i;

	i = 0;
	while (i < a->numb_philo)
	{
		init_philo(m, a, i);
		m->philos[i].last_meal = m->start_time;
		pthread_create(&m->philos[i].thread, NULL, &routine, &m->philos[i]);
		i++;
	}
}

int	init_all(t_main **out, t_args *a)
{
	if (!init_base(out, a))
		return (0);
	init_and_start_philos(*out, a);
	return (1);
}
