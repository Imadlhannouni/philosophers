/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+      */
/*   By: ilhannou <ilhannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 10:18:00 by ilhannou          #+#    #+#             */
/*   Updated: 2025/08/15 10:18:00 by ilhannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death(t_philo *philo)
{
	int d;
	pthread_mutex_lock(&philo->main->dead_mutex);
	d = philo->main->dead_flag;
	pthread_mutex_unlock(&philo->main->dead_mutex);
	return (d);
}

void	set_dead(t_main *m)
{
	pthread_mutex_lock(&m->dead_mutex);
	m->dead_flag = 1;
	pthread_mutex_unlock(&m->dead_mutex);
}

void	mark_finished(t_philo *p)
{
	pthread_mutex_lock(&p->main->finished_mutex);
	p->main->philosophers_finished++;
	pthread_mutex_unlock(&p->main->finished_mutex);
}

int	all_finished(t_main *m)
{
	int d;
	pthread_mutex_lock(&m->finished_mutex);
	d = (m->philosophers_finished == m->numb_philo);
	pthread_mutex_unlock(&m->finished_mutex);
	return (d);
}

static int	check_one(t_philo *p)
{
	time_t now;
	time_t last;
	time_t stamp;
	pthread_mutex_lock(&p->main->eat_mutex);
	last = p->last_meal;
	pthread_mutex_unlock(&p->main->eat_mutex);
	now = get_time_in_ms();
	if (p->numb_of_eat != 0 && now - last > p->time_to_die)
	{
		stamp = now - p->main->start_time;
		pthread_mutex_lock(&p->main->print_mutex);
		if (!p->main->dead_flag)
			printf("%ld %d died\n", (long)stamp, p->id);
		set_dead(p->main);
		pthread_mutex_unlock(&p->main->print_mutex);
		return (1);
	}
	return (0);
}

void	*monitor(void *a)
{
	t_main	*m;
	int		 i;

	m = (t_main *)a;
	while (!check_death(&m->philos[0]))
	{
		i = 0;
		while (i < m->numb_philo)
			if (check_one(&m->philos[i++]))
				return (NULL);
		if (all_finished(m))
		{
			set_dead(m);
			return (NULL);
		}
		usleep(200);
	}
	return (NULL);
}
