/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:47:35 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/27 18:07:13 by mpuig-ma         ###   ########.fr       */
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
	if (philo->id % 2 == 0)
		usleep(100);
	p_eat(philo);
	return (NULL);
}

int	p_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->spoon[LEFT]);
	log_stuff(philo, SPOON, 0);
	pthread_mutex_lock(philo->spoon[RIGHT]);
	log_stuff(philo, SPOON, 0);
	usleep(*(philo->tt_eat) * 100);
	pthread_mutex_unlock(philo->spoon[LEFT]);
	pthread_mutex_unlock(philo->spoon[RIGHT]);
	log_stuff(philo, SLEEP, 0);
	return (EXIT_SUCCESS);
}

int	p_wait(t_philo *philo, time_t tt_time, char *action)
{
	log_stuff(philo, action, 0);
	usleep(tt_time * 100);
	return (EXIT_SUCCESS);
}

int	log_stuff(t_philo *philo, char *action, time_t time)
{
	pthread_mutex_lock(philo->general_mutex_ptr);
	printf("[%jd] %d %s\n", time / 1000, philo->id + 1, action);
	pthread_mutex_unlock(philo->general_mutex_ptr);
	return (EXIT_SUCCESS);
}
