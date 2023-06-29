/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:11:52 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/29 19:29:23 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_eat(t_philo *philo);
static int	ft_wait(t_philo *philo, time_t tt_time, char *action);
static int	ft_log_stuff(t_philo *philo, char *action);

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	//if (philo->id % 2 == 0)
	//	ft_usleep(*philo->tt_sleep);
	while (philo->is_alive == TRUE
		&& (philo->n_eaten < *philo->n_times_eat
			|| *philo->n_times_eat == -1))
	{
		ft_eat(philo);
		ft_wait(philo, *philo->tt_sleep, SLEEP);
		ft_log_stuff(philo, THINK);
	}
	return (NULL);
}

static int	ft_eat(t_philo *philo)
{
	ft_log_stuff(philo, SPOON);
	ft_log_stuff(philo, SPOON);
	ft_log_stuff(philo, EAT);
	ft_usleep(*philo->tt_eat);
	philo->n_eaten++;
	philo->last_meal = ft_gettime();
	return (EXIT_SUCCESS);
}

static int	ft_wait(t_philo *philo, time_t tt_time, char *action)
{
	ft_log_stuff(philo, action);
	ft_usleep(tt_time);
	return (EXIT_SUCCESS);
}

static int	ft_log_stuff(t_philo *philo, char *action)
{
	printf("%8ld %3d %s\n", (ft_gettime() - *philo->init_time),
		philo->id + 1, action);
	return (EXIT_SUCCESS);
}
