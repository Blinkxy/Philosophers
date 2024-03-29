/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzoheir <mzoheir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 23:17:41 by mzoheir           #+#    #+#             */
/*   Updated: 2023/09/14 16:31:38 by mzoheir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_args(char **av)
{
	int	i;
	int	j;
	int	k;

	i = 1;
	while (av[i])
		i++;
	j = 1;
	while (j < i)
	{
		if (f_atoi(av[j]) <= 0)
			return (1);
		k = 0;
		while (av[j][k])
		{
			if (!(av[j][k] >= '0' && av[j][k] <= '9'))
				return (1);
			k++;
		}
		j++;
	}
	return (0);
}

int	error_args_bis(char **av)
{
	int	j;
	int	i;

	j = 0;
	i = f_strlen_double(av);
	if (f_atoi(av[1]) > 200)
		return (1);
	while (++j < i)
	{
		if (!(f_atoi(av[j]) >= 0))
			return (1);
		j++;
	}
	return (0);
}

unsigned long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
}

int	ft_usleep(t_philo *philos, unsigned long time)
{
	unsigned long	j;

	j = get_time();
	while (1)
	{
		pthread_mutex_lock(&philos->lock->death);
		if (check_died(philos->lock->dead) != 1)
		{
			pthread_mutex_unlock(&philos->lock->death);
			if (get_time() - j >= time)
				return (0);
		}
		else
		{
			pthread_mutex_unlock(&philos->lock->mut[(philos->philo_id + 1)
				% (philos->nb_philos)]);
			pthread_mutex_unlock(&philos->lock->mut[philos->philo_id]);
			pthread_mutex_unlock(&philos->lock->death);
			return (1);
		}
		usleep(50);
	}
}

int	subroutine(t_philo *philos, t_mutex *mutex)
{
	if (print(philos, "is thinking", mutex) == 1)
		return (1);
	pthread_mutex_lock(&philos->lock->eat);
	if (philos->eat >= philos->times_to_eat && philos->times_to_eat > -1)
	{
		pthread_mutex_unlock(&philos->lock->eat);
		return (1);
	}
	pthread_mutex_unlock(&philos->lock->eat);
	pthread_mutex_lock(&philos->lock->mut[philos->philo_id]);
	if (print(philos, "has taken a fork", mutex) == 1)
		return (1);
	pthread_mutex_lock(&philos->lock->mut[(philos->philo_id + 1)
		% (philos->nb_philos)]);
	if (print(philos, "has taken a fork", mutex) == 1)
		return (1);
	if (print(philos, "is eating", mutex) == 1)
		return (1);
	bis_routine(philos);
	if (ft_usleep(philos, philos->time_to_eat) == 1)
		return (1);
	pthread_mutex_unlock(&philos->lock->mut[(philos->philo_id + 1)
		% (philos->nb_philos)]);
	pthread_mutex_unlock(&philos->lock->mut[philos->philo_id]);
	return (0);
}
