/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhannou <ilhannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:59:23 by ilhannou          #+#    #+#             */
/*   Updated: 2025/08/18 16:59:37 by ilhannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death(t_main *m)
{
	int	d;

	pthread_mutex_lock(&m->dead_mutex);
	d = m->dead_flag;
	pthread_mutex_unlock(&m->dead_mutex);
	return (d);
}
