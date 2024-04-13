/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:59:15 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/13 21:15:35 by lannur-s         ###   ########.fr       */
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

typedef struct PHILO_STRUCT	t_philo;

typedef struct FEAST_STRUCT
{
	int					num_philo;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	int					meal_limit;

	pthread_mutex_t		*fork_mutexes;

	bool				is_any_dead_philo;
	pthread_mutex_t		death_detection_mutex;
	pthread_mutex_t		announcement_mutex;

	struct PHILO_STRUCT	*philo_array;
}	t_feast;

typedef struct PHILO_STRUCT
{
	int				id;

	pthread_t		thread;

	size_t			start_time;

	pthread_mutex_t	*right_fork_mutex;
	pthread_mutex_t	*left_fork_mutex;

	size_t			last_meal_time;
	int				meals_eaten;
	pthread_mutex_t	meal_mutex;

	t_feast			*feast;
}	t_philo;

enum e_args
{
	NUM_PHILO = 1,
	TIME_TO_DIE = 2,
	TIME_TO_EAT = 3,
	TIME_TO_SLEEP = 4,
	MEAL_LIMIT = 5,
};

bool	get_args(int argc, char *argv[]);

bool	initialize_feast(int argc, char *argv[], t_feast *feast);
void	initialize_philos(t_feast *feast, int i);

int		create_philo_threads(t_feast *feast, t_philo *philo);
void	*routine(void *philo_ptr);
void	odd_philo_eats(t_philo *philo);
void	even_philo_eats(t_philo *philo);
void	philo_thinks(t_philo *philo);
void	philo_sleeps(t_philo *philo);

void	bruce_almighty(t_feast *feast);
bool	is_dead(t_philo *philo);
void	announce_message(char *str, t_philo *philo);

void	destroy_philo_threads(t_feast *feast, t_philo *philo);
void	cleanup_feast(t_feast *feast);

size_t	get_time_in_ms(void);
int		ft_atoi(const char *str);
int		ft_spend_time_in_ms(size_t milliseconds, t_philo *philo);

#endif