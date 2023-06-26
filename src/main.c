/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:17:11 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/26 17:10:36 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_args(int argc, char **argv, t_data *data);
static int	init_data(t_data *data);
static int	init_philosophers(t_data *data);
static int	launch_philosophers(t_data *data);
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
	if (launch_philosophers(&data) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

//clean_data(&data);

static int	check_args(int argc, char **argv, t_data *data)
{
	const int	argc_cp = argc;

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
	data->tt_die = atoi(argv[2]) * 1000;
	data->tt_eat = atoi(argv[3]) * 1000;
	data->tt_sleep = atoi(argv[4]) * 1000;
	data->mutexes = NULL;
	data->philo = NULL;
	if (argc_cp == 6)
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
	gettimeofday(&data->time, NULL);
	pthread_mutex_init(&data->general_mutex, NULL);
	data->mutexes = (t_mutex **) malloc(sizeof(t_mutex *) * data->n_philo);
	data->philo = (t_philo **) malloc(sizeof(t_philo *) * data->n_philo);
	while (i < data->n_philo)
	{
		data->mutexes[i] = (t_mutex *) malloc(sizeof(t_mutex));
		pthread_mutex_init(data->mutexes[i], NULL);
		data->philo[i] = (t_philo *) malloc(sizeof(t_philo));
		if (data->mutexes[i] == NULL || data->philo[i] == NULL)
			return (EXIT_FAILURE);
		data->philo[i]->is_alive = TRUE;
		data->philo[i]->id = i;
		++i;
	}
	return (EXIT_SUCCESS);
}

static int	init_philosophers(t_data *data)
{
	t_philo	*philo;
	int		i;
	int		forknum[2];

	i = 0;
	while (i < data->n_philo)
	{
		forknum[LEFT] = which_fork(i, data->n_philo, LEFT);
		forknum[RIGHT] = which_fork(i, data->n_philo, RIGHT);
		philo = data->philo[i];
		philo->init_time = &data->time;
		philo->last_meal = &data->time;
		philo->tt_die = data->tt_die;
		philo->tt_eat = data->tt_eat;
		philo->tt_sleep = data->tt_sleep;
		philo->tt_think = (data->tt_die - data->tt_eat + data->tt_sleep) * 1000;
		philo->n_times_eat = data->n_times_eat;
		philo->general_mutex_ptr = &data->general_mutex;
		philo->spoon[0] = data->mutexes[forknum[LEFT]];
		philo->spoon[1] = data->mutexes[forknum[RIGHT]];
		++i;
	}
	return (EXIT_SUCCESS);
}

static int	log_stuff(t_philo *philo, char *action, time_t time)
{
	pthread_mutex_lock(philo->general_mutex_ptr);
	printf("[%04jd] %d %s\n", time / 1000, philo->id + 1, action);
	pthread_mutex_unlock(philo->general_mutex_ptr);
	return (EXIT_SUCCESS);
}

int	anybody_death(t_data *data)
{
	int				i;
	struct timeval	t;
	time_t			time;

	i = 0;
	while (i < data->n_philo)
	{
		gettimeofday(&t, NULL);
		time = data->philo[i]->last_meal->tv_usec - data->philo[i]->init_time->tv_usec;
		if (time > data->tt_die)
		{
			log_stuff(data->philo[i], DIE, time);
			pthread_mutex_lock(&data->general_mutex);
			data->philo[i]->is_alive = FALSE;
			return (TRUE);
		}
		if (data->philo[i]->is_alive == FALSE)
			return (TRUE);
		++i;
	}
	return (FALSE);
}

static int	launch_philosophers(t_data *data)
{
	int	i;

	i = 1;
	gettimeofday(&data->time, NULL);
	while (i < data->n_philo)
	{
		pthread_create(&data->philo[i]->th, NULL, &routine, data->philo[i]);
		i += 2;
	}
	i = 0;
	usleep(100);
	while (i < data->n_philo)
	{
		pthread_create(&data->philo[i]->th, NULL, &routine, data->philo[i]);
		i += 2;
	}
	while (anybody_death(data) != TRUE)
	{
		continue ;
	}
	exit (0);
	i = 0;
	while (i < data->n_philo)
	{
		printf("joining: %d\n", i + 1);
		if (pthread_join(data->philo[i++]->th, NULL) != 0)
			perror("Failed to join thread");
	}
	return (EXIT_SUCCESS);
}
