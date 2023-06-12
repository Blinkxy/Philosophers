/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_norm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzoheir <mzoheir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 22:48:40 by mzoheir           #+#    #+#             */
/*   Updated: 2023/06/09 17:01:48 by mzoheir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_init(t_mutex *mutex, char **av)
{
	int	i;
	int	j;

	i = 0;
	j = f_atoi(av[1]);
	mutex->mut = malloc(sizeof(t_philo) * j);
	if (j == 1)
		pthread_mutex_init(&mutex->mut[j - 1], NULL);
	else
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

void	bis_main(t_norm *norm, t_philo *philos, t_mutex *mutex)
{
	pthread_mutex_lock(&mutex->start);
	printf("%ld %d died \n", (get_time() - philos[norm->i].start),
		(philos[norm->i].philo_id) + 1);
	pthread_mutex_unlock(&mutex->start);
}

void	bis_death_check(t_philo *philos, t_norm *norm)
{
	if (philos[norm->i].eat == philos[norm->i].times_to_eat)
		(norm->counter)++;
	else
		norm->counter = 0;
}
