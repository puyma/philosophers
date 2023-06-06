/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 19:25:43 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/06 20:16:54 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_philosophers(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < data->n_philo)
	{
		philo = data->philo[i];
		philo->spoon[0] = data->mutexes[which_fork(i, data->n_philo, LEFT)];
		philo->spoon[1] = data->mutexes[which_fork(i, data->n_philo, RIGHT)];
		if (pthread_create(&philo->th, NULL, &routine, NULL) != 0)
			perror("Failed to created thread");
		++i;
	}
	i = 0;
	sleep(2);
	while (i < data->n_philo)
	{
		philo = data->philo[i];
		if (pthread_join(philo->th, NULL) != 0)
			perror("Failed to join thread");
		++i;
	}
	return (EXIT_SUCCESS);
}
