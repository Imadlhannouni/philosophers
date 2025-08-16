/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhannou <ilhannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 10:15:00 by ilhannou          #+#    #+#             */
/*   Updated: 2025/08/16 11:21:37 by ilhannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_digit(int c)
{
	return (c >= '0' && c <= '9');
}

long	ft_atol(const char *s)
{
	long	sign;
	long	r;
	int		i;

	sign = 1;
	r = 0;
	i = 0;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (is_digit(s[i]))
	{
		r = r * 10 + (s[i] - '0');
		if (r > INT_MAX)
			return (-1);
		i++;
	}
	return (r * sign);
}

static int	set_args(t_args *a, int ac, char **av)
{
	a->numb_philo = (int)ft_atol(av[1]);
	a->time_to_die = ft_atol(av[2]);
	a->time_to_eat = ft_atol(av[3]);
	a->time_to_sleep = ft_atol(av[4]);
	a->numb_time_eat = (ac == 6) ? ft_atol(av[5]) : -1;
	if (a->numb_philo <= 0 || a->time_to_die < 0
		|| a->time_to_eat < 0 || a->time_to_sleep < 0)
		return (0);
	return (1);
}

int	parse_args(int ac, char **av, t_args *a)
{
	int i;
	int j;

	if (ac < 5 || ac > 6)
		return (printf("Usage: %s <nb_philo> <time_to_die> <time_to_eat> "
			"<time_to_sleep> [must_eat]\n", av[0]), 0);
	i = 1;
	while (i < ac)
	{
		j = 0;
		if (av[i][0] == '\0')
			return (0);
		while (av[i][j])
			if (!is_digit(av[i][j++]))
				return (0);
		i++;
	}
	if (!set_args(a, ac, av))
		return (0);
	return (1);
}
