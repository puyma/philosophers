/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:47:35 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/26 17:16:55 by mpuig-ma         ###   ########.fr       */
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
	while (philo->is_alive == TRUE)
	{
		if (philo->spoon[0] == philo->spoon[1])
		{ printf("same\n"); 
			break ;}
		p_eat(philo);
		p_wait(philo, philo->tt_sleep, SLEEP);
		p_wait(philo, philo->tt_think, THINK);
	}
	log_stuff(philo, DIE, 0);
	return (NULL);
}

int	p_eat(t_philo *philo)
{
	struct timeval	*t;
	time_t			time;

	t = &philo->timestamp;
	pthread_mutex_lock(philo->spoon[1]);
	gettimeofday(t, NULL);
	log_stuff(philo, FORK, t->tv_usec - philo->init_time->tv_usec);
	printf("[%d] trying\n", philo->id + 1);
	pthread_mutex_lock(philo->spoon[0]);
	gettimeofday(t, NULL);
	log_stuff(philo, FORK, t->tv_usec - philo->init_time->tv_usec);
	gettimeofday(t, NULL);
	log_stuff(philo, EAT, (t->tv_usec - philo->init_time->tv_usec));
	while ((t->tv_usec - philo->last_meal->tv_usec) < philo->tt_eat)
	{
		gettimeofday(t, NULL);
	}
	gettimeofday(t, NULL);
	gettimeofday(&philo->timestamp, NULL);
	philo->last_meal = &philo->timestamp;
	time = t->tv_usec - philo->last_meal->tv_usec;
	pthread_mutex_unlock(philo->spoon[0]);
	pthread_mutex_unlock(philo->spoon[1]);
	return (0);
}

int	p_wait(t_philo *philo, time_t tt_time, char *action)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	log_stuff(philo, action, t.tv_usec - philo->init_time->tv_usec);
	while ((t.tv_usec - philo->last_meal->tv_usec) < tt_time)
		gettimeofday(&t, NULL);
	return (0);
}

int	log_stuff(t_philo *philo, char *action, time_t time)
{
	pthread_mutex_lock(philo->general_mutex_ptr);
	printf("[%jd] %d %s\n", time / 1000, philo->id + 1, action);
	pthread_mutex_unlock(philo->general_mutex_ptr);
	return (EXIT_SUCCESS);
}
