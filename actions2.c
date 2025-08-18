/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhannou <ilhannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:09:23 by ilhannou          #+#    #+#             */
/*   Updated: 2025/08/18 17:17:22 by ilhannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_think(t_philo *p)
{
	long	buffer;

	if (check_death(p->main))
		return ;
	log_action(p, "is thinking");
	buffer = (p->time_to_die - (p->time_to_eat + p->time_to_sleep));
	if (buffer > 0)
		ft_usleep(p, buffer / 2);
}
