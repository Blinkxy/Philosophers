/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzoheir <mzoheir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 23:17:41 by mzoheir           #+#    #+#             */
/*   Updated: 2023/04/03 02:57:15 by mzoheir          ###   ########.fr       */
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
			return (0);
		j++;
	}
	return (1);
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

int	f_atoi(char *str)
{
	unsigned char	*s;
	int				i;
	int				res;
	int				sign;

	s = (unsigned char *)str;
	res = 0;
	i = 0;
	sign = 1;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
		i++;
	if (s[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (s[i] == '+')
		i++;
	while (s[i] >= 48 && s[i] <= 57)
	{
		res = res * 10 + (s[i] - 48);
		i++;
	}
	return (res * sign);
}

void	subroutine(t_philo *philos)
{
	print(philos, "is thinking");
	pthread_mutex_lock(&philos->lock->mut[philos->philo_id]);
	print(philos, "has taken a fork");
	pthread_mutex_lock(&philos->lock->mut[(philos->philo_id
			% philos->nb_philos) + 1]);
	print(philos, "has taken a fork");
	print(philos, "is eating");
}
