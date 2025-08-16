/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+      */
/*   By: ilhannou <ilhannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 10:17:00 by ilhannou          #+#    #+#             */
/*   Updated: 2025/08/15 10:17:00 by ilhannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	log_action(t_philo *p, const char *msg)
{
    pthread_mutex_lock(&p->main->print_mutex);
    if (!check_death(p))
        printf("%ld %d %s\n", (long)(get_time_in_ms() - p->main->start_time), p->id, msg);
    pthread_mutex_unlock(&p->main->print_mutex);
}

void	take_forks(t_philo *p)
{
    if (check_death(p))
        return ;
    if (p->main->numb_philo == 1)
    {
        pthread_mutex_lock(p->l_fork);
        log_action(p, "has taken a fork");
    sleep_for(p, p->time_to_die);
        pthread_mutex_unlock(p->l_fork);
        return ;
    }
    if (p->id % 2 == 1)
    {
        pthread_mutex_lock(p->l_fork);
        log_action(p, "has taken a fork");
        pthread_mutex_lock(p->r_fork);
        log_action(p, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(p->r_fork);
        log_action(p, "has taken a fork");
        pthread_mutex_lock(p->l_fork);
        log_action(p, "has taken a fork");
    }
}

void	start_eating(t_philo *p)
{
    if (check_death(p))
        return ;
    pthread_mutex_lock(&p->main->eat_mutex);
    p->last_meal = get_time_in_ms();
    pthread_mutex_unlock(&p->main->eat_mutex);
    log_action(p, "is eating");
    if (p->numb_of_eat > 0)
        p->numb_of_eat--;
    sleep_for(p, p->time_to_eat);
    if (p->numb_of_eat == 0)
        mark_finished(p);
}

void	drop_forks(t_philo *p)
{
    pthread_mutex_unlock(p->r_fork);
    pthread_mutex_unlock(p->l_fork);
}

void	philo_think(t_philo *p)
{
    if (check_death(p))
        return ;
    log_action(p, "is thinking");
}
