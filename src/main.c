/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:17:11 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/27 18:03:58 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_args(int argc, char **argv, t_data *data);
static int	init_data(t_data *data);
static int	init_philosopher(int i, t_data *data);
static int	launch_philosophers(t_data *data);

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc, argv, &data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_data(&data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (launch_philosophers(&data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	check_args(int argc, char **argv, t_data *data)
{
	int	i;

	i = argc;
	if (argc != 5 && argc != 6)
		return (EXIT_FAILURE);
	while (--i)
	{
		if (argv[i] == NULL || *argv[i] == '\0'
			|| str_isdigit(argv[i]) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	if (data->n_philo == 0)
		return (EXIT_FAILURE);
	data->philo = NULL;
	data->mutexes = NULL;
	data->n_philo = atoi(argv[1]);
	data->tt_die = atoi(argv[2]) * 1000;
	data->tt_eat = atoi(argv[3]) * 1000;
	data->tt_sleep = atoi(argv[4]) * 1000;
	data->n_times_eat = -1;
	if (argc == 6)
		data->n_times_eat = atoi(argv[5]);
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
		if (data->mutexes[i] == NULL)
			return (EXIT_FAILURE);
		pthread_mutex_init(data->mutexes[i], NULL);
		++i;
	}
	i = 0;
	while (i < data->n_philo)
		init_philosopher(i++, data);
	pthread_mutex_init(&data->general_mutex, NULL);
	gettimeofday(&data->time, NULL);
	return (EXIT_SUCCESS);
}

static int	init_philosopher(int i, t_data *data)
{
	int		forknum[2];

	data->philo[i] = (t_philo *) malloc(sizeof(t_philo));
	if (data->philo[i] == NULL)
		return (EXIT_FAILURE);
	forknum[LEFT] = which_fork(i, data->n_philo, LEFT);
	forknum[RIGHT] = which_fork(i, data->n_philo, RIGHT);
	data->philo[i]->id = i;
	data->philo[i]->is_alive = TRUE;
	data->philo[i]->init_time = &data->time;
	data->philo[i]->tt_die = &data->tt_die;
	data->philo[i]->tt_eat = &data->tt_eat;
	data->philo[i]->tt_sleep = &data->tt_sleep;
	data->philo[i]->n_times_eat = &data->n_times_eat;
	data->philo[i]->spoon[LEFT] = data->mutexes[forknum[LEFT]];
	data->philo[i]->spoon[RIGHT] = data->mutexes[forknum[RIGHT]];
	data->philo[i]->general_mutex_ptr = &data->general_mutex;
	return (EXIT_SUCCESS);
}

static int	launch_philosophers(t_data *data)
{
	static int	i = 0;

	gettimeofday(&data->time, NULL);
	while (i < data->n_philo)
	{
		pthread_create(&data->philo[i]->th, NULL, &routine, data->philo[i]);
		++i;
	}
	while (1 != TRUE)
		continue ;
	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_join(data->philo[i]->th, NULL) != 0)
			perror("Failed to join thread");
		++i;
	}
	return (EXIT_SUCCESS);
}
