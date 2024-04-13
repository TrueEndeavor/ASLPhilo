/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bruce_almighty.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 20:50:28 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/13 22:17:08 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Every philo checks for death of any philo
bool	is_dead(t_philo *philo)
{
	bool	death_flag;

	death_flag = false;
	pthread_mutex_lock(&philo->feast->death_detection_mutex);
	death_flag = philo->feast->is_any_dead_philo;
	pthread_mutex_unlock(&philo->feast->death_detection_mutex);
	return (death_flag);
}

// bruce_almighty checks if all philos eaten full
// Also checks for death of all philo
bool	supervise_feast(t_feast *feast, int *total)
{
	int		i;
	t_philo	*p;

	i = 0;
	while (i < feast->num_philo)
	{
		p = &feast->philo_array[i];
		pthread_mutex_lock(&feast->philo_array[i].meal_mutex);
		if (p->feast->meal_limit != 0 && p->meals_eaten >= p->feast->meal_limit)
		{
			(*total)++;
		}
		if ((get_time_in_ms() - p->last_meal_time) >= p->feast->time_to_die)
		{
			announce_message("died", p);
			pthread_mutex_lock(&feast->death_detection_mutex);
			feast->is_any_dead_philo = 1;
			pthread_mutex_unlock(&feast->death_detection_mutex);
			pthread_mutex_unlock(&feast->philo_array[i].meal_mutex);
			return (false);
		}
		pthread_mutex_unlock(&feast->philo_array[i].meal_mutex);
		i++;
	}
	return (true);
}

void	bruce_almighty(t_feast *feast)
{
	int	total;

	while (1)
	{
		total = 0;
		if (!supervise_feast(feast, &total))
			break ;
		if (feast->meal_limit != 0 && total == feast->num_philo)
		{
			pthread_mutex_lock(&feast->death_detection_mutex);
			feast->is_any_dead_philo = 1;
			pthread_mutex_unlock(&feast->death_detection_mutex);
			break ;
		}
		usleep(1000);
	}
	return ;
}
