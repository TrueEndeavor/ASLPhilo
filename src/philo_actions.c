/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:45:54 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/13 21:57:46 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_thinks(t_philo *p)
{
	if (get_time_in_ms() - p->last_meal_time >= p->feast->time_to_die
		|| is_dead(p))
	{
		return ;
	}
	announce_message("is thinking", p);
	while (get_time_in_ms() - p->last_meal_time < 0.9 * p->feast->time_to_die)
		ft_spend_time_in_ms(1, p);
}

void	even_philo_eats(t_philo *p)
{
	if (get_time_in_ms() - p->last_meal_time >= p->feast->time_to_die
		|| is_dead(p))
	{
		return ;
	}
	pthread_mutex_lock(p->right_fork_mutex);
	announce_message("has taken a fork", p);
	pthread_mutex_lock(p->left_fork_mutex);
	announce_message("has taken a fork", p);
	pthread_mutex_lock(&p->meal_mutex);
	p->last_meal_time = get_time_in_ms();
	p->meals_eaten++;
	pthread_mutex_unlock(&p->meal_mutex);
	announce_message("is eating", p);
	ft_spend_time_in_ms(p->feast->time_to_eat, p);
	pthread_mutex_unlock(p->left_fork_mutex);
	pthread_mutex_unlock(p->right_fork_mutex);
}

void	odd_philo_eats(t_philo *p)
{
	if (get_time_in_ms() - p->last_meal_time >= p->feast->time_to_die
		|| is_dead(p))
	{
		return ;
	}
	pthread_mutex_lock(p->left_fork_mutex);
	announce_message("has taken a fork", p);
	pthread_mutex_lock(p->right_fork_mutex);
	announce_message("has taken a fork", p);
	pthread_mutex_lock(&p->meal_mutex);
	p->last_meal_time = get_time_in_ms();
	p->meals_eaten++;
	pthread_mutex_unlock(&p->meal_mutex);
	announce_message("is eating", p);
	ft_spend_time_in_ms(p->feast->time_to_eat, p);
	pthread_mutex_unlock(p->right_fork_mutex);
	pthread_mutex_unlock(p->left_fork_mutex);
}

void	philo_sleeps(t_philo *p)
{
	if (get_time_in_ms() - p->last_meal_time >= p->feast->time_to_die
		|| is_dead(p))
	{
		return ;
	}
	announce_message("is sleeping", p);
	ft_spend_time_in_ms(p->feast->time_to_sleep, p);
}
