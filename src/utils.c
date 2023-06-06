/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:07:50 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/06 18:24:39 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
