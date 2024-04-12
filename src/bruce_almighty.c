/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bruce_almighty.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 20:50:28 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/12 21:13:40 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	did_all_philosophers_do_their_routine(t_feast *feast, int *total)
{
	int		i;
	t_philo	*p;

	i = 0;
	while (i < feast->num_philo)
	{
		p = &feast->guests[i];
		pthread_mutex_lock(&feast->guests[i].meal_mutex);
		if (p->feast->meal_limit != 0 && p->meals_eaten >= p->feast->meal_limit)
		{
			(*total)++;
		}
		if (get_time_in_ms() - p->last_meal_time >= p->feast->time_to_die)
		{
			announce_message("died", p);
			pthread_mutex_lock(&feast->death_detection_mutex);
			feast->is_a_dead_philo = 1;
			pthread_mutex_unlock(&feast->death_detection_mutex);
			pthread_mutex_unlock(&feast->guests[i].meal_mutex);
			return (1);
		}
		pthread_mutex_unlock(&feast->guests[i].meal_mutex);
		i++;
	}
	return (0);
}

void	bruce_almighty(t_feast *feast)
{
	int	total;

	while (1)
	{
		total = 0;
		if (did_all_philosophers_do_their_routine(feast, &total) == 1)
		{
			break ;
		}
		if (feast->meal_limit != 0
			&& total == feast->num_philo)
		{
			pthread_mutex_lock(&feast->death_detection_mutex);
			feast->is_a_dead_philo = 1;
			pthread_mutex_unlock(&feast->death_detection_mutex);
			break ;
		}
		usleep(1000);
	}
	return ;
}