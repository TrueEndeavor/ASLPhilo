/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:17:46 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/12 20:25:37 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	initialize_feast(int argc, char *argv[], t_feast *feast)
{
	int i;
	
	i = 0;
	feast->num_philo = ft_atoi(argv[NUMBER_OF_PHILO]);
	feast->time_to_die = ft_atoi(argv[TIME_TO_DIE]);
	feast->time_to_eat = ft_atoi(argv[TIME_TO_EAT]);
	feast->time_to_sleep = ft_atoi(argv[TIME_TO_SLEEP]);
	if (argc == 6)
		feast->meal_limit = ft_atoi(argv[MEAL_LIMIT]);
	else
		feast->meal_limit = 0;
	feast->fork_mutexes = (pthread_mutex_t *)malloc(feast->num_philo * sizeof(pthread_mutex_t));
	if (!feast->fork_mutexes)
		return (false);
	while (i < feast->num_philo)
	{
		pthread_mutex_init(&(feast->fork_mutexes[i]), NULL);
		i++;
	}
	pthread_mutex_init(&(feast->announce_mutex), NULL);
	pthread_mutex_init(&(feast->death_detection_mutex), NULL);
	return (true);
}

void	initialize_philos(t_feast *feast, t_philo *philo)
{
	int		i;
	size_t	time_in_ms;
	
	i = 0;
	time_in_ms = get_time_in_ms();
	while (i < feast->num_philo)
	{
		// Think about the indexes well
		philo[i].id = i + 1;
		philo[i].meals_eaten = 0;
		philo[i].start_time = time_in_ms;
		philo[i].last_meal_time = time_in_ms;
		philo[i].feast = feast;
		philo[i].left_fork_mutex = &(feast->fork_mutexes[i]);
		if (i == 0)
			philo[i].right_fork_mutex = &(feast->fork_mutexes[feast->num_philo - 1]);
		else
			philo[i].right_fork_mutex = &(feast->fork_mutexes[i - 1]);
		i++;
	}
	feast->guests = philo;
}

int	create_philo_threads(t_feast *feast, t_philo *philo)
{
	int	i;

	i = 0;
	
	while (i < feast->num_philo)
	{
		if (pthread_create(&(philo[i].thread), NULL, &philo_routine, &(philo[i])) != 0)
		{
			printf("Error creating thread %d\n", i);
			return (1);
		}
		i++;
	}
	return (0);
}