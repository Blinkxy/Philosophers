/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzoheir <mzoheir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 23:17:41 by mzoheir           #+#    #+#             */
/*   Updated: 2023/05/03 20:21:08 by mzoheir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_args(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
		i++;
	j = 1;
	while (j < i)
	{
		if (f_atoi(av[j]) <= 0)
			return (1);
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

void	ft_usleep(unsigned long time)
{
	unsigned long	j;

	j = get_time();
	while (1)
	{
		if (get_time() - j >= time)
			return ;
		usleep(50);
	}
}

void	subroutine(t_philo *philos, t_mutex *mutex)
{
	print(philos, "is thinking", mutex);
	pthread_mutex_lock(&philos->lock->mut[philos->philo_id]);
	print(philos, "has taken a fork", mutex);
	pthread_mutex_lock(&philos->lock->mut[(philos->philo_id % philos->nb_philos)
		+ 1]);
	print(philos, "has taken a fork", mutex);
	print(philos, "is eating", mutex);
	pthread_mutex_lock(&philos->lock->last_meal);
	philos->last_meal = get_time();
	pthread_mutex_unlock(&philos->lock->last_meal);
	ft_usleep(philos->time_to_eat);
}
