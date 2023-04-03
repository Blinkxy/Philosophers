/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzoheir <mzoheir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 23:17:02 by mzoheir           #+#    #+#             */
/*   Updated: 2023/04/03 03:31:42 by mzoheir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(t_philo *philos, char *s)
{
	pthread_mutex_lock(&philos->lock->death);
	if (philos->lock->dead != 1)
		printf("%ld  %d %s\n", get_time() - philos->start, philos->philo_id, s);
	pthread_mutex_unlock(&philos->lock->death);
}

void	*routine(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philos->lock->death);
		if (philos->lock->dead == 1)
			return (0);
		pthread_mutex_unlock(&philos->lock->death);
		subroutine(philos);
		philos->last_meal = get_time();
		ft_usleep(philos->time_to_eat);
		philos->eat++;
		pthread_mutex_unlock(&philos->lock->mut[(philos->philo_id
				% philos->nb_philos) + 1]);
		pthread_mutex_unlock(&philos->lock->mut[philos->philo_id]);
		if (philos->eat == philos->times_to_eat)
			return (0);
		print(philos, "is sleeping");
		ft_usleep(philos->time_to_sleep);
	}
	return (0);
}

void	make_threads(t_philo *philos, t_mutex *mutex, pthread_t *th,
		char **av)
{
	unsigned long	start_sim;
	int				i;

	start_sim = get_time();
	mutex->dead = 0;
	i = 0;
	while (++i <= f_atoi(av[1]))
	{
		philos[i].philo_id = i;
		philos[i].nb_philos = f_atoi(av[1]);
		philos[i].eat = 0;
		if (av[5])
			philos[i].times_to_eat = f_atoi(av[5]);
		else
			philos[i].times_to_eat = -1;
		philos[i].time_to_die = f_atoi(av[2]);
		philos[i].time_to_eat = f_atoi(av[3]);
		philos[i].time_to_sleep = f_atoi(av[4]);
		philos[i].start = start_sim;
		philos[i].lock = mutex;
		philos[i].last_meal = get_time();
		pthread_create(&th[i], NULL, &routine, &philos[i]);
		usleep(50);
	}
}

void	death_check(t_philo *philos, int *tab, t_mutex *mutex, char **av)
{
	tab[0] = 1;
	tab[2] = 0;
	while (1)
	{
		if (tab[2] == tab[1])
			break ;
		if (get_time()
			- philos[tab[0]].last_meal >= (unsigned long)f_atoi(av[2]))
		{
			printf("%ld %d died \n", (get_time() - philos[tab[0]].start),
				philos[tab[0]].philo_id);
			pthread_mutex_lock(&philos->lock->death);
			mutex->dead = 1;
			pthread_mutex_unlock(&philos->lock->death);
			break ;
		}
		if (philos[tab[0]].eat == philos[tab[0]].times_to_eat)
			tab[2]++;
		else
			tab[2] = 0;
		if (tab[0] == tab[1])
			tab[0] = 1;
		tab[0]++;
	}
}

int	main(int ac, char **av)
{
	int			tab[3];
	pthread_t	th[200];
	t_philo		philos[200];
	t_mutex		mutex;

	if (ac == 5 || ac == 6)
	{
		tab[0] = 0;
		tab[1] = f_atoi(av[1]);
		while (++tab[0] <= tab[1])
			pthread_mutex_init(&mutex.mut[tab[0]], NULL);
		if (error_args(av) == 0)
			return (0);
		make_threads(philos, &mutex, th, av);
		death_check(philos, tab, &mutex, av);
		tab[0] = 0;
		while (++tab[0] <= tab[1])
			pthread_join(th[tab[0]], NULL);
		tab[0] = 0;
		while (++tab[0] <= tab[1])
			pthread_mutex_destroy(&mutex.mut[tab[0]]);
	}
	return (0);
}

// Tab[0] ==> i
// Tab[1] ==> nb philos
// Tab[2] ==> Counter of finished eaten philos (Last parameter)