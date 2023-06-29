/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 18:04:02 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/29 16:31:22 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_anybody_death(t_data *data);
static int	ft_kill_everybody(t_data *data);

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
	ft_usleep(data->tt_die);
	while (ft_anybody_death(data) == -1)
		;
	(void) ft_kill_everybody;
	pthread_mutex_lock(&data->general_mutex);
	ft_kill_everybody(data);
	printf("%8ld %3d %s\n", (ft_gettime() - data->init_time), ft_anybody_death(data) + 1, DIE);
	pthread_mutex_unlock(&data->general_mutex);
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
			return (i);
		++i;
	}
	return (-1);
}

static int	ft_kill_everybody(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		data->philo[i]->is_alive = FALSE;
		++i;
	}
	return (EXIT_SUCCESS);
}
