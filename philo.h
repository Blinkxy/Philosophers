/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzoheir <mzoheir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 23:25:49 by mzoheir           #+#    #+#             */
/*   Updated: 2023/04/03 03:19:51 by mzoheir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct mut
{
	pthread_mutex_t	mut[200];
	pthread_mutex_t	death;
	int				dead;
}					t_mutex;

typedef struct philo
{
	int				philo_id;
	int				time_to_sleep;
	int				time_to_eat;
	int				eat;
	int				time_to_die;
	t_mutex			*lock;
	int				nb_philos;
	int				times_to_eat;
	unsigned long	start;
	unsigned long	last_meal;
}					t_philo;

unsigned long		get_time(void);
void				ft_usleep(unsigned long time);
int					f_atoi(char *str);
void				make_threads(t_philo *philos, t_mutex *mutex,
						pthread_t *th, char **av);
void				death_check(t_philo *philos, int *tab, t_mutex *mutex,
						char **av);
int					error_args(char **av);
void				subroutine(t_philo *philos);
void				print(t_philo *philos, char *s);
#endif