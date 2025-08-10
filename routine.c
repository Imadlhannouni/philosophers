/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhannou <ilhannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:09:08 by ilhannou          #+#    #+#             */
/*   Updated: 2025/08/10 17:21:53 by ilhannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	numb_of_meals(t_main *main)
{
	pthread_mutex_lock(&main->finished_mutex);
	if (main->philosophers_finished == main->numb_philo)
	{
		pthread_mutex_lock(&main->dead_mutex);
		main->dead_flag = 1;
		pthread_mutex_unlock(&main->dead_mutex);
		pthread_mutex_unlock(&main->finished_mutex);
		return (0);
	}
	pthread_mutex_unlock(&main->finished_mutex);
	return (1);
}

void *monitor(void *arg)
{
	t_main *main = (t_main *)arg;
	int i;

	while (1)
	{
		i = 0;
		while (i < main->numb_philo)
		{
			pthread_mutex_lock(&main->eat_mutex);
			if ((get_time() - main->philos[i].last_meal) >= main->philos[i].time_to_die && main->philos[i].numb_of_eat != 0)
			{
				pthread_mutex_lock(&main->dead_mutex);
				main->dead_flag = 1;
				pthread_mutex_unlock(&main->dead_mutex);
				printf("%lu %d died\n", get_time() - main->start_time, main->philos[i].id);
				pthread_mutex_unlock(&main->eat_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&main->eat_mutex);
			i++;
		}
		if (!numb_of_meals(main))
			return (NULL);
		usleep(1000);
	}
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo*)arg;

	while (1)
	{
		if (check_death(philo))
			return NULL ;
		pthread_mutex_t *first;
		pthread_mutex_t *second;
		
		first = philo->l_fork;
		second = philo->r_fork; 
		printf("Philo %d is thinking\n", philo->id);
		if (first < second)
		{
			pthread_mutex_lock(first);
			printf("Philo %d took right fork\n", philo->id);
			pthread_mutex_lock(second);
			printf("Philo %d took left fork\n", philo->id);
		}
		else
		{
			pthread_mutex_lock(second);
			printf("Philo %d took right fork\n", philo->id);
			pthread_mutex_lock(first);
			printf("Philo %d took left fork\n", philo->id);
		}

		philo->is_eating = 1;
		pthread_mutex_lock(&philo->main->eat_mutex);
		philo->last_meal = get_time();
		pthread_mutex_unlock(&philo->main->eat_mutex);
		printf("Philo %d is eating and num : %ld\n", philo->id, philo->numb_of_eat);
		if (philo->numb_of_eat > 0)
			philo->numb_of_eat--;
		if (philo->numb_of_eat == 0)
		{
			pthread_mutex_lock(&philo->main->finished_mutex);
			philo->main->philosophers_finished++;
			pthread_mutex_unlock(&philo->main->finished_mutex);
			pthread_mutex_unlock(philo->r_fork);
			pthread_mutex_unlock(philo->l_fork);
			return (NULL);
		}
		precise_sleep(philo->time_to_eat);
		philo->is_eating = 0;
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		if (check_death(philo))
			return (NULL);
		printf("Philo %d is sleeping\n", philo->id);
		precise_sleep(philo->time_to_sleep);
	}
	return (NULL);
}
