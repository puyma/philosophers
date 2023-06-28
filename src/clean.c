/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 18:08:06 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/28 18:08:16 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clean_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		free(data->mutexes[i]);
		free(data->philo[i]);
		++i;
	}
	free(data->mutexes);
	free(data->philo);
}
