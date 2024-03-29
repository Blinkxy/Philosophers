/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzoheir <mzoheir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 23:17:02 by mzoheir           #+#    #+#             */
/*   Updated: 2023/09/14 16:31:53 by mzoheir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print(t_philo *philos, char *s, t_mutex *mutex)
{
	pthread_mutex_lock(&philos->lock->print_lock);
	pthread_mutex_lock(&mutex->death);
	if (check_died(philos->lock->dead) != 1)
	{
		pthread_mutex_unlock(&mutex->death);
		printf("%ld  %d %s\n", get_time() - philos->start, philos->philo_id + 1,
			s);
		pthread_mutex_unlock(&mutex->print_lock);
	}
	else
	{
		pthread_mutex_unlock(&mutex->death);
		pthread_mutex_unlock(&mutex->print_lock);
		return (1);
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philos->lock->death);
		if (check_died(philos->lock->dead))
		{
			pthread_mutex_unlock(&philos->lock->death);
			break ;
		}
		pthread_mutex_unlock(&philos->lock->death);
		if (philos->nb_philos == 1)
		{
			ft_usleep(philos, philos->time_to_die);
			break ;
		}
		if (subroutine(philos, philos->lock) == 1)
			break ;
		if (print(philos, "is sleeping", philos->lock) == 1)
			break ;
		if (ft_usleep(philos, philos->time_to_sleep) == 1)
			break ;
	}
	return (0);
}

void	make_threads(t_philo *philos, t_mutex *mutex, pthread_t *th, char **av)
{
	unsigned long	start_sim;
	int				i;

	start_sim = get_time();
	i = -1;
	while (++i < f_atoi(av[1]))
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
		usleep(60);
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
		pthread_mutex_unlock(&mutex->finish);
		pthread_mutex_lock(&mutex->last_meal);
		if (get_time() - philos[norm.i].last_meal >= philos[norm.i].time_to_die)
		{
			pthread_mutex_lock(&mutex->print_lock);
			pthread_mutex_unlock(&mutex->last_meal);
			pthread_mutex_lock(&mutex->death);
			mutex->dead = 1;
			pthread_mutex_unlock(&mutex->death);
			bis_main(&norm, philos, mutex);
			pthread_mutex_unlock(&mutex->print_lock);
			break ;
		}
		pthread_mutex_unlock(&mutex->last_meal);
		bis_death_check_2(philos, av, &norm);
	}
}

int	main(int ac, char **av)
{
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
		norm_main(f_atoi(av[1]), &mutex, th);
	}
	return (0);
}

// int main(int ac, char **av)
// {
// 	mmain(ac, av);
// 	while (1)
// 	{
// 		;
// 	}
// 	return(0);
// }