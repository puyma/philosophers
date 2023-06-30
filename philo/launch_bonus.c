/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:11:08 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/29 19:33:00 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_process_job(t_philo *philo);

int	ft_launch_philosophers(t_data *data)
{
	int		i;
	int		*pid;
	t_philo	*philo;

	i = 0;
	data->init_time = ft_gettime();
	pid = (int *) malloc(sizeof(int) * data->n_philo);
	if (pid == NULL)
		ft_putstr_fd("Error allocation PIDs\n", STDERR_FILENO);
	while (i < data->n_philo)
	{
		philo = data->philo[i];
		pid[i] = fork();
		if (pid[i] == -1)
			ft_putstr_fd("Error: fork\n", STDERR_FILENO);
		if (pid[i] == 0)
			ft_process_job(data->philo[i]);
		++i;
	}
	i = 0;
	while (i < data->n_philo)
		waitpid(pid[i++], NULL, 0);
	return (EXIT_SUCCESS);
}

static int	ft_process_job(t_philo *philo)
{
	pthread_create(&philo->th, NULL, &ft_routine, philo);
	pthread_detach(philo->th);
	ft_usleep(*philo->tt_die);
	while (ft_gettime() - philo->last_meal > *philo->tt_die)
		;
	philo->is_alive = FALSE;
	printf("%8ld %3d %s\n", (ft_gettime() - *philo->init_time),
		philo->id + 1, DIE);
	exit(EXIT_SUCCESS);
}
