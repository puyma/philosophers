/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:17:11 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/02 19:07:18 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		check_args(int argc, char **argv);
int		usage(void);
size_t	ft_strlen(const char *str);

int	main(int argc, char **argv)
{
	check_args(argc, argv);
	return (0);
}

int	check_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (usage());
	(void) argv;
	return (0);
}

int	usage(void)
{
	const char	*usage_str = "Usage: n_philosophers tt_die tt_eat tt_sleep [n_eat_times]\n";

	return (write(2, usage_str, ft_strlen(usage_str)));
}

size_t	ft_strlen(const char *str)
{
	size_t	nbytes;
	char	*s;

	nbytes = 0;
	s = (char *) str;
	while (s && *s != '\0')
	{
		++nbytes;
		++s;
	}
	return (nbytes);
}
