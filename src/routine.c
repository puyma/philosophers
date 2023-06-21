/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:47:35 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/21 20:19:28 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	log_stuff(t_philo *philo, char *action);

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	usleep(10000);
	pthread_mutex_lock(philo->general_mutex_ptr);
	log_stuff(philo, FORK);
	pthread_mutex_unlock(philo->general_mutex_ptr);
	(void) log_stuff;
	return (NULL);
}

int	log_stuff(t_philo *philo, char *action)
{
	struct timeval	timeval;
	time_t time;

	gettimeofday(&timeval, NULL);
	time = (timeval.tv_usec - philo->init_time->tv_usec) / 1000;
	printf("[%jd] %d %s\n", time, philo->id, action);
	return (EXIT_SUCCESS);
}
