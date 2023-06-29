/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 18:04:02 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/29 12:45:55 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_anybody_death(t_data *data);

int	ft_launch_philosophers(t_data *data)
{
	int	i;

	i = 0;
	data->init_time = ft_gettime();
	while (i < data->n_philo)
	{
		pthread_create(&data->philo[i]->th, NULL, &ft_routine, data->philo[i]);
		++i;
	}
	ft_usleep((data->tt_eat) * data->n_philo);
	while (ft_anybody_death(data) != FALSE)
	{
		exit (0);
		return (EXIT_FAILURE);
	}
	while (i-- > 0)
	{
		if (pthread_join(data->philo[i]->th, NULL) != 0)
			printf("Failed to join thread\n");
	}
	return (EXIT_SUCCESS);
}

static int	ft_anybody_death(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (ft_gettime() - data->philo[i]->last_meal > data->tt_die)
			data->philo[i]->is_alive = FALSE;
		if (data->philo[i]->is_alive == FALSE)
		{
			ft_log_stuff(data->philo[i], DIE);
			pthread_mutex_lock(&data->general_mutex);
			return (TRUE);
		}
		++i;
	}
	return (FALSE);
}
