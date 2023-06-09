/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:06:27 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/30 13:51:43 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_check_args(int argc, char **argv, t_data *data);
static int	ft_init_data(t_data *data);
static int	ft_init_philosopher(int i, t_data *data);

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
	data->spoons = sem_open(SEM_F, O_CREAT, data->n_philo);
	data->printer = sem_open(SEM_P, O_CREAT, 1);
	data->philo = (t_philo **) malloc(sizeof(t_philo *) * data->n_philo);
	while (i < data->n_philo)
		ft_init_philosopher(i++, data);
	return (EXIT_SUCCESS);
}

static int	ft_init_philosopher(int i, t_data *data)
{
	data->philo[i] = (t_philo *) malloc(sizeof(t_philo));
	if (data->philo[i] == NULL)
		return (EXIT_FAILURE);
	data->philo[i]->id = i;
	data->philo[i]->is_alive = TRUE;
	data->philo[i]->spoons = data->spoons;
	data->philo[i]->printer = data->printer;
	data->philo[i]->n_eaten = 0;
	data->philo[i]->init_time = &data->init_time;
	data->philo[i]->last_meal = data->init_time;
	data->philo[i]->tt_die = &data->tt_die;
	data->philo[i]->tt_eat = &data->tt_eat;
	data->philo[i]->tt_sleep = &data->tt_sleep;
	data->philo[i]->n_times_eat = &data->n_times_eat;
	return (EXIT_SUCCESS);
}
