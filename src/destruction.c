/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:09:41 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/12 21:22:49 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_philo_threads(t_feast *feast, t_philo *philo)
{
	int i;
	
	i = 0;
	(void) philo; // For the moment
	while (i < feast->num_philo)
	{
		if (pthread_join(feast->guests[i].thread, NULL) != 0)
			write(2, "Join phi. thread error\n", 23);
		i++;
	}
	i = 0;
	while (i < feast->num_philo)
	{
		pthread_mutex_destroy(&feast->guests[i].meal_mutex);
		i++;
	}
}

void	cleanup_feast(t_feast *feast)
{
	int i;
	
	i = 0;
	pthread_mutex_destroy(&(feast->announce_mutex));
	pthread_mutex_destroy(&feast->death_detection_mutex);	
	if (feast->fork_mutexes)
	{
		while (i < feast->num_philo)
		{
			pthread_mutex_destroy(&(feast->fork_mutexes[i]));
			i++;
		}
	}
}
