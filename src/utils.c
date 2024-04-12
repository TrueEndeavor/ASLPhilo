/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:42:45 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/12 21:05:36 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	return ((c >= 48 && c <= 57) || 0);
}

static int	ft_isspace(int c)
{
	return (c == ' ' || c == '\f' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\v');
}

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while (ft_isspace(*str) == 1)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res * sign);
}

size_t	get_time_in_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday function call error\n", 33);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	let_sleep_in_ms(size_t milliseconds, t_philo *philo)
{
	size_t	start_time;

	(void) philo; //For the moment
	start_time = get_time_in_ms();
 	while (get_time_in_ms() < start_time + milliseconds
		&& is_dead(philo) == 0)
	{
		usleep(200);
	}
	return (0);
}

bool	is_dead(t_philo *philo)
{
	bool	boolean;

	pthread_mutex_lock(&philo->feast->death_detection_mutex);
	boolean = philo->feast->is_a_dead_philo;
	pthread_mutex_unlock(&philo->feast->death_detection_mutex);
	return (boolean);
}