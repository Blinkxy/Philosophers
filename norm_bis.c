/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzoheir <mzoheir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:52:34 by mzoheir           #+#    #+#             */
/*   Updated: 2023/09/07 12:33:22 by mzoheir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philos(t_philo *philos, pthread_t *th, t_mutex *mutex)
{
	mutex = NULL;
	free(philos);
	philos = NULL;
	free(th);
	th = NULL;
}

void	mutex_destroyer(t_mutex *mutex)
{
	pthread_mutex_destroy(&mutex->death);
	pthread_mutex_destroy(&mutex->last_meal);
	pthread_mutex_destroy(&mutex->eat);
	pthread_mutex_destroy(&mutex->start);
	pthread_mutex_destroy(&mutex->print_lock);
}

void	norm_main(int nb_philo, t_mutex *mutex, pthread_t *th, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < nb_philo)
	{
		pthread_join(th[i], NULL);
	}
	i = -1;
	while (++i < nb_philo)
		pthread_mutex_destroy(&mutex->mut[i]);
	mutex_destroyer(mutex);
	free_philos(philos, th, mutex);
}

void	bis_death_check_2(t_philo *philos, t_mutex *mutex, char **av,
		t_norm *norm)
{
	pthread_mutex_lock(&mutex->eat);
	bis_death_check(philos, norm);
	pthread_mutex_unlock(&mutex->eat);
	(norm->i)++;
	if ((norm->i) == f_atoi(av[1]) && f_atoi(av[1]) > 1)
		(norm->i) = 0;
	if (f_atoi(av[1]) == 1)
		(norm->i) = 0;
}

void	norm_bs(t_norm *norm)
{
	norm->i = 0;
	norm->counter = 0;
}
