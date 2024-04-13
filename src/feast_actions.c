/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feast_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:36:11 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/13 21:41:02 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	announce_message(char *str, t_philo *philo)
{
	size_t	time;

	if (is_dead(philo))
		return ;
	time = get_time_in_ms() - philo->start_time;
	pthread_mutex_lock(&philo->feast->announcement_mutex);
	printf("%zu %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->feast->announcement_mutex);
}
