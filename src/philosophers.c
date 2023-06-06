/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 19:25:43 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/06 20:06:52 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_philosophers(t_data *data)
{
	int		i;
	int		spoons[2];
	t_philo	*philo;

	i = 0;
	while (i < data->n_philo)
	{
		philo = data->philo[i];
		spoons[0] = which_fork(i, data->n_philo, LEFT);
		spoons[1] = which_fork(i, data->n_philo, RIGHT);
		philo->spoon[0] = data->mutexes[spoons[0]];
		philo->spoon[1] = data->mutexes[spoons[1]];
		//printf("Philosopher %d will try to pick L: %d, R: %d\n",
		//	i, spoons[0], spoons[1]);
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
		{
			printf("i: %d\n", i);
            perror("Failed to join thread");
		}
		++i;
	}
	return (EXIT_SUCCESS);
}
