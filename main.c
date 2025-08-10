/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhannou <ilhannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 13:39:45 by ilhannou          #+#    #+#             */
/*   Updated: 2025/08/10 17:12:25 by ilhannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	res;

	sign = 1;
	res = 0;
	i = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
	{
		i++;
	}
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		res = res * 10 + nptr[i] - '0';
		i++;
	}
	return (res * sign);
}

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->main->dead_mutex);
	if (philo->main->dead_flag)
	{
		pthread_mutex_unlock(&philo->main->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->main->dead_mutex);
	return (0);
}

size_t	get_time(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	precise_sleep(size_t time_in_ms)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < time_in_ms)
		usleep(100);
}

t_main	*init_philos(t_args *args)
{
	t_main		*main;
	int		i;

	main = malloc(sizeof(t_main));
	if (!main)
		return (NULL);
	main->philos = malloc(sizeof(t_philo) * args->numb_philo);
	main->forks = malloc(sizeof(pthread_mutex_t) * args->numb_philo);
	main->dead_flag = 0;
	main->numb_philo = args->numb_philo;
	main->start_time = get_time();
	main->philosophers_finished = 0;
	pthread_mutex_init(&main->finished_mutex, NULL);
	pthread_mutex_init(&main->eat_mutex, NULL);
	pthread_mutex_init(&main->dead_mutex, NULL);
	i = 0;
	while (i < args->numb_philo)
		pthread_mutex_init(&main->forks[i++], NULL);
	i = 0;
	
	while (i < args->numb_philo)
	{
		main->philos[i].id = i + 1;
		main->philos[i].time_to_die = args->time_to_die;
		main->philos[i].time_to_eat = args->time_to_eat;
		main->philos[i].time_to_sleep = args->time_to_sleep;
		main->philos[i].numb_of_eat = args->numb_time_eat;
		if (args->numb_philo % 2 == 0)
		{
			main->philos[i].l_fork = &main->forks[i]; // even or odd 
			main->philos[i].r_fork = &main->forks[(i + 1) % args->numb_philo];	
		}
		else
		{
			main->philos[i].l_fork = &main->forks[(i + 1) % args->numb_philo];
			main->philos[i].r_fork = &main->forks[i]; // even or odd 
		}
		main->philos[i].last_meal = main->start_time;
		main->philos[i].main = main;
		i++;
	}
	i = 0;
	while (i < args->numb_philo)
	{
		pthread_create(&main->philos[i].thread, NULL, &routine, &main->philos[i]);
		i++;
	}
	return (main);
}

int main(int argc, char *argv[])
{
	t_main		*main;
	t_args		args;
	pthread_t	monitor_thread;
	int			i;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s <nb_philo> <time_to_die> <time_to_eat> <time_to_sleep> <number_of_times_each_philosopher_must_eat>\n", argv[0]);
		return 1;
	}
	args.numb_philo = ft_atoi(argv[1]);
	args.time_to_die = ft_atoi(argv[2]);
	args.time_to_eat = ft_atoi(argv[3]);
	args.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args.numb_time_eat = ft_atoi(argv[5]);
	else
		args.numb_time_eat = -1; // GOOD 
	main = init_philos(&args);
	if (!main)
		return 1;
	pthread_create(&monitor_thread, NULL, &monitor, main);
	i = 0;
	while (i < main->numb_philo)
	{
		pthread_join(main->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);// delete 
	free_all(main);
	return 0;
}



