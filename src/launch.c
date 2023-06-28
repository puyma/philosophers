/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 18:04:02 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/28 18:23:39 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	anybody_death(t_data *data);

int	launch_philosophers(t_data *data)
{
	int	i;

	i = 0;
	data->init_time = ft_gettime();
	while (i < data->n_philo)
	{
		pthread_create(&data->philo[i]->th, NULL, &routine, data->philo[i]);
		++i;
	}
	while (anybody_death(data) != TRUE)
	{

	}
	while (i-- > 0)
	{
		if (pthread_join(data->philo[i]->th, NULL) != 0)
			perror("Failed to join thread");
	}
	return (EXIT_SUCCESS);
}

static int	anybody_death(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (data->philo[i]->is_alive == FALSE)
			return (TRUE);
		++i;
	}
	return (FALSE);
}
