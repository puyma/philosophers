/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:07:50 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/05 18:08:18 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
