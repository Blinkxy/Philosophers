/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzoheir <mzoheir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 23:17:02 by mzoheir           #+#    #+#             */
/*   Updated: 2023/05/09 19:10:55 by mzoheir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(t_philo *philos, char *s, t_mutex *mutex)
{
	pthread_mutex_lock(&mutex->death);
	if (philos->lock->dead != 1)
	{
		pthread_mutex_unlock(&mutex->death);
		pthread_mutex_lock(&mutex->print_lock);
		printf("%ld  %d %s\n", get_time() - philos->start, philos->philo_id, s);
		pthread_mutex_unlock(&mutex->print_lock);
	}
	pthread_mutex_unlock(&mutex->death);
}

void	*routine(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philos->lock->death);
		if (philos->lock->dead == 1)
		{
			pthread_mutex_unlock(&philos->lock->death);
			return (0);
		}
		pthread_mutex_unlock(&philos->lock->death);
		subroutine(philos, philos->lock);
		pthread_mutex_unlock(&philos->lock->mut[(philos->philo_id
				% philos->nb_philos) + 1]);
		pthread_mutex_unlock(&philos->lock->mut[philos->philo_id]);
		pthread_mutex_lock(&philos->lock->eat);
		philos->eat++;
		pthread_mutex_unlock(&philos->lock->eat);
		if (philos->eat == philos->times_to_eat)
			return (0);
		print(philos, "is sleeping", philos->lock);
		ft_usleep(philos->time_to_sleep);
	}
	return (0);
}

void	make_threads(t_philo *philos, t_mutex *mutex, pthread_t *th, char **av)
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
		philos[i].last_meal = start_sim;
		pthread_create(&th[i], NULL, &routine, &philos[i]);
		usleep(50);
	}
}

void	death_check(t_philo *philos, t_mutex *mutex, char **av)
{
	t_norm	norm;

	norm_bs(&norm);
	while (1)
	{
		if (norm.counter == f_atoi(av[1]))
			break ;
		pthread_mutex_lock(&mutex->last_meal);
		if (get_time()
			- philos[norm.i].last_meal >= philos[norm.i].time_to_die)
		{
			pthread_mutex_unlock(&mutex->last_meal);
			bis_main(&norm, philos, mutex);
			break ;
		}	
		bis_death_check_2(philos, mutex, av, &norm);
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
		if (error_args(av) == 1 || error_args_bis(av) == 1)
			return (1);
		mutex_init(&mutex, av);
		make_threads(philos, &mutex, th, av);
		death_check(philos, &mutex, av);
		tab[0] = 0;
		tab[1] = f_atoi(av[1]);
		if (tab[1] == 1)
		{
			pthread_mutex_destroy(&mutex.mut[tab[0]]);
			return (0);
		}
		else
			norm_main(tab, &mutex, th);
	}
	return (0);
}

// Tab[0] ==> i
// Tab[1] ==> nb philos
// Tab[2] ==> Counter of finished eaten philos (Last parameter)