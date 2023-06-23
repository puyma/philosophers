/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:47:35 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/23 13:28:47 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	log_stuff(t_philo *philo, char *action, time_t time);

void	*routine(void *arg)
{
	time_t	time;
	t_philo	*philo;
	int		i;

	philo = (t_philo *) arg;
	gettimeofday(&philo->timestamp, NULL);
	time = (philo->timestamp.tv_usec - philo->last_meal->tv_usec) / 1000;
	while (time < (long) philo->tt_die)
	{
		i = pthread_mutex_lock(philo->spoon[0]);
		log_stuff(philo, FORK, time);
		if (philo->spoon[0] == philo->spoon[1])
		{
			//printf("same\n");
			break ;
		}
		i = pthread_mutex_lock(philo->spoon[1]);
		log_stuff(philo, FORK, time);
		gettimeofday(philo->last_meal, NULL);
		printf("last_meal: %d\n", philo->last_meal->tv_usec);
		log_stuff(philo, EAT, time);
		usleep(philo->tt_eat * 1000);
		pthread_mutex_unlock(philo->spoon[0]);
		pthread_mutex_unlock(philo->spoon[1]);
		gettimeofday(&philo->timestamp, NULL);
		time = (philo->timestamp.tv_usec - philo->last_meal->tv_usec) / 1000;
	}
	log_stuff(philo, DIE, time);
	return (NULL);
}

int	log_stuff(t_philo *philo, char *action, time_t time)
{
	pthread_mutex_lock(philo->general_mutex_ptr);
	printf("[%03jd] %d %s\n", time, philo->id + 1, action);
	pthread_mutex_unlock(philo->general_mutex_ptr);
	return (EXIT_SUCCESS);
}
