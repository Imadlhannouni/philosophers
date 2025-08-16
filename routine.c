/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhannou <ilhannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:09:08 by ilhannou          #+#    #+#             */
/*   Updated: 2025/08/16 20:36:50 by ilhannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *a)
{
    t_philo *p;

	p = (t_philo *)a;
    if (p->id % 2 == 0)
        ft_usleep(p, p->time_to_eat / 2);
    while (!check_death(p->main))
    {
		if (!take_forks(p))
			return NULL;
        if (p->main->numb_philo == 1)
			return NULL;
        start_eating(p);
        drop_forks(p);
        if (p->numb_of_eat == 0)
			return NULL;
        philo_sleep(p);
        philo_think(p);
    }
    return NULL;
}
