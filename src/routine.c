/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:47:35 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/27 13:52:34 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	p_eat(t_philo *philo);
int	p_wait(t_philo *philo, time_t tt_time, char *action);
int	log_stuff(t_philo *philo, char *action, time_t time);

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	(void) philo;
	return (NULL);
}

int	p_eat(t_philo *philo)
{
	(void) philo;
	return (0);
}

int	p_wait(t_philo *philo, time_t tt_time, char *action)
{
	(void) philo;
	(void) tt_time;
	(void) action;
	return (0);
}

int	log_stuff(t_philo *philo, char *action, time_t time)
{
	pthread_mutex_lock(philo->general_mutex_ptr);
	printf("[%jd] %d %s\n", time / 1000, philo->id + 1, action);
	pthread_mutex_unlock(philo->general_mutex_ptr);
	return (EXIT_SUCCESS);
}
