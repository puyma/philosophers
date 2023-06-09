/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:18:31 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/30 13:50:11 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h> /* pthread_* */
# include <stdio.h> /* printf */
# include <stdlib.h> /* malloc, free, exit, EXIT_MACROS */
# include <string.h> /* memset */
# include <sys/time.h> /* gettimeofday, struct timeval */
# include <unistd.h> /* write, usleep, fork */

# include <signal.h> /* kill */
# include <sys/wait.h> /* waitpid */
# include <semaphore.h> /* sem_* */

# define LEFT	0
# define RIGHT	1
# define TRUE	1
# define FALSE	0
# define SPOON	"has taken a fork"
# define EAT	"is eating"
# define SLEEP	"is sleeping"
# define THINK	"is thinking"
# define DIE	"died"
# define USAGE	"Usage: n_philosophers tt_die tt_eat tt_sleep [n_eat_times]\n"
# define SEM_F	"/spoons"
# define SEM_P	"/printer"

typedef pthread_mutex_t	t_mutex;

typedef struct s_philosopher
{
	int				id;
	int				is_alive;
	int				n_eaten;
	pthread_t		th;
	sem_t			*spoons;
	sem_t			*printer;
	long int		*init_time;
	long int		last_meal;
	int				*tt_die;
	int				*tt_eat;
	int				*tt_sleep;
	int				*tt_think;
	int				*n_times_eat;
}					t_philo;

typedef struct s_data
{
	int				n_philo;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				n_times_eat;
	long int		init_time;
	sem_t			*spoons;
	sem_t			*printer;
	t_philo			**philo;
}					t_data;

/* clean.c */
void		ft_clean_data(t_data *data);

/* launch.c */
int			ft_launch_philosophers(t_data *data);

/* routine.c */
void		*ft_routine(void *arg);

/* str_utils.c */
int			ft_str_isdigit(char *str);
int			ft_putstr_fd(char *s, int fd);
int			ft_atoi(const char *str);

/* time_utils.c */
long int	ft_gettime(void);
int			ft_usleep(long int time);

#endif /* philosophers.h */
