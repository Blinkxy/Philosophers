/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_norm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzoheir <mzoheir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 22:48:40 by mzoheir           #+#    #+#             */
/*   Updated: 2023/09/14 16:14:08 by mzoheir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_init(t_mutex *mutex, char **av)
{
	int	i;
	int	j;

	i = 0;
	j = f_atoi(av[1]);
	mutex->dead = 0;
	mutex->finished = 0;
	mutex->mut = malloc(sizeof(pthread_mutex_t) * j);
	if (!mutex->mut)
		return ;
	{
		while (i < j)
		{
			pthread_mutex_init(&mutex->mut[i], NULL);
			i++;
		}
	}
	pthread_mutex_init(&mutex->death, NULL);
	pthread_mutex_init(&mutex->last_meal, NULL);
	pthread_mutex_init(&mutex->eat, NULL);
	pthread_mutex_init(&mutex->start, NULL);
	pthread_mutex_init(&mutex->print_lock, NULL);
	pthread_mutex_init(&mutex->finish, NULL);
}

int	f_strlen_double(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	f_atoi(char *str)
{
	int				i;
	int				res;
	int				sign;

	res = 0;
	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * sign);
}

void	bis_main(t_norm *norm, t_philo *philos, t_mutex *mutex)
{
	pthread_mutex_lock(&mutex->start);
	printf("%ld %d died \n", (get_time() - philos[norm->i].start),
		(philos[norm->i].philo_id) + 1);
	pthread_mutex_unlock(&mutex->start);
}
