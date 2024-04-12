/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:59:15 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/12 21:09:31 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct PHILO_STRUCT t_philo;

typedef struct FEAST_STRUCT
{
	int					num_philo;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	int					meal_limit;
	bool				is_a_dead_philo;

	pthread_mutex_t     *fork_mutexes;
	
	pthread_mutex_t		announce_mutex;
	pthread_mutex_t		death_detection_mutex;	
	struct PHILO_STRUCT *guests;
}	t_feast;

typedef struct PHILO_STRUCT
{
	int			id;
	int			meals_eaten;
	size_t		start_time;
	size_t		last_meal_time;
	
	t_feast 		*feast;
	pthread_t 		thread;
	
	pthread_mutex_t *right_fork_mutex;
	pthread_mutex_t *left_fork_mutex;
	
	pthread_mutex_t meal_mutex;
}	t_philo;

enum e_args
{
	NUMBER_OF_PHILO = 1,
	TIME_TO_DIE = 2,
	TIME_TO_EAT = 3,
	TIME_TO_SLEEP = 4,
	MEAL_LIMIT = 5,
};

bool		get_args(int argc, char *argv[]);

bool	initialize_feast(int argc, char *argv[], t_feast *feast);
void	initialize_philos(t_feast *feast, t_philo *philo);
int		create_philo_threads(t_feast *feast, t_philo *philo);

void	*philo_routine(void *philo_ptr);
void	destroy_philo_threads(t_feast *feast, t_philo *philo);
void	cleanup_feast(t_feast *feast, t_philo *philo);

size_t	get_time_in_ms(void);
int		ft_atoi(const char *str);
void	announce_message(char *str, t_philo *philo);
void	thinks(t_philo *philo);
void	even_eats(t_philo *philo);
void	odd_eats(t_philo *philo);
void	sleeps(t_philo *philo);
int	let_sleep_in_ms(size_t milliseconds, t_philo *philo);
bool	is_dead(t_philo *philo);
void	bruce_almighty(t_feast *feast);

#endif