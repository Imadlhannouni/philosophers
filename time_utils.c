/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhannou <ilhannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 10:16:00 by ilhannou          #+#    #+#             */
/*   Updated: 2025/08/16 20:36:45 by ilhannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <sys/time.h>

time_t	get_time_in_ms(void)
{
	struct timeval		v;

	gettimeofday(&v, NULL);
	return ((v.tv_sec * 1000) + (v.tv_usec / 1000));
}

void	ft_usleep(t_philo *p, long ms)
{
	time_t start = get_time_in_ms();

	while (!check_death(p->main))
	{
		if ((get_time_in_ms() - start) >= ms)
			break ;
		usleep(200);
	}
}

static void	active_sleep_until(time_t wake_up, t_philo *p)
{
	while (get_time_in_ms() < wake_up)
	{
		if (check_death(p->main))
			break ;
		usleep(100);
	}
}

void	philo_sleep(t_philo *p)
{
	time_t	wake_up;

	if (check_death(p->main))
		return ;
	log_action(p, "is sleeping");
	wake_up = get_time_in_ms() + p->time_to_sleep;
	active_sleep_until(wake_up, p);
}
