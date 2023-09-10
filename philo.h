/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzoheir <mzoheir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 23:25:49 by mzoheir           #+#    #+#             */
/*   Updated: 2023/09/10 13:08:21 by mzoheir          ###   ########.fr       */
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
	pthread_mutex_t	*mut;
	int				dead;
	pthread_mutex_t	death;
	pthread_mutex_t	last_meal;
	pthread_mutex_t	eat;
	pthread_mutex_t	start;
	pthread_mutex_t	print_lock;
}					t_mutex;

typedef struct philo
{
	int				philo_id;
	int				time_to_sleep;
	int				time_to_eat;
	int				eat;
	unsigned long	time_to_die;
	t_mutex			*lock;
	int				nb_philos;
	int				times_to_eat;
	unsigned long	start;
	unsigned long	last_meal;
}					t_philo;

typedef struct norm
{
	int				i;
	int				counter;
}					t_norm;

unsigned long		get_time(void);
int					ft_usleep(t_philo *philos, unsigned long time);
int					f_atoi(char *str);
void				make_threads(t_philo *philos, t_mutex *mutex, pthread_t *th,
						char **av);
void				death_check(t_philo *philos, t_mutex *mutex, char **av);
void				bis_death_check(t_philo *philos, t_norm *norm);
void				bis_death_check_2(t_philo *philos, t_mutex *mutex,
						char **av, t_norm *norm);
int					error_args(char **av);
int					error_args_bis(char **av);
int					subroutine(t_philo *philos, t_mutex *mutex);
int					print(t_philo *philos, char *s, t_mutex *mutex);
void				mutex_init(t_mutex *mutex, char **av);
int					f_strlen_double(char **str);
void				bis_main(t_norm *norm, t_philo *philos, t_mutex *mutex);
void				norm_main(int nb_philo, t_mutex *mutex, pthread_t *th,
						t_philo *philos);
void				norm_bs(t_norm *norm);
void				mutex_destroyer(t_mutex *mutex);
void				free_philos(t_philo *philos, pthread_t *th, t_mutex *mutex);
int					check_died(int died);
#endif