/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:47:35 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/21 20:45:48 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	log_stuff(t_philo *philo, char *action);

void	*routine(void *arg)
{
	time_t	time;
	t_philo	*philo;

	philo = (t_philo *) arg;
	gettimeofday(&philo->timestamp, NULL);
	time = (philo->last_meal->tv_usec - philo->timestamp.tv_usec) / 1000;
	while (time < philo->tt_die)
	{
		gettimeofday(&philo->timestamp, NULL);
	}
	log_stuff(philo, FORK);
	return (NULL);
}

int	log_stuff(t_philo *philo, char *action)
{
	struct timeval	timeval;
	time_t			time;

	gettimeofday(&timeval, NULL);
	time = (timeval.tv_usec - philo->init_time->tv_usec) / 1000;
	pthread_mutex_lock(philo->general_mutex_ptr);
	printf("[%jd] %d %s\n", time, philo->id + 1, action);
	pthread_mutex_unlock(philo->general_mutex_ptr);
	return (EXIT_SUCCESS);
}


