/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:17:11 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/05 18:36:06 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_args(int argc, char **argv, t_data *data);
int			unamed_philosophers(t_data *data);

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc, argv, &data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	unamed_philosophers(&data);
	return (EXIT_SUCCESS);
}

int	unamed_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		ft_putstr_fd("Hey\n", STDOUT_FILENO);
		++i;
	}
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
