/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:25:46 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/12 20:27:58 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *philo_routine(void *philo_ptr)
{
	t_philo	*philo;
	size_t	time;

	philo = (t_philo *) philo_ptr;
	time = get_time_in_ms() - philo->start_time;
	if (philo->feast->num_philo == 1)
	{
		announce_message("has taken a fork", philo);
		return (philo_ptr);
	}
	// to avoid data race ...making the even philos wait 
	else if (philo->id % 2 == 0)
		usleep(philo->feast->time_to_eat);
	while (philo->feast->num_philo > 1 && !is_dead(philo))
	{
		if (philo->id % 2 == 0)
			even_eats(philo);
		else
			odd_eats(philo);
		// if (!is_dead(philo))
		sleeps(philo);
		// if (!is_dead(philo))
		thinks(philo);
	}		
	return (philo_ptr);
}