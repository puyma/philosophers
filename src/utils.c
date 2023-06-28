/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:07:50 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/28 17:45:00 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	which_fork(int num, int total_num, int leftright)
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

int	str_isdigit(char *str)
{
	char	*s;

	s = str;
	while (s != NULL && *s != '\0')
	{
		if (! (48 <= *s && *s <= 57))
			return (EXIT_FAILURE);
		++s;
	}
	return (EXIT_SUCCESS);
}

int	ft_putstr_fd(char *s, int fd)
{
	while (*s)
		write(fd, s++, 1);
	return (0);
}

void	clean_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		free(data->mutexes[i]);
		free(data->philo[i]);
		++i;
	}
	free(data->mutexes);
	free(data->philo);
}

long int	ft_gettime(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int	ft_usleep(long int time)
{
	const long int	t = ft_gettime();
	time += t;

	while (ft_gettime() < time)
	{
		usleep(10);
	}
	return (0);
}
