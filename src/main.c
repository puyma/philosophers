/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:17:11 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/05 19:29:49 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#define LEFT 0
#define RIGHT 1

static int	check_args(int argc, char **argv, t_data *data);
int			unamed_function(t_data *data);
int			which_fork(int num, int total_num, int leftright);

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc, argv, &data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	unamed_function(&data);
	return (EXIT_SUCCESS);
}

int	unamed_function(t_data *data)
{
	pthread_mutex_t	**mutexes;
	int				i;

	mutexes = (pthread_mutex_t **)
		malloc(sizeof(pthread_mutex_t *) * data->n_philo);
	i = 0;
	while (i < data->n_philo)
	{
		mutexes[i] = (pthread_mutex_t *)
			malloc(sizeof(pthread_mutex_t));
		++i;
	}
	i = 0;
	while (i < data->n_philo)
	{
		printf("Philosopher %d will try to pick L: %d, R: %d\n",
			i, which_fork(i, data->n_philo, LEFT),
			which_fork(i, data->n_philo, RIGHT));
		++i;
	}
	i = 0;
	return (EXIT_SUCCESS);
}

int	which_fork(int num, int total_num, int leftright)
{
	int	fork_number;

	if (num == 0 && leftright == RIGHT)
		fork_number = total_num - 1;
	else if (num == total_num - 1 && leftright == LEFT)
		fork_number = 0;
	else if (leftright == LEFT)
		fork_number = num + 1;
	else
		fork_number = num - 1;
	return (fork_number);
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
