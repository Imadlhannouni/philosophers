/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhannou <ilhannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:09:08 by ilhannou          #+#    #+#             */
/*   Updated: 2025/08/16 12:05:08 by ilhannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *a)
{
	t_philo *p;

	p = (t_philo *)a;
	sim_start_delay(p->main->start_time);
	if (p->id % 2 == 0)
		sleep_for(p, 1);
	while (!check_death(p))
	{
		philo_think(p);
		take_forks(p);
		if (p->main->numb_philo == 1)
			return (NULL);
		start_eating(p);
		drop_forks(p);
		if (p->numb_of_eat == 0)
			return (NULL);
		philo_sleep(p);
	}
	return (NULL);
}
