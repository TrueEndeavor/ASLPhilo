/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:58:30 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/12 21:22:54 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define NUM_PHILOSOPHERS 200

int main(int argc, char *argv[])
{
	t_feast	*feast;
	t_philo *philo;
	
	if (!get_args(argc, argv))
		return (1);
	feast = (t_feast *) malloc (ft_atoi(argv[NUMBER_OF_PHILO]) * sizeof(t_feast));
	if (!feast)
		return (1);
	if (!initialize_feast(argc, argv, feast))
	{
		// Cleanup
		return (1);
	}
	philo = (t_philo *)malloc (feast->num_philo * sizeof(t_philo));
	if (!philo)
		return (1);	
	initialize_philos(feast, philo);
	create_philo_threads(feast, philo);
	bruce_almighty(feast);
	destroy_philo_threads(feast, philo);
	cleanup_feast(feast);
	return 0;
}