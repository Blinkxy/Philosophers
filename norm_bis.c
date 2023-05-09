/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzoheir <mzoheir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:52:34 by mzoheir           #+#    #+#             */
/*   Updated: 2023/05/09 14:28:26 by mzoheir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	norm_main(int *tab, t_mutex *mutex, pthread_t *th)
{
	{
		while (++tab[0] <= tab[1])
			pthread_join(th[tab[0]], NULL);
		tab[0] = 0;
		while (++tab[0] <= tab[1])
			pthread_mutex_destroy(&mutex->mut[tab[0]]);
	}
}

void	bis_death_check_2(t_philo *philos, t_mutex *mutex, char **av,
		t_norm *norm)
{
	pthread_mutex_unlock(&mutex->last_meal);
	pthread_mutex_lock(&mutex->eat);
	bis_death_check(philos, norm);
	pthread_mutex_unlock(&mutex->eat);
	if ((norm->i) == f_atoi(av[1]) && f_atoi(av[1]) > 1)
		(norm->i) = 1;
	(norm->i)++;
	if (f_atoi(av[1]) == 1)
		(norm->i) = 1;
}

void	norm_bs(t_norm *norm)
{
	norm->i = 1;
	norm->counter = 0;
}

void	norm_bs_2(t_mutex *mutex)
{
	pthread_mutex_unlock(&mutex->start);
	pthread_mutex_lock(&mutex->last_meal);
}
