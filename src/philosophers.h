/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:18:31 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/21 20:19:46 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h> /* pthread_* */
# include <stdio.h> /* printf */
# include <stdlib.h> /* malloc, free, EXIT_MACROS */
# include <string.h> /* memset */
# include <sys/time.h> /* gettimeofday, struct timeval */
# include <unistd.h> /* write, usleep */

# define LEFT	0
# define RIGHT	1
# define USAGE	"Usage: n_philosophers tt_die tt_eat tt_sleep [n_eat_times]\n"
# define TRUE	1
# define FALSE	0

# define FORK	"has taken a fork"
# define EAT	"is eating"
# define SLEEP	"is sleeping"
# define THINK	"is thinking"
# define DIE	"died"

typedef pthread_mutex_t	t_mutex;

typedef struct s_philosopher
{
	int				id;
	int				is_alive;
	t_mutex			*spoon[2];
	struct timeval	*init_time;
	t_mutex			*general_mutex_ptr;
	pthread_t		th;
}					t_philo;

typedef struct s_data
{
	int				n_philo;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				n_times_eat;
	struct timeval	time;
	t_mutex			general_mutex;
	t_mutex			**mutexes;
	t_philo			**philo;
}					t_data;

/* philosophers.c */
int		init_philosophers(t_data *data);

/* routine.c */
void	*routine(void *arg);

/* utils.c */
int		which_fork(int num, int total_num, int leftright);
int		str_isdigit(char *str);
int		ft_putstr_fd(char *s, int fd);

#endif /* philosophers.h */
