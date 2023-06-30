/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:17:11 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/30 12:15:33 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_check_args(int argc, char **argv, t_data *data);
static int	ft_init_data(t_data *data);
static int	ft_init_philosopher(int i, t_data *data);
static int	ft_which_fork(int num, int total_num, int leftright);

int	main(int argc, char **argv)
{
	t_data	data;

	if (ft_check_args(argc, argv, &data) == EXIT_FAILURE)
	{
		ft_putstr_fd(USAGE, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (ft_init_data(&data) == EXIT_FAILURE)
		return (EXIT_FAILURE + 1);
	if (ft_launch_philosophers(&data) == EXIT_FAILURE)
		return (EXIT_FAILURE + 2);
	return (EXIT_SUCCESS);
}

static int	ft_check_args(int argc, char **argv, t_data *data)
{
	int	i;

	i = argc;
	if (argc != 5 && argc != 6)
		return (EXIT_FAILURE);
	while (--i)
	{
		if (argv[i] == NULL || *argv[i] == '\0'
			|| ft_str_isdigit(argv[i]) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	data->philo = NULL;
	data->spoons = NULL;
	data->n_philo = ft_atoi(argv[1]);
	if (data->n_philo == 0)
		return (EXIT_FAILURE);
	data->tt_die = ft_atoi(argv[2]);
	data->tt_eat = ft_atoi(argv[3]);
	data->tt_sleep = ft_atoi(argv[4]);
	data->n_times_eat = -1;
	if (argc == 6)
		data->n_times_eat = ft_atoi(argv[5]);
	return (EXIT_SUCCESS);
}

static int	ft_init_data(t_data *data)
{
	int	i;

	i = 0;
	data->spoons = (t_mutex **) malloc(sizeof(t_mutex *) * data->n_philo);
	data->philo = (t_philo **) malloc(sizeof(t_philo *) * data->n_philo);
	while (i < data->n_philo)
	{
		data->spoons[i] = (t_mutex *) malloc(sizeof(t_mutex));
		if (data->spoons[i] == NULL)
			return (EXIT_FAILURE);
		pthread_mutex_init(data->spoons[i], NULL);
		++i;
	}
	i = 0;
	while (i < data->n_philo)
		ft_init_philosopher(i++, data);
	pthread_mutex_init(&data->general_mutex, NULL);
	return (EXIT_SUCCESS);
}

static int	ft_init_philosopher(int i, t_data *data)
{
	int		forknum[2];

	data->philo[i] = (t_philo *) malloc(sizeof(t_philo));
	if (data->philo[i] == NULL)
		return (EXIT_FAILURE);
	forknum[LEFT] = ft_which_fork(i, data->n_philo, LEFT);
	forknum[RIGHT] = ft_which_fork(i, data->n_philo, RIGHT);
	data->philo[i]->id = i;
	data->philo[i]->is_alive = TRUE;
	data->philo[i]->n_eaten = 0;
	data->philo[i]->init_time = &data->init_time;
	data->philo[i]->last_meal = data->init_time;
	data->philo[i]->tt_die = &data->tt_die;
	data->philo[i]->tt_eat = &data->tt_eat;
	data->philo[i]->tt_sleep = &data->tt_sleep;
	data->philo[i]->n_times_eat = &data->n_times_eat;
	data->philo[i]->spoon[LEFT] = data->spoons[forknum[LEFT]];
	data->philo[i]->spoon[RIGHT] = data->spoons[forknum[RIGHT]];
	data->philo[i]->general_mutex_ptr = &data->general_mutex;
	return (EXIT_SUCCESS);
}

static int	ft_which_fork(int num, int total_num, int leftright)
{
	int	fork_number;

	if (leftright == LEFT)
		fork_number = num;
	else if (num == 0)
		fork_number = total_num - 1;
	else
		fork_number = num - 1;
	return (fork_number);
}
