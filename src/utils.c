/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:42:45 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/13 19:46:10 by lannur-s         ###   ########.fr       */
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

/* 
	gettimeofday gives currenttime;
	                              Microseconds​
	Time in ms = seconds × 1000 + ------------
	                                1000
*/
size_t	get_time_in_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday function call error\n", 33);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/* Spend the given time, but make sure the CPU is not consumed.
   Thanks to the little delay of usleep, it checks if the time
   elapsed, by not consuming CPU in full */
int	ft_spend_time_in_ms(size_t milliseconds, t_philo *philo)
{
	size_t	start_time;

	start_time = get_time_in_ms();
	while (get_time_in_ms() < start_time + milliseconds \
		&& is_dead(philo) == 0)
	{
		usleep(1200);
	}
	return (0);
}
