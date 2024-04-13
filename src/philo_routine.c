/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:25:46 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/13 21:21:31 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	if (philo->feast->num_philo == 1)
	{
		announce_message("has taken a fork", philo);
		return (philo_ptr);
	}
	else if (philo->id % 2 == 0)
		usleep(philo->feast->time_to_eat);
	while (philo->feast->num_philo > 1 && !is_dead(philo))
	{
		if (philo->id % 2 == 0)
			even_philo_eats(philo);
		else
			odd_philo_eats(philo);
		if (!is_dead(philo))
			philo_sleeps(philo);
		if (!is_dead(philo))
			philo_thinks(philo);
	}		
	return (philo_ptr);
}
