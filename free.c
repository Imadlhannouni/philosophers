/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhannou <ilhannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:04:09 by ilhannou          #+#    #+#             */
/*   Updated: 2025/08/16 11:21:37 by ilhannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_all(t_main *m)
{
	int	i;

	i = 0;
	if (!m)
		return ;
	while (i < m->numb_philo)
		pthread_mutex_destroy(&m->forks[i++]);
	pthread_mutex_destroy(&m->eat_mutex);
	pthread_mutex_destroy(&m->dead_mutex);
	pthread_mutex_destroy(&m->finished_mutex);
	pthread_mutex_destroy(&m->print_mutex);
	free(m->philos);
	free(m->forks);
	free(m);
}
