/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzoheir <mzoheir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 13:18:20 by mzoheir           #+#    #+#             */
/*   Updated: 2023/09/14 16:32:50 by mzoheir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_died(int died)
{
	if (died == 1)
		return (1);
	else
		return (0);
}

void	bis_routine(t_philo *philos)
{
	pthread_mutex_lock(&philos->lock->eat);
	philos->eat++;
	pthread_mutex_unlock(&philos->lock->eat);
	pthread_mutex_lock(&philos->lock->last_meal);
	philos->last_meal = get_time();
	pthread_mutex_unlock(&philos->lock->last_meal);
}
