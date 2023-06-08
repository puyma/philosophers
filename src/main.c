/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:17:11 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/08 19:15:51 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_args(int argc, char **argv, t_data *data);
static int	init_data(t_data *data);
void		clean_data(t_data *data);

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc, argv, &data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_data(&data) == -1)
		return (EXIT_FAILURE);
	if (init_philosophers(&data) == -1)
		return (EXIT_FAILURE);
	clean_data(&data);
	return (EXIT_SUCCESS);
}

static int	check_args(int argc, char **argv, t_data *data)
{
	if (argc != 5 && argc != 6)
		return (EXIT_FAILURE);
	while (--argc)
	{
		if (argv[argc] == NULL || *argv[argc] == '\0'
			|| str_isdigit(argv[argc]) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	data->n_times_eat = -1;
	data->n_philo = atoi(argv[1]);
	data->tt_die = atoi(argv[2]);
	data->tt_eat = atoi(argv[3]);
	data->tt_sleep = atoi(argv[4]);
	data->mutexes = NULL;
	data->philo = NULL;
	if (argc == 6)
		data->n_times_eat = atoi(argv[5]);
	if (data->n_philo == 0)
	{
		ft_putstr_fd("Error\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	init_data(t_data *data)
{
	int	i;

	i = 0;
	data->mutexes = (t_mutex **) malloc(sizeof(t_mutex *) * data->n_philo);
	data->philo = (t_philo **) malloc(sizeof(t_philo *) * data->n_philo);
	while (i < data->n_philo)
	{
		data->mutexes[i] = (t_mutex *) malloc(sizeof(t_mutex));
		data->philo[i] = (t_philo *) malloc(sizeof(t_philo));
		if (data->mutexes[i] == NULL || data->philo[i] == NULL)
			return (EXIT_FAILURE);
		data->philo[i]->is_alive = 1;
		data->philo[i]->id = i;
		++i;
	}
	return (EXIT_SUCCESS);
}

int	init_philosophers(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < data->n_philo)
	{
		philo = data->philo[i];
		philo->spoon[0] = data->mutexes[which_fork(i, data->n_philo, LEFT)];
		philo->spoon[1] = data->mutexes[which_fork(i, data->n_philo, RIGHT)];
		if (pthread_create(&philo->th, NULL, &routine, philo) != 0)
			return (EXIT_FAILURE);
		++i;
	}
	i = 0;
	while (i < data->n_philo)
	{
		philo = data->philo[i];
		if (pthread_join(philo->th, NULL) != 0)
			perror("Failed to join thread");
		++i;
	}
	return (EXIT_SUCCESS);
}
