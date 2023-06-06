/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:17:11 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/06 18:36:49 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_args(int argc, char **argv, t_data *data);
static int	init_mutex(t_data *data);
int			clean_death(t_data *data);

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (check_args(argc, argv, &data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_mutex(&data) == -1)
		return (EXIT_FAILURE);
	// init philosophers 
	i = 0;
	while (i < data.n_philo)
	{
		printf("Philosopher %d will try to pick L: %d, R: %d\n",
			i, which_fork(i, data.n_philo, LEFT),
			which_fork(i, data.n_philo, RIGHT));
		++i;
	}
	clean_death(&data);
	return (EXIT_SUCCESS);
}

static int	check_args(int argc, char **argv, t_data *data)
{
	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd(USAGE, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	while (--argc)
	{
		if (argv[argc] == NULL || *argv[argc] == '\0'
			|| str_isdigit(argv[argc]) != EXIT_SUCCESS)
		{
			ft_putstr_fd("Error: invalid argument(s)\n", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
	}
	data->n_times_eat = -1;
	data->n_philo = atoi(argv[1]);
	data->tt_die = atoi(argv[2]);
	data->tt_eat = atoi(argv[3]);
	data->tt_sleep = atoi(argv[4]);
	if (argc == 6)
		data->n_times_eat = atoi(argv[5]);
	return (0);
}

static int	init_mutex(t_data *data)
{
	int	i;

	data->mutexes = (pthread_mutex_t **)
		malloc(sizeof(pthread_mutex_t *) * data->n_philo);
	i = 0;
	while (i < data->n_philo)
	{
		data->mutexes[i] = (pthread_mutex_t *)
			malloc(sizeof(pthread_mutex_t));
		if (data->mutexes[i] == NULL)
		{
			ft_putstr_fd("Failed init_mutex\n", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		++i;
	}
	return (EXIT_SUCCESS);
}

int	clean_death(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		free(data->mutexes[i]);
		++i;
	}
	free(data->mutexes);
	return (EXIT_SUCCESS);
}
