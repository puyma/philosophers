/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:47:35 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/27 19:10:18 by mpuig-ma         ###   ########.fr       */
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
	while (philo->is_alive == TRUE)
	{
		p_eat(philo);
		philo->is_alive = FALSE;
	}
	return (NULL);
}

int	p_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->spoon[LEFT]);
	log_stuff(philo, SPOON, 0);
	pthread_mutex_lock(philo->spoon[RIGHT]);
	log_stuff(philo, SPOON, 0);
	usleep(*(philo->tt_eat));
	pthread_mutex_unlock(philo->spoon[LEFT]);
	pthread_mutex_unlock(philo->spoon[RIGHT]);
	if (++philo->n_eaten >= *philo->n_times_eat)
	{
		log_stuff(philo, "  has eaten enough", 0);
		usleep(*philo->tt_eat);
		exit(0);
	}
	return (EXIT_SUCCESS);
}

int	p_wait(t_philo *philo, time_t tt_time, char *action)
{
	log_stuff(philo, action, 0);
	usleep(tt_time);
	return (EXIT_SUCCESS);
}

int	log_stuff(t_philo *philo, char *action, time_t time)
{
	pthread_mutex_lock(philo->general_mutex_ptr);
	printf("[%jd] %d %s\n", time / 1000, philo->id + 1, action);
	pthread_mutex_unlock(philo->general_mutex_ptr);
	return (EXIT_SUCCESS);
}
