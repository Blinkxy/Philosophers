/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzoheir <mzoheir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:52:34 by mzoheir           #+#    #+#             */
/*   Updated: 2023/09/14 16:21:26 by mzoheir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_destroyer(t_mutex *mutex)
{
	pthread_mutex_destroy(&mutex->death);
	pthread_mutex_destroy(&mutex->last_meal);
	pthread_mutex_destroy(&mutex->eat);
	pthread_mutex_destroy(&mutex->start);
	pthread_mutex_destroy(&mutex->print_lock);
	pthread_mutex_destroy(&mutex->finish);
}

void	norm_main(int nb_philo, t_mutex *mutex, pthread_t *th)
{
	int	i;

	i = -1;
	while (++i < nb_philo)
		pthread_join(th[i], NULL);
	i = -1;
	while (++i < nb_philo)
		pthread_mutex_destroy(&mutex->mut[i]);
	free(mutex->mut);
	mutex_destroyer(mutex);
}

void	bis_death_check_2(t_philo *philos, char **av, t_norm *norm)
{
	pthread_mutex_lock(&philos->lock->eat);
	if (philos[norm->i].eat >= philos[norm->i].times_to_eat
		&& philos[norm->i].times_to_eat != -1)
		(norm->counter)++;
	else
		norm->counter = 0;
	pthread_mutex_unlock(&philos->lock->eat);
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
