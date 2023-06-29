/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:11:52 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/29 18:57:28 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	printf("%d Hey from P\n", philo->id + 1);
	philo->is_alive = FALSE;
	return (NULL);
}
