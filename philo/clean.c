/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 18:08:06 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/30 12:48:52 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_clean_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(data->spoons[i]);
		free(data->spoons[i]);
		free(data->philo[i]);
		++i;
	}
	pthread_mutex_destroy(&data->general_mutex);
	free(data->spoons);
	free(data->philo);
}
