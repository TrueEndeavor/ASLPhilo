/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:17:46 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/13 21:58:43 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	initialize_feast(int argc, char *argv[], t_feast *feast)
{
	int	i;

	i = 0;
	feast->num_philo = ft_atoi(argv[NUM_PHILO]);
	feast->time_to_die = ft_atoi(argv[TIME_TO_DIE]);
	feast->time_to_eat = ft_atoi(argv[TIME_TO_EAT]);
	feast->time_to_sleep = ft_atoi(argv[TIME_TO_SLEEP]);
	if (argc == 6)
		feast->meal_limit = ft_atoi(argv[MEAL_LIMIT]);
	else
		feast->meal_limit = 0;
	feast->fork_mutexes = \
		(pthread_mutex_t *)malloc(feast->num_philo * sizeof(pthread_mutex_t));
	if (!feast->fork_mutexes)
		return (false);
	while (i < feast->num_philo)
	{
		pthread_mutex_init(&(feast->fork_mutexes[i]), NULL);
		i++;
	}
	feast->is_any_dead_philo = false;
	pthread_mutex_init(&(feast->announcement_mutex), NULL);
	pthread_mutex_init(&(feast->death_detection_mutex), NULL);
	return (true);
}

void	initialize_philos(t_feast *feast, int i)
{
	feast->philo_array[i].id = i + 1;
	feast->philo_array[i].meals_eaten = 0;
	feast->philo_array[i].feast = feast;
	feast->philo_array[i].left_fork_mutex = &(feast->fork_mutexes[i]);
	if (i == 0)
		feast->philo_array[i].right_fork_mutex = \
			&(feast->fork_mutexes[feast->num_philo - 1]);
	else
		feast->philo_array[i].right_fork_mutex = &(feast->fork_mutexes[i - 1]);
	pthread_mutex_init(&(feast->philo_array[i].meal_mutex), NULL);
}

// One thread per philo
int	create_philo_threads(t_feast *feast, t_philo *philo)
{
	int		i;
	size_t	time_in_ms;

	i = 0;
	while (i < feast->num_philo)
	{
		initialize_philos(feast, i);
		i++;
	}
	time_in_ms = get_time_in_ms();
	feast->philo_array = philo;
	i = 0;
	while (i < feast->num_philo)
	{
		feast->philo_array[i].start_time = time_in_ms;
		feast->philo_array[i].last_meal_time = time_in_ms;
		if (pthread_create(&(feast->philo_array[i].thread), NULL, &routine, \
			&(feast->philo_array[i])) != 0)
		{
			printf("Error creating thread %d\n", i);
			return (1);
		}
		i++;
	}
	return (0);
}
