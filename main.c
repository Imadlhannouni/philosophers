/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhannou <ilhannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 13:39:45 by ilhannou          #+#    #+#             */
/*   Updated: 2025/08/16 11:21:37 by ilhannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	join_threads(t_main *m)
{
	int i;

	i = 0;
	while (i < m->numb_philo)
		pthread_join(m->philos[i++].thread, NULL);
}

int	main(int ac, char **av)
{
	t_main		*m;
	t_args		 a;
	pthread_t	mon;

	if (!parse_args(ac, av, &a))
		return (1);
	if (!init_all(&m, &a))
		return (1);
	pthread_create(&mon, NULL, &monitor, m);
	join_threads(m);
	pthread_join(mon, NULL);
	free_all(m);
	return (0);
}



