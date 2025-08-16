/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhannou <ilhannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 10:17:00 by ilhannou          #+#    #+#             */
/*   Updated: 2025/08/16 20:19:44 by ilhannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	log_action(t_philo *p, const char *msg)
{
    pthread_mutex_lock(&p->main->print_mutex);
    if (!check_death(p->main))
        printf("%ld %d %s\n", (long)(get_time_in_ms() - p->main->start_time), p->id, msg);
    pthread_mutex_unlock(&p->main->print_mutex);
}

int take_forks(t_philo *p)
{
    pthread_mutex_t *first;
    pthread_mutex_t *second;
    
    if (check_death(p->main))
        return 0;
    p->l_locked = 0;
    p->r_locked = 0;
    if (p->main->numb_philo == 1)
    {
        pthread_mutex_lock(p->l_fork);
        p->l_locked = 1;
        log_action(p, "has taken a fork");
        ft_usleep(p, p->time_to_die);
        drop_forks(p);
        return 0;
    }
    if (p->l_fork < p->r_fork)
    {
        first = p->l_fork;
        second = p->r_fork;
    }
    else
    {
        first = p->r_fork;
        second = p->l_fork;
    }
    pthread_mutex_lock(first);
    if (first == p->l_fork)
        p->l_locked = 1;
    else
        p->r_locked = 1;
    log_action(p, "has taken a fork");
    if (check_death(p->main))
    {
        drop_forks(p);
        return 0;
    }
    pthread_mutex_lock(second);
    if (second == p->l_fork)
        p->l_locked = 1;
    else
        p->r_locked = 1;
    log_action(p, "has taken a fork");
    
    if (check_death(p->main))
    {
        drop_forks(p);
        return 0;
    }
    return 1;
}


void	start_eating(t_philo *p)
{
    pthread_mutex_lock(&p->main->eat_mutex);
    p->last_meal = get_time_in_ms();
    p->is_eating = 1;
    pthread_mutex_unlock(&p->main->eat_mutex);
    log_action(p, "is eating");
    ft_usleep(p, p->time_to_eat);
    pthread_mutex_lock(&p->main->eat_mutex);
    p->is_eating = 0;
    pthread_mutex_unlock(&p->main->eat_mutex);
    if (p->numb_of_eat > 0)
    {
        p->numb_of_eat--;
        if (p->numb_of_eat == 0)
            mark_finished(p);
    }
}

void	drop_forks(t_philo *p)
{
    if (p->r_locked)
    {
        pthread_mutex_unlock(p->r_fork);
        p->r_locked = 0;
    }
    if (p->l_locked)
    {
        pthread_mutex_unlock(p->l_fork);
        p->l_locked = 0;
    }
}

void philo_think(t_philo *p)
{
    if (check_death(p->main))
        return;
    log_action(p, "is thinking");

    long buffer = (p->time_to_die - (p->time_to_eat + p->time_to_sleep));
    if (buffer > 0)
        ft_usleep(p, buffer / 2);
}
