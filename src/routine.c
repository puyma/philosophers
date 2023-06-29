/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:47:35 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/29 16:27:38 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_eat(t_philo *philo);
int	ft_wait(t_philo *philo, long int tt_time, char *action);

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->id % 2 == 0)
		ft_usleep(*philo->tt_sleep);
	while (philo->is_alive == TRUE
		&& (philo->n_eaten < *philo->n_times_eat || *philo->n_times_eat == -1))
	{
		if (philo->is_alive == FALSE)
			break ;
		ft_eat(philo);
		if (philo->is_alive == FALSE)
			break ;
		ft_wait(philo, *philo->tt_sleep, SLEEP);
		if (philo->is_alive == FALSE)
			break ;
		ft_log_stuff(philo, THINK);
	}
	pthread_mutex_unlock(philo->general_mutex_ptr);
	return (NULL);
}

int	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->spoon[LEFT]);
	ft_log_stuff(philo, SPOON);
	pthread_mutex_lock(philo->spoon[RIGHT]);
	ft_log_stuff(philo, SPOON);
	ft_log_stuff(philo, EAT);
	ft_usleep(*(philo->tt_eat));
	pthread_mutex_unlock(philo->spoon[LEFT]);
	pthread_mutex_unlock(philo->spoon[RIGHT]);
	philo->n_eaten++;
	philo->last_meal = ft_gettime();
	return (EXIT_SUCCESS);
}

int	ft_wait(t_philo *philo, time_t tt_time, char *action)
{
	ft_log_stuff(philo, action);
	ft_usleep(tt_time);
	return (EXIT_SUCCESS);
}

int	ft_log_stuff(t_philo *philo, char *action)
{
	pthread_mutex_lock(philo->general_mutex_ptr);
	if (philo->is_alive == FALSE)
		pthread_mutex_unlock(philo->general_mutex_ptr);
	else
		printf("%8ld %3d %s\n", (ft_gettime() - *philo->init_time),
			philo->id + 1, action);
	pthread_mutex_unlock(philo->general_mutex_ptr);
	return (EXIT_SUCCESS);
}
