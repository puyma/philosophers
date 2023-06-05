/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:18:31 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/05 18:26:20 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h> /* printf */
# include <stdlib.h> /* malloc, EXIT_MACROS */
# include <unistd.h> /* write */

# define USAGE "Usage: n_philosophers tt_die tt_eat tt_sleep [n_eat_times]\n"

typedef struct s_data
{
	int	n_philo;
	int	tt_die;
	int	tt_eat;
	int	tt_sleep;
	int	n_times_eat;
}		t_data;

int		str_isdigit(char *str);
int		ft_putstr_fd(char *s, int fd);

#endif /* philosophers.h */
