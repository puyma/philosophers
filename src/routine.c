/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:47:35 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/28 18:17:30 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	p_eat(t_philo *philo);
int	p_wait(t_philo *philo, long int tt_time, char *action);
int	log_stuff(t_philo *philo, char *action);

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->id % 2 == 0)
		ft_usleep(100);
	while (philo->is_alive == TRUE
		&& (philo->n_eaten < *philo->n_times_eat || *philo->n_times_eat == -1))
	{
		p_eat(philo);
		p_wait(philo, *philo->tt_sleep, SLEEP);
		log_stuff(philo, THINK);
	}
	return (NULL);
}

int	p_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->spoon[LEFT]);
	log_stuff(philo, SPOON);
	pthread_mutex_lock(philo->spoon[RIGHT]);
	log_stuff(philo, SPOON);
	ft_usleep(*(philo->tt_eat));
	pthread_mutex_unlock(philo->spoon[LEFT]);
	pthread_mutex_unlock(philo->spoon[RIGHT]);
	philo->n_eaten++;
	log_stuff(philo, EAT);
	ft_usleep(*philo->tt_sleep);
	return (EXIT_SUCCESS);
}

int	p_wait(t_philo *philo, time_t tt_time, char *action)
{
	log_stuff(philo, action);
	ft_usleep(tt_time);
	return (EXIT_SUCCESS);
}

int	log_stuff(t_philo *philo, char *action)
{
	pthread_mutex_lock(philo->general_mutex_ptr);
	printf("%8ld %3d %s\n", (ft_gettime() - *philo->init_time),
		philo->id + 1, action);
	pthread_mutex_unlock(philo->general_mutex_ptr);
	return (EXIT_SUCCESS);
}
